/*

Partiendo de un vector ordenado formado por los k primeros numeros enteros no negativos
(0,1,2,...,k-1), se han eliminado numeros del mismo (al menos se ha eliminado un numeros), y
los n numeros que quedan se almacenan en otro vector, con n < k. Se pretende encontrar el
numeros mas pequeño de los que se han eliminado.
Por ejemplo, si la entrada es [0, 1, 2, 6, 9, 11, 15], el elemento faltante mas pequeño es 3.
Si la entrada es [1, 2, 3, 4, 6, 9, 11, 15], entonces el resultado es 0.
Si la entrada es [0, 1, 2, 3, 4, 5, 6], entonces la salida debe ser 7.
diseñad, analizad la eficiencia (teorica y empirica) e implementad varios algoritmos para
resolver este problema: un algoritmo “obvio” y otro algoritmo mas eficiente basado en la tecnica
divide y venceras (justificad detalladamente su funcionamiento).
*/

#include <iostream>
#include <fstream>
#include "practica2.h"
using namespace std; 


// g++ main.cpp practica2.cpp -o build/main -std=c++20 -pedantic -Wall



int main(){
    [[maybe_unused]]  const int MIN_INTER = 0, MAX_INTER = 2500000;
    Practica2 p; 
    p.testProfe();

    vector<int> tams = {
        100000,      // 100 mil 
        500000,      // 500 mil
        1000000,     // 1 millón
        5000000,     // 5 millones
        10000000,    // 10 millones
        50000000,    // 50 millones
        100000000,   // 100 millones
        300000000    // 300 millones
    };

    ofstream basicoFile("data/algoritmoBasico.dat");
    ofstream divideFile("data/algoritmoDivideVenceras.dat");

    
    cout << "-----------------------ALGORTIMO BÁSICO--------------------------------\n";
    for(const auto t : tams){
        const double time = p.crearTestAleatorioAlgoritmoBasico(MIN_INTER, t);
        basicoFile << t << "\t" << time << endl;
    }
    cout << "-----------------------ALGORTIMO DIVIDE Y VENCERÁS--------------------------------\n";
    for(const auto t : tams){
        const double time = p.crearTestAleatorioAlgoritmoDivideVenceras(MIN_INTER, t);
        divideFile << t << "\t" << time << endl;
    }

    basicoFile.close();
    divideFile.close();
    
    return 0;
}