/*
NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
DNI: 75571535K
GRUPO DE PRÁCTICAS: Jueves
*/

#ifndef AUTOMATA_H
#define AUTOMATA_H

int calcularTamanio(int tmax);

void mostrar(const bool estado[], const int tam);

void generarReglas(int regla, bool reglas[8]);

void inicializarEstado(bool estado[], const int tam);

void evolucionar(bool estado[], bool nuevoEstado[], const bool reglas[8], const int tam);

void ejecutarAutomata(int regla, int tmax);

#endif