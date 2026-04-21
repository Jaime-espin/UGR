#include <iostream>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

/**
 * @brief Calcula el conjunto mínimo de frecuencias láser necesarias para que todas las sustancias reaccionen.
 * @param intervalos Vector de pares [l_i, h_i] que representan los rangos de reacción de cada sustancia.
 * @param frecuencias Vector de salida donde se almacenan las frecuencias de disparo elegidas.
 * @return Número total de disparos láser a realizar (tamaño de la solución).
 */
int frecuencias(const vector<pair<double,double>> &intervalos, vector<double> &frecuencias);

/**
 * @brief Determina la frecuencia de disparo del laser óptima para un grupo de sustancias con rangos solapados.
 * @param subconjunto Set de rangos de sustancias pendientes (se eliminan del set conforme quedan cubiertas por un láser).
 * @param cota_sup Frecuencia candidata actual (el límite superior de la sustancia evaluada).
 * @return Vector con la frecuencia exacta calculada para hacer reaccionar a este grupo de sustancias.
 */
vector<double> encuentraIntersecciones(set<pair<double,double>> &subconjunto, double cota_sup);

int main(int argc, char const *argv[]) {

    vector<pair<double,double>> intervalos1 = {{1, 3}, {2, 5}, {4, 7}};
    vector<double> resultado1;
    frecuencias(intervalos1, resultado1);

    cout << "Test 1 - Intervalos: [1,3], [2,5], [4,7]" << endl;
    cout << "Intersecciones encontradas: ";
    for (double val : resultado1) cout << val << " ";
    cout << "\nTotal: " << resultado1.size() << endl << endl;

    vector<pair<double,double>> intervalos2 = {{1, 2}, {5, 6}, {10, 11}};
    vector<double> resultado2;
    frecuencias(intervalos2, resultado2);

    cout << "Test 2 - Intervalos disjuntos: [1,2], [5,6], [10,11]" << endl;
    cout << "Intersecciones encontradas: ";
    for (double val : resultado2) cout << val << " ";
    cout << "\nTotal: " << resultado2.size() << endl << endl;

    vector<pair<double,double>> intervalos3 = {{1, 10}, {2, 8}, {3, 6}, {4, 5}};
    vector<double> resultado3;
    frecuencias(intervalos3, resultado3);

    cout << "Test 3 - Intervalos anidados: [1,10], [2,8], [3,6], [4,5]" << endl;
    cout << "Intersecciones encontradas: ";
    for (double val : resultado3) cout << val << " ";
    cout << "\nTotal: " << resultado3.size() << endl;

    return 0;
}

int frecuencias(const vector<pair<double,double>> &intervalos, vector<double> &frecuencias) {

    set<pair<double,double>> subconjuntos(intervalos.begin(), intervalos.end());
    vector<double> intersecciones;

    while (!subconjuntos.empty()) {
        intersecciones = encuentraIntersecciones(subconjuntos,subconjuntos.begin()->second);
        frecuencias.insert(frecuencias.end(), intersecciones.begin(), intersecciones.end());
    }

    return frecuencias.size();
}


vector<double> encuentraIntersecciones(set<pair<double,double>> &subconjunto, double cota_sup) {

    assert(!subconjunto.empty());

    if (subconjunto.size() < 2){ //si solo hay 1 elemento

        vector<double> f{cota_sup};
        subconjunto.clear();
        return f; //regreso mi frecuencia

    }else{ //si hay mas de 1 elemento

        auto siguiente = subconjunto.begin();
        siguiente++;

        if (cota_sup < siguiente->first) { //si nos pasamos

            vector<double> f{cota_sup};
            subconjunto.erase(subconjunto.begin());
            return f;

        } else { //si hay mas intersecciones

            cota_sup = (cota_sup > siguiente->second) ? siguiente->second : cota_sup;
            subconjunto.erase(subconjunto.begin());
            return encuentraIntersecciones(subconjunto, cota_sup);
        }
    }
}