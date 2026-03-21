#!/bin/bash

# Script para generar datos faltantes de fibonacci y hanoi

echo "=== Completar Generación de Datos ==="
echo

# Recompilaciones
cd "/home/jaime/universidad/Practicas/ALG/Practica1/Material para la práctica/src" || exit 1

echo "Recompilando fibonacci..."
g++ fibonacci.cpp -o ../bin/fibonacci 2>&1 | head -20

echo "Recompilando hanoi..."
g++ hanoi.cpp -o ../bin/hanoi 2>&1 | head -20

echo
echo "Generando fibonacci.csv..."
cd "/home/jaime/universidad/Practicas/ALG/Practica1/Material para la práctica"
> datos/fibonacci.csv

for n in 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 50; do
  echo -n "  n=$n ... "
  # Ejecutar 3 veces y promediar
  t1=$(timeout 30 ./bin/fibonacci $n 2>/dev/null | cut -d',' -f2)
  t2=$(timeout 30 ./bin/fibonacci $n 2>/dev/null | cut -d',' -f2)
  t3=$(timeout 30 ./bin/fibonacci $n 2>/dev/null | cut -d',' -f2)
  
  if [ ! -z "$t1" ] && [ ! -z "$t2" ] && [ ! -z "$t3" ]; then
    # Calcular promedio usando awk para evitar problemas con bc
    promedio=$(awk -v a="$t1" -v b="$t2" -v c="$t3" 'BEGIN { print (a+b+c)/3 }')
    echo "$n,$promedio" >> datos/fibonacci.csv
    echo "[$promedio]"
  else
    echo "ERROR"
  fi
done

echo
echo "Generando hanoi.csv..."
> datos/hanoi.csv

for n in 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33; do
  echo -n "  n=$n ... "
  if resultado=$(timeout 30 ./bin/hanoi $n 2>/dev/null | grep "^$n,"); then
    echo "$resultado" >> datos/hanoi.csv
    echo "OK"
  else
    echo "ERROR/TIMEOUT"
  fi
done

echo
echo "=== Verificación Final ==="
for archivo in datos/*.csv; do
  lineas=$(wc -l < "$archivo" 2>/dev/null || echo 0)
  printf "%-30s: %3d líneas\n" "$(basename "$archivo")" "$lineas"
done

echo
echo "✓ Proceso completado"
