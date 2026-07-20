#include <iostream>
#include <filesystem>
#include <limits>
#include <chrono>
#include <iomanip>
#include "LianasColgantes.h"

using namespace std;
namespace fs = std::filesystem;

const int NUM_EJECUCIONES = 1;

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
    
    // algoritmo básico
    vector<pair<int,int>> ruta_basica;
    double tiempo_basico_ms;
    
    // algoritmo óptimo
    vector<pair<int,int>> ruta_optima;
    double tiempo_optimo_ms;

    double nodos_podados;
    double nodos_generados;
};

/**
 * @brief Ejecuta el algoritmo óptimo backtracking NUM_EJECUCIONES veces y devuelve la ruta optima y el tiempo medio.
 * @param mapa Mapa de lianas
 * @param destino Casilla objetivo
 * @param tiempo_medio_ms Parametro de salida con el tiempo medio en ms
 * @param media_podados Devuelve la cantidad media de nodos podados
 * @param media_generados Devuelve la cantidad media de nodos generados
 * @return La ruta optima encontrada
 */
vector<pair<int,int>> ejecutarOptimoConMedia(const Lianas& mapa, pair<int,int> destino, double& tiempo_medio_ms, double& media_podados, double& media_generados) {

    vector<pair<int,int>> mejor_ruta;
    double tiempo_total = 0.0;
    int nodos_podados = 0;
    int nodos_generados = 0;

    for (int i = 0; i < NUM_EJECUCIONES; ++i) {
        EstadoCamino estado(mapa.getDimension());
        int min_saltos = numeric_limits<int>::max();
        int nodos_pod = 0;
        int nodos_gen = 0; 

        auto t0 = chrono::high_resolution_clock::now();
        vector<pair<int,int>> ruta = caminoHaciaAltar(mapa, estado, destino, min_saltos, nodos_pod, nodos_gen);
        auto t1 = chrono::high_resolution_clock::now();

        nodos_podados += nodos_pod;
        nodos_generados += nodos_gen;

        tiempo_total += chrono::duration<double, milli>(t1 - t0).count();

        if (i == 0)
            mejor_ruta = ruta;
    }

    tiempo_medio_ms = tiempo_total / NUM_EJECUCIONES;
    media_podados = (double) nodos_podados / NUM_EJECUCIONES;
    media_generados = (double) nodos_generados / NUM_EJECUCIONES; 
    return mejor_ruta;
}

/**
 * @brief Ejecuta el algoritmo básico backtracking NUM_EJECUCIONES veces y devuelve la ruta optima y el tiempo medio.
 * @param mapa Mapa de lianas
 * @param destino Casilla objetivo
 * @param tiempo_medio_ms Parametro de salida con el tiempo medio en ms
 * @return La ruta optima encontrada
 */
vector<pair<int,int>> ejecutarBasicoConMedia(const Lianas& mapa, pair<int,int> destino, double& tiempo_medio_ms) {

    vector<pair<int,int>> mejor_ruta;
    double tiempo_total = 0.0;

    for (int i = 0; i < NUM_EJECUCIONES; ++i) {
        EstadoCamino estado(mapa.getDimension());

        auto t0 = chrono::high_resolution_clock::now();
        bool exito = caminoSencillo(mapa, estado, destino);
        auto t1 = chrono::high_resolution_clock::now();

        tiempo_total += chrono::duration<double, milli>(t1 - t0).count();

        if (i == 0 && exito)
            mejor_ruta = estado.ruta;
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
        cout << "Hago el archivo: " << ruta_archivo << endl;

        Lianas lianas(ruta_archivo);
        int dim = lianas.getDimension();

        if (dim == 0) continue;

        pair<int,int> destino(dim - 1, dim - 1);
        double tiempo_basico, tiempo_optimo;
        double nodos_podados = 0.0;
        double nodos_generados = 0.0; 

        vector<pair<int,int>> camino_basico = ejecutarBasicoConMedia(lianas, destino, tiempo_basico);
        vector<pair<int,int>> camino_optimo = ejecutarOptimoConMedia(lianas, destino, tiempo_optimo, nodos_podados, nodos_generados);

        resultados.push_back({ fs::path(ruta_archivo).filename().string(), dim, camino_basico, tiempo_basico, camino_optimo, tiempo_optimo, nodos_podados, nodos_generados });

        cout << "He terminado el archivo " << ruta_archivo << endl; 
    }

    cout << endl << "================ MATRICES RESULTADO ================" << endl;
    for (const ResultadoMapa& r : resultados) {
        cout << endl << "Mapa: " << r.nombre << " | ALGORITMO BÁSICO" << endl;
        imprimir_camino(r.ruta_basica, r.dimension);
        
        cout << endl << "Mapa: " << r.nombre << " | ALGORITMO ÓPTIMO" << endl;
        imprimir_camino(r.ruta_optima, r.dimension);
    }

    cout << endl << "================ RESUMEN DE TRAYECTORIA ================" << endl;
    for (const ResultadoMapa& r : resultados) {
        int saltos_basico = r.ruta_basica.empty() ? 0 : r.ruta_basica.size() - 1;
        int saltos_optimo = r.ruta_optima.empty() ? 0 : r.ruta_optima.size() - 1;
        
        cout << endl << "Mapa: " << r.nombre << endl;
        cout << "  [BÁSICO] Saltos: " << saltos_basico << " | Tiempo: " << r.tiempo_basico_ms << " ms" << endl;
        cout << "  Trayectoria: " << r.ruta_basica << endl;
        
        cout << "  [ÓPTIMO] Saltos: " << saltos_optimo << " | Tiempo: " << r.tiempo_optimo_ms << " ms" << endl;
        cout << "  Trayectoria: " << r.ruta_optima << endl;
    }

    cout << "================ TABLA PARA EL LIDER SUPREMO (OMAR) ================" << endl << endl;

    cout << left << setw(18) << "MAPA" 
         << right << setw(12) << "SALTOS(B)" 
         << setw(18) << "TIEMPO(B)ms" 
         << setw(12) << "SALTOS(O)" 
         << setw(18) << "TIEMPO(O)ms" 
         << setw(18) << "GENERADOS(O)" 
         << setw(15) << "PODADOS(O)" << endl;
         
    cout << string(93, '-') << endl;

    for (const ResultadoMapa& r : resultados) {
        int saltos_basico = r.ruta_basica.empty() ? 0 : r.ruta_basica.size() - 1;
        int saltos_optimo = r.ruta_optima.empty() ? 0 : r.ruta_optima.size() - 1;
        
        cout << left << setw(18) << r.nombre 
             << right << setw(12) << saltos_basico 
             << setw(18) << fixed << setprecision(4) << r.tiempo_basico_ms 
             << setw(12) << saltos_optimo 
             << setw(18) << fixed << setprecision(4) << r.tiempo_optimo_ms 
             << setw(15) << r.nodos_generados
             << setw(15) << r.nodos_podados << endl;
    }

    return 0;
}