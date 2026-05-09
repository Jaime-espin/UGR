#include <iostream>
#include "LianasColgantes.h"

using namespace std;

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

ostream& operator<<(ostream& os, const pair<int, int>& coordenada) {
    os << "(" << coordenada.first << "," << coordenada.second << ")";
    return os;
}
ostream& operator<<(ostream& os, const vector<pair<int, int>>& ruta) {
    if (ruta.empty()) {
        os << "Ruta vacía.";
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

int main(const int argc, const char * argv[]) {

    if (argc != 4) {
        cout << "Uso: " << argv[0] << " <archivo_matriz.txt> <fila_destino> <columna_destino>" << endl;
        return -1;
    }

    fstream archivo;
    archivo.open(argv[1]);
    if (!archivo) {
        cerr << "Error al abrir archivo." << endl;
        return -1;
    }

    //Inicalizamos matriz
    Lianas lianas;
    archivo >> lianas;
    int dim = lianas.getDimension();
    //Establecemos el estado inicial y la direccion objetivo
    EstadoCamino estado(dim);
    pair<int,int> destino(atoi(argv[2]) ,atoi(argv[3]));
    int min_saltos = numeric_limits<int>::max();

    if ((destino.first < 0) or (destino.first >= dim) or
        (destino.second < 0) or (destino.second >= dim)) {
        cout << "Destino invalido." << endl;
        return -1;
    }

    cout << endl << "MATRIZ INICIAL: " << lianas << endl;

    vector<pair<int,int>> camino_optimo = caminoHaciaAltar(lianas,estado,destino,min_saltos);

    cout << endl << endl << "CAMINO MAS OPTIMO:" << endl;

    imprimir_camino(camino_optimo, dim);

    cout << endl << "RESUMEN: " << camino_optimo << endl;
    cout << endl << "NUMERO DE SALTOS: " << camino_optimo.size() - 1 << endl;

    return 0;
}