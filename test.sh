#!/bin/bash

# --- VALIDACIÓN DEL COMANDO ---
if [ -z "$1" ]; then
    echo "❌ ERROR: No has indicado contra qué Ninja quieres jugar."
    echo "💡 Uso correcto: ./testNinjaEntero.sh <numero_del_ninja>"
    exit 1
fi

NINJA="ninja$1"
TIEMPO_MAX=200
LOG_FILE="log_memoria_${NINJA}.txt"

echo "=========================================================="
echo " 🚀 BATERÍA DE PRUEBAS PARA TABLAS DE LA MEMORIA "
echo " Rival: $NINJA "
echo "=========================================================="
echo "=== LOG COMPLETO DE PRUEBAS CONTRA $NINJA ===" > "$LOG_FILE"

evaluar_partida() {
    local exit_code=$1
    local output="$2"
    local mi_jugador=$3 
    
    if echo "$output" | grep -q -i -E "error en respuesta del servidor|timed out after"; then
        echo "⚠️ ERROR/TIMEOUT"
    elif [ $exit_code -eq 124 ]; then 
        echo "⏳ TIMEOUT (Límite superado)"
    elif echo "$output" | grep -q "¡Gana el Jugador ${mi_jugador}!"; then 
        echo "✅ VICTORIA"
    elif echo "$output" | grep -q "¡Gana el Jugador"; then 
        echo "❌ DERROTA"
    else 
        echo "🤝 EMPATE"
    fi
}

# ---------------------------------------------------------
# FASE 0: VERIFICACIÓN TÉCNICA (Solo se ejecuta con el ninja 1)
# ---------------------------------------------------------
if [ "$1" == "1" ]; then
    echo -e "\n>> [TEST TÉCNICO 1] STATUS en 3x3..."
    echo -e "\n*** STATUS 3x3 ***" >> "$LOG_FILE"
    OUTPUT=$(timeout 15 ./n_en_raya -p1 status -p2 aleatorio -f 3 -c 3 -n 3 -nogui 2>&1)
    echo "$OUTPUT" >> "$LOG_FILE"
    echo "Hecho. Revisa el log."

    echo -e "\n>> [TEST TÉCNICO 2] Minimax vs Alfa-Beta (Profundidad = 4)..."
    echo -e "\n*** MINIMAX (d=4, id=0) ***" >> "$LOG_FILE"
    OUTPUT_M=$(timeout $TIEMPO_MAX ./n_en_raya -p1 minimax -id1 0 -p2 aleatorio -f 9 -c 9 -n 5 -d 4 -nogui 2>&1)
    echo "$OUTPUT_M" >> "$LOG_FILE"
    
    echo -e "\n*** ALFA-BETA (d=4, id=0) ***" >> "$LOG_FILE"
    OUTPUT_AB=$(timeout $TIEMPO_MAX ./n_en_raya -p1 inteligente -id1 0 -p2 aleatorio -f 9 -c 9 -n 5 -d 4 -nogui 2>&1)
    echo "$OUTPUT_AB" >> "$LOG_FILE"
    echo "Hecho. Revisa el log para comparar nodos."
fi

# ---------------------------------------------------------
# FASE 1: TABLA "COMO JUGADOR 1" (Tú vs Ninja, d=7)
# ---------------------------------------------------------
echo -n -e "\n>> [TABLA 4.1] ALFA-BETA (J1) vs $NINJA (J2) [d=7]... "
echo -e "\n\n*** TABLA 1: INTELIGENTE (J1) vs $NINJA (J2) [d=7] ***" >> "$LOG_FILE"

OUTPUT=$(timeout $TIEMPO_MAX ./n_en_raya -p1 inteligente -id1 1 -p2 $NINJA -d 7 -f 9 -c 9 -n 5 -nogui 2>&1)
EXIT_CODE=$?
echo "$OUTPUT" >> "$LOG_FILE"
RES=$(evaluar_partida $EXIT_CODE "$OUTPUT" 1)
echo "$RES"

# ---------------------------------------------------------
# FASE 2: TABLA "COMO JUGADOR 2" (Ninja vs Tú, d=7)
# ---------------------------------------------------------
echo -n ">> [TABLA 4.2] $NINJA (J1) vs ALFA-BETA (J2) [d=7]... "
echo -e "\n\n*** TABLA 2: $NINJA (J1) vs INTELIGENTE (J2) [d=7] ***" >> "$LOG_FILE"

OUTPUT=$(timeout $TIEMPO_MAX ./n_en_raya -p1 $NINJA -p2 inteligente -id2 1 -d 7 -f 9 -c 9 -n 5 -nogui 2>&1)
EXIT_CODE=$?
echo "$OUTPUT" >> "$LOG_FILE"
RES=$(evaluar_partida $EXIT_CODE "$OUTPUT" 2)
echo "$RES"

echo -e "\n=========================================================="
echo " 📁 Revisa el archivo: $LOG_FILE para ver los nodos visitados."
echo "=========================================================="