#include <iostream>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

/**
 * @brief Genera un número aleatorio de tipo double en un rango específico.
 * @param min Límite inferior del rango.
 * @param max Límite superior del rango.
 * @return Un número aleatorio entre min y max.
 */
double generarAleatorioDouble(double min, double max);

/**
 * @brief Genera N intervalos aleatorios dentro de un rango de valores global.
 * @param n Número de intervalos a generar.
 * @param min Límite inferior global permitido para los intervalos.
 * @param max Límite superior global permitido para los intervalos.
 * @return Vector de pares [l_i, h_i] representando los intervalos válidos.
 */
vector<pair<double, double>> generarIntervalosAleatorios(int n, double min, double max);

/**
 * @brief Calcula el conjunto mínimo de frecuencias láser necesarias para que todas las sustancias reaccionen.
 * @param intervalos vector de pares [l_i, h_i] que representan los rangos de reacción de cada sustancia.
 * @param frecuencias vector de salida donde se almacenan las frecuencias de disparo elegidas.
 * @return Número total de disparos láser a realizar (tamaño de la solución).
 */
int minFrecuencias(const vector<pair<double,double>> &intervalos, vector<double> &frecuencias);

/**
 * @brief Determina la frecuencia de disparo del laser óptima para un grupo de sustancias con rangos solapados.
 * @param subconjunto Set de rangos de sustancias pendientes (se eliminan del set conforme quedan cubiertas por un láser).
 * @param cota_sup Frecuencia candidata actual (el límite superior de la sustancia evaluada).
 * @return double con la frecuencia exacta calculada para hacer reaccionar a este grupo de sustancias.
 */
double encuentraIntersecciones(set<pair<double,double>> &subconjunto, double cota_sup);

int main(int argc, char const *argv[]) {

    srand(time(nullptr));

    int n;
    double rango_min;
    double rango_max;
    cout << "Introduzca el numero de intervalos: " << endl;
    cin >> n;
    cout << "Introduzca el rango minimo: " << endl;
    cin >> rango_min;
    cout << "Introduzca el rango maximo: " << endl;
    cin >> rango_max;

    assert(rango_min < rango_max);
    assert(n > 0);

    vector<pair<double, double>> intervalos = generarIntervalosAleatorios(n, rango_min, rango_max);

    cout << endl << "...Los intervalos a probar son..." << endl;

    for (const auto& intervalo : intervalos)
        cout << "[" << intervalo.first << ",  " << intervalo.second << "]" << endl;

    vector<double> F;
    int num_frecuencias = minFrecuencias(intervalos,F);

    cout << endl << "La cantidad minima de frecuencias es de " << num_frecuencias << endl;
    cout << "El conjunto F de frecuencias es: " << endl << "F = {";
    //mejorando el formato
    for (size_t i = 0; i < F.size(); ++i) {
        cout << F[i];
        if (i < F.size() - 1)
            cout << ", ";
    }
    cout << "}" << endl;

    return 0;
}

int minFrecuencias(const vector<pair<double,double>> &intervalos, vector<double> &frecuencias) {

    //se usa un set y no multiset porque no nos importa que elimine los valores de los intervalos repetidos
    set<pair<double,double>> subconjuntos(intervalos.begin(), intervalos.end());
    double interseccion;

    while (!subconjuntos.empty()) {
        interseccion = encuentraIntersecciones(subconjuntos,subconjuntos.begin()->second);
        frecuencias.push_back(interseccion);
    }
    return frecuencias.size();
}


double encuentraIntersecciones(set<pair<double,double>> &subconjunto, double cota_sup) {

    assert(!subconjunto.empty());

    if (subconjunto.size() < 2){ //si solo hay 1 elemento

        subconjunto.clear();
        return cota_sup; //regreso mi frecuencia

    }else{ //si hay mas de 1 elemento

        auto siguiente = next(subconjunto.begin());
        
        if (cota_sup < siguiente->first) { //si nos pasamos

            subconjunto.erase(subconjunto.begin());
            return cota_sup;

        } else { //si hay mas intersecciones

            cota_sup = (cota_sup > siguiente->second) ? siguiente->second : cota_sup;
            subconjunto.erase(subconjunto.begin());
            return encuentraIntersecciones(subconjunto, cota_sup);
        }
    }
}

double generarAleatorioDouble(double min, double max) {

    double factor = (double)rand() / RAND_MAX;
    return min + factor * (max - min);
}

vector<pair<double, double>> generarIntervalosAleatorios(int n, double min, double max) {
    
    vector<pair<double, double>> intervalos;
    
    intervalos.reserve(n); 

    for (int i = 0; i < n; ++i) {

        double p1 = generarAleatorioDouble(min, max);
        double p2 = generarAleatorioDouble(min, max);

        double l_i = (p1 > p2) ?  p2: p1;
        double h_i = (p1 < p2) ?  p2: p1;

        intervalos.emplace_back(l_i, h_i);
    }

    return intervalos;
}