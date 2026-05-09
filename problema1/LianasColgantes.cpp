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