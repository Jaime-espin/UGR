#include <iostream>
#include <filesystem>
#include <limits>
#include <chrono>
#include "LianasColgantes.h"

using namespace std;
namespace fs = std::filesystem;

const int NUM_EJECUCIONES = 10;

/**
 * @brief Imprime la ruta sobre una matriz dimension x dimension segun su orden de visita
 * @param ruta Secuencia de coordenadas del camino optimo.
 * @param dimension Tamaño del lado de la matriz.
 */
void imprimir_camino(const vector<pair<int,int>> &ruta, const int dimension) {

    vector<vector<int>> matriz_resultado(dimension, vector<int>(dimension, 0));

    //rellenamos matriz resultado
    for (int i = 0; i < ruta.size(); ++i) {
        int fila = ruta[i].first;
        int columna = ruta[i].second;
        if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
            matriz_resultado[fila][columna] = i + 1;
        }
    }

    //imprimimos matriz
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cout << matriz_resultado[i][j] << "\t";
        }
        cout << endl;
    }
}

/** @brief Serializa una coordenada como "(fila,columna)". */
ostream& operator<<(ostream& os, const pair<int, int>& coordenada) {
    os << "(" << coordenada.first << "," << coordenada.second << ")";
    return os;
}
/** @brief Serializa una ruta como "(r0,c0) -> (r1,c1) -> …" */
ostream& operator<<(ostream& os, const vector<pair<int, int>>& ruta) {
    if (ruta.empty()) {
        os << "Ruta vacía. NO TIENE SOLUCION";
        return os;
    }

    for (size_t i = 0; i < ruta.size(); ++i) {
        os << ruta[i];
        // Añadimos una flechita entre los pasos, excepto al final
        if (i < ruta.size() - 1) {
            os << " -> ";
        }
    }
    return os;
}

/**
 * @brief Lee un directorio y extrae las rutas de todos los archivos .txt
 * @param ruta_directorio La ruta al directorio
 * @return Un vector de strings con las rutas completas a los archivos
 */
vector<string> obtenerMapas(const string& ruta_directorio) {

    vector<string> archivos_txt;

    //verificamos que el directorio exista
    if (!fs::exists(ruta_directorio) or !fs::is_directory(ruta_directorio)) {
        cerr << "El directorio '" << ruta_directorio << "' no existe o no es válido." << endl;
        return archivos_txt;
    }

    //iteramos por el directorio
    for (const auto& entrada : fs::directory_iterator(ruta_directorio)) {

        // comprobamos que sea un .txt
        if (entrada.is_regular_file() && entrada.path().extension() == ".txt")
            archivos_txt.push_back(entrada.path().string()); //creamos ruta
    }

    return archivos_txt;
}

/** @brief Agrupa los datos de salida de un mapa: nombre del archivo, tamaño, ruta optima y tiempo medio. */
struct ResultadoMapa {
    string nombre;
    int dimension;
    vector<pair<int,int>> ruta;
    double tiempo_ms;
};

/**
 * @brief Ejecuta el algoritmo backtracking NUM_EJECUCIONES veces y devuelve la ruta optima y el tiempo medio.
 * @param mapa Mapa de lianas
 * @param destino Casilla objetivo
 * @param tiempo_medio_ms Parametro de salida con el tiempo medio en ms
 * @return La ruta optima encontrada
 */
vector<pair<int,int>> ejecutarConMedia(const Lianas& mapa, pair<int,int> destino, double& tiempo_medio_ms) {

    vector<pair<int,int>> mejor_ruta;
    double tiempo_total = 0.0;

    for (int i = 0; i < NUM_EJECUCIONES; ++i) {
        EstadoCamino estado(mapa.getDimension());
        int min_saltos = numeric_limits<int>::max();

        auto t0 = chrono::high_resolution_clock::now();
        vector<pair<int,int>> ruta = caminoHaciaAltar(mapa, estado, destino, min_saltos);
        auto t1 = chrono::high_resolution_clock::now();

        tiempo_total += chrono::duration<double, milli>(t1 - t0).count();

        if (i == 0)
            mejor_ruta = ruta;
    }

    tiempo_medio_ms = tiempo_total / NUM_EJECUCIONES;
    return mejor_ruta;
}

int main(const int argc, const char * argv[]) {

    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <directorio_mapas>" << endl;
        return -1;
    }

    vector<string> archivos = obtenerMapas(argv[1]);
    if (archivos.empty()) {
        cerr << "No se encontraron mapas .txt en: " << argv[1] << endl;
        return -1;
    }

    sort(archivos.begin(), archivos.end());

    vector<ResultadoMapa> resultados;

    for (const string& ruta_archivo : archivos) {

        Lianas lianas(ruta_archivo);
        int dim = lianas.getDimension();

        if (dim == 0) continue;

        pair<int,int> destino(dim - 1, dim - 1);
        double tiempo_medio_ms;
        vector<pair<int,int>> camino_optimo = ejecutarConMedia(lianas, destino, tiempo_medio_ms);

        resultados.push_back({ fs::path(ruta_archivo).filename().string(), dim, camino_optimo, tiempo_medio_ms });
    }

    cout << endl << "MATRICES RESULTADO" << endl;
    for (const ResultadoMapa& r : resultados) {
        cout << endl << "Mapa: " << r.nombre << endl;
        imprimir_camino(r.ruta, r.dimension);
    }

    cout << endl << "RESUMEN DE TRAYECETORIA" << endl;
    for (const ResultadoMapa& r : resultados) {
        int num_saltos = r.ruta.empty() ? 0 : r.ruta.size() - 1;
        cout << endl << "Mapa: " << r.nombre << endl;
        cout << "Trayectoria: " << r.ruta << endl;
        cout << "Numero de saltos: " << num_saltos << endl;
        cout << "Tiempo: " << r.tiempo_ms << " ms" << endl;
    }

    cout << endl << "TABLA PARA EL LIDER SUPREMO (OMAR)" << endl << endl;

    cout << endl << "MAPA\t SALTOS \t TIEMPO(ms) \t TRAYECTORIA" << endl;
    for (const ResultadoMapa& r : resultados) {
        int num_saltos = r.ruta.empty() ? 0 : r.ruta.size() - 1;
        cout << r.nombre << "\t" << num_saltos << "\t" << r.tiempo_ms << "\t" << r.ruta << endl;
    }

    return 0;
}