#!/bin/bash

echo "======================================================="
echo " INICIANDO BATERÍA DE PRUEBAS - AGENTE ESTUDIANTE"
echo "======================================================="

# --- FASE 1: STATUS (Motor base en 3x3) ---
echo -e "\n>>> FASE 1: STATUS (Fuerza Bruta 3x3) <<<"

echo "Prueba 1.1: Status (P1) vs Status (P2)"
./n_en_raya -p1 status -p2 status -f 3 -c 3 -n 3 -nogui

echo "Prueba 1.2: Status (P1) vs Aleatorio (P2)"
./n_en_raya -p1 status -p2 aleatorio -f 3 -c 3 -n 3 -nogui

echo "Prueba 1.3: Aleatorio (P1) vs Status (P2) -> ¡Invertido!"
./n_en_raya -p1 aleatorio -p2 status -f 3 -c 3 -n 3 -nogui


# --- FASE 2: MINIMAX (Profundidad 4 en 9x9) ---
# Usamos tu heuristica1 (índice 1)
echo -e "\n>>> FASE 2: MINIMAX (Prof. 4, Heurística 1) <<<"

echo "Prueba 2.1: Minimax (P1) vs Ninja 1 (P2)"
./n_en_raya -p1 minimax -id1 1 -p2 ninja1 -d 4 -nogui

echo "Prueba 2.2: Ninja 1 (P1) vs Minimax (P2) -> ¡Invertido!"
# Fíjate que aquí usamos -id2 1 porque ahora Minimax es el Jugador 2
./n_en_raya -p1 ninja1 -p2 minimax -id2 1 -d 4 -nogui


# --- FASE 3: ALFA-BETA (Profundidad 7 en 9x9) ---
# El reto real de la competición
echo -e "\n>>> FASE 3: PODA ALFA-BETA (Prof. 7, Heurística 1) <<<"

echo "Prueba 3.1: Inteligente (P1) vs Ninja 1 (P2)"
./n_en_raya -p1 inteligente -id1 1 -p2 ninja1 -d 7 -nogui

echo "Prueba 3.2: Ninja 1 (P1) vs Inteligente (P2) -> ¡Invertido!"
./n_en_raya -p1 ninja1 -p2 inteligente -id2 1 -d 7 -nogui

# Descomenta estas líneas cuando quieras probar contra los Ninjas superiores
# echo "Prueba 3.3: Inteligente (P1) vs Ninja 2 (P2)"
# ./n_en_raya -p1 inteligente -id1 1 -p2 ninja2 -d 7 -nogui

# echo "Prueba 3.4: Ninja 2 (P1) vs Inteligente (P2)"
# ./n_en_raya -p1 ninja2 -p2 inteligente -id2 1 -d 7 -nogui

echo -e "\n======================================================="
echo " BATERÍA DE PRUEBAS FINALIZADA"
echo "======================================================="