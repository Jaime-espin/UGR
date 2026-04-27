#!/bin/bash

# Compilar con optimizaciones
g++ -O3 camaras-fb.cpp -o camaras-fb

# Tañamos a evaluar
sizes=(20 22 24 25 26 27 28)

echo "Ejecutando pruebas para grafos tipo árbol..."
echo "----------------------------------------"

for n in "${sizes[@]}"; do
    echo "Prueba para n=$n"
    ./camaras-fb $n arbol | grep -E "Solucion OPTIMA para ARBOL|Seran necesarias|Tiempo Voraz|Tiempo Voraz Arbol|La solucion con valor|Tiempo FB"
    echo "----------------------------------------"
done
