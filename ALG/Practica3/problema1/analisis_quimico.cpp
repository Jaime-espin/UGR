#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>
#include "myTime.h"
#include <fstream>

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

/**
 * @brief Calcula el conjunto mínimo de frecuencias láser necesarias para que todas las sustancias reaccionen.
 * @param intervalos vector de pares [l_i, h_i] que representan los rangos de reacción de cada sustancia.
 * @param frecuencias vector de salida donde se almacenan las frecuencias de disparo elegidas.
 * @return Número total de disparos láser a realizar (tamaño de la solución).
 */
int minFrecuenciasGreedySuboptimo(vector<pair<double, double>>& intervalos, vector<double> &frecuencias);

/**
 * @brief Realiza la medición de tiempos y la exportación de los datos empíricos.
 */
void realizarEstudioEmpirico();

/**
 * @brief Permite al usuario probar los algoritmos introduciendo por consola el rango del intervalo.
 */
void mainManual();

int main(int argc, char const *argv[]) {

    srand(time(nullptr));

    //mainManual();
    realizarEstudioEmpirico();

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

bool ordenarInicio(const pair<double, double>& a, const pair<double, double>& b){
    if(a.first == b.first){ //Si el primer componente es igual miramos el segundo
        return a.second < b.second; 
    }

    return a.first < b.first;
}
//Mi idea es disparar por donde empieza directamente la sustancia
int minFrecuenciasGreedySuboptimo(vector<pair<double, double>>& intervalos, vector<double> &frecuencias){

    //Ordenamos por el inicio
    sort(intervalos.begin(), intervalos.end(), ordenarInicio);

    //Para cada intervalo tomamos la decisión de disparar al principio
    for(const auto& intervalo : intervalos){
        bool alcanzado = false;
        //Vemos si tenemos una frecuencia que sirva
        for(int i = 0; i < frecuencias.size() && !alcanzado; i++){
            const auto& f = frecuencias[i];
            if(f >= intervalo.first && f <= intervalo.second) alcanzado = true;
        }

        //Si no lo hemos alcanzado con ninguna frecuencia pues tenemos que disparar al inicio
        if(!alcanzado){
            frecuencias.push_back(intervalo.first);
        }
    }

    return frecuencias.size();
}

void realizarEstudioEmpirico() {

    MyTime timer;
    ofstream fileOptimo("data/algoritmoOptimo.dat");
    ofstream fileSuboptimo("data/algoritmoSuboptimo.dat");

    vector<int> tams = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000}; // Números asequibles para el n^2
    int iteraciones = 15; // Iteraciones para cada medición 

    cout << "\n--- INICIANDO ESTUDIO EMPIRICO ---" << endl;
    cout << "N\tOptimo_s\tSuboptimo_s" << endl;

    for (int n : tams) {
        double tiempo_optimo_total = 0.0;
        double tiempo_suboptimo_total = 0.0;

        for (int i = 0; i < iteraciones; ++i) {
            // Generamos el caso original aleatorio
            vector<pair<double, double>> intervalosOriginales = generarIntervalosAleatorios(n, 0, 10000);
            vector<double> F;

            // Medición del Algoritmo Óptimo
            timer.start();
            minFrecuencias(intervalosOriginales, F);
            timer.end();
            
            tiempo_optimo_total += *timer;

            // Tenemos que limpiar frecuencias y pasar copias de los intervalos
            F.clear();
            vector<pair<double, double>> intervalosCopia = intervalosOriginales; 

            // Medición del Algoritmo Subóptimo
            timer.start();
            minFrecuenciasGreedySuboptimo(intervalosCopia, F);
            timer.end();
            
            tiempo_suboptimo_total += *timer;
        }

        double media_optimo = tiempo_optimo_total / iteraciones;
        double media_suboptimo = tiempo_suboptimo_total / iteraciones;

        // Imprimimos resultados
        cout << n << "\t" << media_optimo << "\t" << media_suboptimo << endl;
        fileOptimo << n << "\t" << media_optimo << endl;
        fileSuboptimo << n << "\t" << media_suboptimo << endl;
    }

    fileOptimo.close();
    fileSuboptimo.close();
}

void mainManual(){
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

    cout << "--------- Algoritmo Voraz Óptimo ----------" << endl;
    cout << endl << "La cantidad minima de frecuencias es de " << num_frecuencias << endl;
    cout << "El conjunto F de frecuencias es: " << endl << "F = {";
    //mejorando el formato
    for (size_t i = 0; i < F.size(); ++i) {
        cout << F[i];
        if (i < F.size() - 1)
            cout << ", ";
    }
    cout << "}" << endl;

    cout << "\n\n--------- Algoritmo Voraz Subóptimo ----------" << endl;
    num_frecuencias = minFrecuenciasGreedySuboptimo(intervalos, F);
    cout << endl << "La cantidad minima de frecuencias es de " << num_frecuencias << endl;
    cout << "El conjunto F de frecuencias es: " << endl << "F = {";
    //mejorando el formato
    for (size_t i = 0; i < F.size(); ++i) {
        cout << F[i];
        if (i < F.size() - 1)
            cout << ", ";
    }
    cout << "}" << endl;
}