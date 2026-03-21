/*
NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
DNI: 75571535K
GRUPO DE PRÁCTICAS: Jueves
*/

#include <iostream>
#include "automata.h"

using namespace std;

int main() {
    int regla, tmax;

    cout << "Ingrese la regla (0-255): ";
    cin >> regla;
    cout << "Ingrese el número de iteraciones: ";
    cin >> tmax;

    if (regla < 0 || regla > 255 || tmax < 1) {
        cout << "Error: Ingrese una regla entre 0-255 y al menos 1 iteración.\n";
    }
    
    ejecutarAutomata(regla, tmax);
}
