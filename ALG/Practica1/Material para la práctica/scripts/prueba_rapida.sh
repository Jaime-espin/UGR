#!/bin/bash

# Script de prueba rápida - verifica que todos los algoritmos compilen y ejecuten

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

SRC_DIR="$(dirname "$0")/../src"
BIN_DIR="$(dirname "$0")/../bin"

mkdir -p "$BIN_DIR"

echo -e "${GREEN}=== Prueba Rápida de Algoritmos ===${NC}"
echo

# Algoritmos a probar
declare -A ALGORITMOS=(
  ["burbuja"]="50000"
  ["insercion"]="50000"
  ["seleccion"]="50000"
  ["mergesort"]="500000"
  ["quicksort"]="500000"
  ["floyd"]="150"
  ["dijkstra-iterado"]="150"
  ["fibonacci"]="40"
  ["hanoi"]="25"
)

echo "Compilando y probando cada algoritmo..."
echo

for algo in "${!ALGORITMOS[@]}"; do
  n=${ALGORITMOS[$algo]}
  
  echo -n "[$algo] n=$n ... "
  
  # Compilar
  g++ "$SRC_DIR/${algo}.cpp" -o "$BIN_DIR/${algo}" 2>/dev/null
  
  # Ejecutar
  resultado=$("$BIN_DIR/${algo}" $n 2>/dev/null)
  
  if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ $resultado${NC}"
  else
    echo -e "${RED}✗ ERROR${NC}"
  fi
done

echo
echo -e "${GREEN}=== Prueba Completada ===${NC}"
