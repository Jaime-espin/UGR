#!/bin/bash

# Script para generar datos sin optimización, con formato: n;tiempo (decimales con coma)

echo "=== Generación de Datos Sin Optimización ==="
echo

BIN_DIR="/home/jaime/universidad/Practicas/ALG/Practica1/Material para la práctica/bin"
DATOS_DIR="/home/jaime/universidad/Practicas/ALG/Practica1/Material para la práctica/datos"

# Crear directorio de datos
mkdir -p "$DATOS_DIR"

# Algoritmos O(n²) - cuadráticos
echo "Algoritmos O(n²) - Cuadráticos"
for algo in burbuja insercion seleccion; do
  echo "Procesando $algo..."
  > "$DATOS_DIR/${algo}.csv"
  
  for n in 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 110000 120000 130000 140000 150000 160000 170000 180000 190000 200000 210000 220000 230000 240000 250000; do
    timeout 120 "$BIN_DIR/$algo" $n >> "$DATOS_DIR/${algo}.csv" 2>/dev/null
  done
  
  lineas=$(wc -l < "$DATOS_DIR/${algo}.csv" 2>/dev/null || echo 0)
  echo "  ✓ ${algo}.csv generado ($lineas líneas)"
done

echo

# Algoritmos O(n log n)
echo "Algoritmos O(n log n)"
for algo in mergesort quicksort; do
  echo "Procesando $algo..."
  > "$DATOS_DIR/${algo}.csv"
  
  for n in 200000 400000 600000 800000 1000000 1200000 1400000 1600000 1800000 2000000 2200000 2400000 2600000 2800000 3000000 3200000 3400000 3600000 3800000 4000000 4200000 4400000 4600000 4800000 5000000; do
    timeout 120 "$BIN_DIR/$algo" $n >> "$DATOS_DIR/${algo}.csv" 2>/dev/null
  done
  
  lineas=$(wc -l < "$DATOS_DIR/${algo}.csv" 2>/dev/null || echo 0)
  echo "  ✓ ${algo}.csv generado ($lineas líneas)"
done

echo

# Algoritmos O(n³) - cúbicos
echo "Algoritmos O(n³) - Cúbicos"
for algo in floyd dijkstra-iterado; do
  echo "Procesando $algo..."
  > "$DATOS_DIR/${algo}.csv"
  
  for n in 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200 2300 2400 2500; do
    timeout 120 "$BIN_DIR/$algo" $n >> "$DATOS_DIR/${algo}.csv" 2>/dev/null
  done
  
  lineas=$(wc -l < "$DATOS_DIR/${algo}.csv" 2>/dev/null || echo 0)
  echo "  ✓ ${algo}.csv generado ($lineas líneas)"
done

echo

# Fibonacci - exponencial
echo "Fibonacci - Exponencial"
> "$DATOS_DIR/fibonacci.csv"

for n in 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 50; do
  timeout 60 "$BIN_DIR/fibonacci" $n >> "$DATOS_DIR/fibonacci.csv" 2>/dev/null
done

lineas=$(wc -l < "$DATOS_DIR/fibonacci.csv" 2>/dev/null || echo 0)
echo "  ✓ fibonacci.csv generado ($lineas líneas)"

echo

# Hanoi - exponencial 
echo "Hanoi - Exponencial"
> "$DATOS_DIR/hanoi.csv"

for n in 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33; do
  timeout 30 "$BIN_DIR/hanoi" $n >> "$DATOS_DIR/hanoi.csv" 2>/dev/null
done

lineas=$(wc -l < "$DATOS_DIR/hanoi.csv" 2>/dev/null || echo 0)
echo "  ✓ hanoi.csv generado ($lineas líneas)"

echo
echo "=== Verificación Final ==="
for archivo in "$DATOS_DIR"/*.csv; do
  lineas=$(wc -l < "$archivo" 2>/dev/null || echo 0)
  printf "%-30s: %3d líneas\n" "$(basename "$archivo")" "$lineas"
done

echo
echo "✓ Generación completada"
ls -lh "$DATOS_DIR"/*.csv 2>/dev/null | awk '{printf "  %s (%s)\n", $9, $5}'
