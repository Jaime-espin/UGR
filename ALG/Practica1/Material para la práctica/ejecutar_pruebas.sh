#!/bin/bash

# 1. Compilar los algoritmos (ejemplo con Burbuja e Inserción)
g++ -O2 burbuja.cpp -o burbuja
g++ -O2 insercion.cpp -o insercion

# 2. Limpiar archivos de datos viejos
echo -n "" > datos_cuadraticos.dat

# 3. Ejecutar bucle para O(n^2): de 10.000 a 250.000, saltos de 10.000
echo "Ejecutando algoritmos cuadráticos..."
for ((n=10000; n<=250000; n+=10000))
do
    ./burbuja $n >> datos_cuadraticos.dat
    ./insercion $n >> datos_cuadraticos.dat
done

echo "¡Pruebas terminadas! Datos guardados en datos_cuadraticos.dat"