#include "LianasColgantes.h"

//-------------------------------------------------------------
//METODOS DE LA CLASE Lianas
//-------------------------------------------------------------

Lianas::Lianas(const string& archivo) : dimension(0) {
    ifstream f(archivo);
    if (!f) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        exit(-1);
    }

    f >> *this;
}

istream& operator>>(istream&flujo, Lianas& l) {
    // leemos todos los valores para determinar la dimension
    vector<int> valores;
    int v;
    while (flujo >> v)
        valores.push_back(v);

    int n = (int)sqrt( (double)valores.size() );
    if (n * n != (int)valores.size()) {
        cerr << "No contiene una matriz cuadrada " << endl;
        return flujo;
    }

    l.dimension = n;
    l.lianas.assign(n, vector<int>(n));

    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            l.lianas[i][j] = valores[k++];

    return flujo;
}

ostream& operator<<(ostream& os, const Lianas& l) {

    for (int i = 0; i < l.getDimension(); i++) {
        for (int j = 0; j < l.getDimension(); j++)
            os << l[i][j] << "\t";
        os << endl;
    }
    return os;
}


//-------------------------------------------------------------
//FUNCIONALIDADES AUXILIARES AL ALGORITMO BACKTRACKING
//-------------------------------------------------------------

EstadoCamino::EstadoCamino(int n) : fila(0), columna(0), visitados(n, vector<bool>(n, false)) {
    visitados[0][0] = true;
    ruta.push_back({0, 0});
}

bool EstadoCamino::avanzarEstado(const Lianas &l, Direccion movimiento) {

    int salto = l[fila][columna];

    auto dentro = [&l](int valor) -> bool {
        return (valor >= 0) && (valor < l.getDimension());
    };

    int destF = fila;
    int destC = columna;

    switch (movimiento) {
        case IZQUIERDA: destC -= salto; break;
        case DERECHA:   destC += salto; break;
        case ARRIBA:    destF -= salto; break;
        case ABAJO:     destF += salto; break;
        default: return false; //para que devuelva false
    }

    //Si podemos avanzar
    if (dentro(destF) && dentro(destC) && !visitados[destF][destC]) {
        fila = destF; columna = destC;
        ruta.push_back({destF, destC });
        visitados[destF][destC] = true;
        return true;
    }else
        return false;
}

void EstadoCamino::deshacerEstado(int fila_anterior, int columna_anterior) {

    visitados[fila][columna] = false;
    ruta.pop_back();
    fila = fila_anterior;
    columna = columna_anterior;
}

//-------------------------------------------------------------
//ALGORITMO BACKTRACKING
//-------------------------------------------------------------

vector<pair<int, int>> caminoHaciaAltar(const Lianas &mapa, EstadoCamino &estado, pair<int, int> destino, int &min_saltos) {

    //si no mejorará la solución que ya tenemos, podamos
    if (estado.ruta.size() >= min_saltos)
        return vector<pair<int, int>>();

    //si llegamos al destino
    if (estado.fila == destino.first && estado.columna == destino.second) {
        min_saltos = estado.ruta.size();
        return estado.ruta;
    }

    vector<pair<int, int>> mejor_ruta;
    Direccion direcciones[] = {ABAJO, DERECHA, IZQUIERDA, ARRIBA}; //ordenado asi intencionalmente porque
    // asi podra obtener los mejores caminos (que se encuentran abajo muy probablemente si es que se parte del inicio)

    for (Direccion dir : direcciones) {

        int fila_origen = estado.fila;
        int col_origen = estado.columna;

        //intentamos avanzar
        if (estado.avanzarEstado(mapa, dir)) {

            //exploramos
            vector<pair<int,int>> camino_encontrado = caminoHaciaAltar(mapa, estado, destino, min_saltos);

            if (!camino_encontrado.empty()) {
                mejor_ruta = camino_encontrado; //si encontramos un mejor camino
            }

            //restauramos hacia al estado que tenia antes de ejecutar avanzarEstado
            estado.deshacerEstado(fila_origen, col_origen);
        }
    }

    return mejor_ruta;
}