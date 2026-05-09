#include "LianasColgantes.h"

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

// Método que utliza Backtracking 
// Funciona de la siguiente manera: Este método va a analizar todas las rutas posibles desde un pilar hacia la meta
// y se va a quedar con la secuencia que de el menor número de saltos.

void Lianas::explorar(int x, int y, int destinoX, int destinoY, vector<vector<bool>>& visitado,
         vector<pair<int, int>>& caminoActual, vector<pair<int, int>>& mejorCamino, int& minSaltos) const{

    // Primero podamos la rama en la que nos escontramos si ya tiene la misma cantidad de saltos
    // que el mejor camino encontrado hasta el momento.
    if(caminoActual.size() >= minSaltos){
        return;
    }

    // Vemos si hemos llegado al pilar de destino
    if( x == destinoX && y == destinoY){
        // Añadimos el último salto realizado al camino
        caminoActual.push_back({x,y});

        // Comprobamos si los saltos que llevamos actualmente mejoran la solución encontrada hasta el momento
        if(caminoActual.size() - 1 < minSaltos){
            minSaltos = caminoActual.size() - 1;
            mejorCamino = caminoActual;
        }

        // Eliminamos el último paso
        caminoActual.pop_back(); 
        return;
    }

    // Marcamos el pilar donde nos escontramos como visitado
    // Se añade el pilar a la ruta actual
    visitado[x][y] = true;
    caminoActual.push_back({x,y});

    // Vemos cuanto podemos saltar desde nuestra posición actual
    int k = lianas[x][y];

    // Nos aseguramos que la liana sea mayor a 0
    if(k > 0){
        // Movimiento hacia abajo (x + k, y)
        if(x + k < dimension && !visitado[x + k][y]){
            explorar(x + k, y, destinoX, destinoY,visitado, caminoActual, mejorCamino, minSaltos);
        }

        // Movimiento hacia arriba (x - k,y)
        if(x - k < dimension && !visitado[x - k][y]){
            explorar(x - k, y, destinoX, destinoY,visitado, caminoActual, mejorCamino, minSaltos);
        }

        // Movimiento hacio la derecha (x, y + k)
        if(y + k < dimension && !visitado[x][y + k]){
            explorar(x, y + k, destinoX, destinoY,visitado, caminoActual, mejorCamino, minSaltos);
        }

        // Movimiento hacio la izquierda (x, y - k)
        if(y - k < dimension && !visitado[x][y - k]){
            explorar(x, y - k, destinoX, destinoY,visitado, caminoActual, mejorCamino, minSaltos);
        }
    }

    // Al terminar de explorar todas las ramas desde ese punto quitamos
    // el pilar de la ruta actual para que otras rutas puedan pasar por el
    caminoActual.pop_back();
    visitado[x][y] = false;
}