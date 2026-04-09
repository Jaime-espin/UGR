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
#include "practica2.h"
using namespace std; 


// g++ main.cpp practica2.cpp -o build/main -std=c++20 -pedantic -Wall



int main(){
    const int MIN_INTER = 0, MAX_INTER = 2500000;
    Practica2 p; 
    p.testProfe();
    p.crearTestAleatorioAlgoritmoBasico(MIN_INTER, MAX_INTER);
    
    return 0;
}