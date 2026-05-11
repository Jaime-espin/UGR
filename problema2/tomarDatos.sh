#!/bin/bash

# Compilar con optimización
g++ -O3 ./problema2/camaras.cpp -o camaras

# Archivo de salida
OUTPUT="resultados_backtracking.csv"
echo "n,Topologia,Nodos_Generados,Nodos_Podados,Tiempo_s" > $OUTPUT

# Bucle para grafos aleatorios y tipo árbol
for topologia in "aleatorio" "arbol"; do
    for n in {10..30..2}; do
        echo "Ejecutando n=$n ($topologia)..."
        
        if [ "$topologia" == "aleatorio" ]; then
            salida=$(./problema2/camaras $n)
        else
            salida=$(./problema2/camaras $n arbol)
        fi
        
        # Extraer específicamente el bloque de Backtracking usando grep y awk
        n_generados=$(echo "$salida" | grep -A 4 "Backtracking" | grep "Nodos generados:" | awk '{print $3}')
        n_podados=$(echo "$salida" | grep -A 4 "Backtracking" | grep "Nodos podados:" | awk '{print $3}')
        tiempo=$(echo "$salida" | grep -A 4 "Backtracking" | grep "Tiempo:" | awk '{print $2}')
        
        # Guardar en CSV
        echo "$n,$topologia,$n_generados,$n_podados,$tiempo" >> $OUTPUT
    done
done

echo "Estudio finalizado. Datos guardados en $OUTPUT."