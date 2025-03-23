#include <iostream>
#include "automata.h"

using namespace std;

# define BLANCO  " \33[30;47m" // fondo blanco
# define NEGRO " \33[30;40m" // fondo negro
# define RESET " \33[0m" // resetear fondo

int calcularTamanio(int tmax) {
    int tam = tmax + 1;
    if(tam < 100){
        return tam;
    }
    return 100;
}

void mostrar ( const bool estado [ ], const int tam ) {
    for ( int i = 0; i < tam ; ++ i ){
        cout << ( estado [ i ] ? NEGRO : BLANCO) << " \u2003\u2003 " << RESET;
    }
    cout << endl;
}

void generarReglas(int regla, bool reglas[8]){
    for (int i = 0; i <= 7; i++) {
        reglas[i] = regla%2;
        regla /= 2;
    }
}

void inicializarEstado(bool estado[], const int tam){
    for (int i = 0; i < tam; i++) {
        estado[i] = false;
    }
    estado[tam / 2] = true;
}

void evolucionar(bool estado[], bool nuevoEstado[], const bool reglas[8], const int tam){
    for (int i = 0; i < tam; i++) {
        int izq = estado[(i-1 + tam) % tam];
        int centro = estado[i];
        int der = estado[(i+1) % tam];

        int indice = izq * 4 + centro * 2 + der;
        nuevoEstado[i] = reglas[indice];
    }
}

void ejecutarAutomata(int regla, int tmax){
    int tam = calcularTamanio(tmax);
    bool estado[tam], nuevoEstado[tam];
    bool reglas[8];

    generarReglas(regla, reglas);
    inicializarEstado(estado, tam);

    for (int t = 0; t < tmax; ++t) {
        mostrar(estado, tam);
        evolucionar(estado, nuevoEstado, reglas, tam);
        
        for (int i = 0; i < tam; ++i) {
            estado[i] = nuevoEstado[i];
        }
    }
}