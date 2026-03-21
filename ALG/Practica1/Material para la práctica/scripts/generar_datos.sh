#!/bin/bash

# Script para generar datos de rendimiento de los 9 algoritmos
# Salida: archivos CSV en la carpeta ../datos/

set -e

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Rutas
SRC_DIR="$(dirname "$0")/../src"
DATOS_DIR="$(dirname "$0")/../datos"
BIN_DIR="$(dirname "$0")/../bin"

# Crear directorios si no existen
mkdir -p "$DATOS_DIR"
mkdir -p "$BIN_DIR"

echo -e "${GREEN}=== Generador de Datos de Rendimiento ===${NC}"
echo "Compilando algoritmos..."
echo

# Compilar todos los algoritmos
cd "$SRC_DIR"

# Array de algoritmos
ALGORITMOS=(
  "burbuja"
  "insercion"
  "seleccion"
  "mergesort"
  "quicksort"
  "floyd"
  "dijkstra-iterado"
  "fibonacci"
  "hanoi"
)

# Compilar cada uno
for algo in "${ALGORITMOS[@]}"; do
  if [ -f "${algo}.cpp" ]; then
    echo -n "Compilando ${algo}... "
    g++ "${algo}.cpp" -o "$BIN_DIR/${algo}" 2>/dev/null
    if [ $? -eq 0 ]; then
      echo -e "${GREEN}OK${NC}"
    else
      echo -e "${RED}ERROR${NC}"
      exit 1
    fi
  fi
done

echo
echo -e "${GREEN}=== Ejecutando Análisis ===${NC}"
echo

# Algoritmos O(n²) - cuadráticos
echo -e "${YELLOW}Algoritmos O(n²) - Cuadráticos${NC}"
for algo in burbuja insercion seleccion; do
  echo "Procesando $algo..."
  > "$DATOS_DIR/${algo}.csv"
  
  for n in 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 110000 120000 130000 140000 150000 160000 170000 180000 190000 200000 210000 220000 230000 240000 250000; do
    timeout 120 "$BIN_DIR/$algo" $n >> "$DATOS_DIR/${algo}.csv" 2>/dev/null || echo "Timeout en n=$n"
  done
  
  echo "  ✓ ${algo}.csv generado ($(wc -l < "$DATOS_DIR/${algo}.csv") líneas)"
done

echo

# Algoritmos O(n log n)
echo -e "${YELLOW}Algoritmos O(n log n)${NC}"
for algo in mergesort quicksort; do
  echo "Procesando $algo..."
  > "$DATOS_DIR/${algo}.csv"
  
  for n in 200000 400000 600000 800000 1000000 1200000 1400000 1600000 1800000 2000000 2200000 2400000 2600000 2800000 3000000 3200000 3400000 3600000 3800000 4000000 4200000 4400000 4600000 4800000 5000000; do
    timeout 120 "$BIN_DIR/$algo" $n >> "$DATOS_DIR/${algo}.csv" 2>/dev/null || echo "Timeout en n=$n"
  done
  
  echo "  ✓ ${algo}.csv generado ($(wc -l < "$DATOS_DIR/${algo}.csv") líneas)"
done

echo

# Algoritmos O(n³) - cúbicos
echo -e "${YELLOW}Algoritmos O(n³) - Cúbicos${NC}"
for algo in floyd dijkstra-iterado; do
  echo "Procesando $algo..."
  > "$DATOS_DIR/${algo}.csv"
  
  for n in 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200 2300 2400 2500; do
    timeout 120 "$BIN_DIR/$algo" $n >> "$DATOS_DIR/${algo}.csv" 2>/dev/null || echo "Timeout en n=$n"
  done
  
  echo "  ✓ ${algo}.csv generado ($(wc -l < "$DATOS_DIR/${algo}.csv") líneas)"
done

echo

# Fibonacci - exponencial
echo -e "${YELLOW}Fibonacci - Exponencial${NC}"
echo "Procesando fibonacci..."
> "$DATOS_DIR/fibonacci.csv"

for n in 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 42 44 46 48 50; do
  # Ejecutar 3 veces y promediar
  total=0
  for i in {1..3}; do
    resultado=$("$BIN_DIR/fibonacci" $n 2>/dev/null | grep "^$n," | cut -d',' -f2)
    total=$(echo "$total + $resultado" | bc -l)
  done
  promedio=$(echo "scale=10; $total / 3" | bc -l)
  echo "$n,$promedio" >> "$DATOS_DIR/fibonacci.csv"
done

echo "  ✓ fibonacci.csv generado ($(wc -l < "$DATOS_DIR/fibonacci.csv") líneas)"

echo

# Hanoi - exponencial iterativo
echo -e "${YELLOW}Hanoi - Exponencial Iterativo${NC}"
echo "Procesando hanoi..."
> "$DATOS_DIR/hanoi.csv"

for n in 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33; do
  timeout 120 "$BIN_DIR/hanoi" $n >> "$DATOS_DIR/hanoi.csv" 2>/dev/null || echo "Timeout en n=$n"
done

echo "  ✓ hanoi.csv generado ($(wc -l < "$DATOS_DIR/hanoi.csv") líneas)"

echo
echo -e "${GREEN}=== Proceso Completado ===${NC}"
echo "Datos guardados en: $DATOS_DIR"
echo
echo "Archivos generados:"
ls -lh "$DATOS_DIR"/*.csv 2>/dev/null | awk '{print "  - " $9 " (" $5 ")"}'
