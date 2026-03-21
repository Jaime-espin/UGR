#!/bin/bash
# GUÍA DE EJECUCIÓN EN WINDOWS CON GIT BASH
# ==========================================

# 1. INSTALAR GIT BASH (si no lo tienes)
#    Descargar desde: https://gitforwindows.org/
#    Instalar con opciones por defecto

# 2. INSTALAR MINGW-W64 (si no lo tienes)
#    Descargar desde: https://www.mingw-w64.org/
#    O si ya tienes MinGW instalado, asegúrate que g++ está en el PATH

# 3. VERIFICAR QUE g++ ESTÁ DISPONIBLE
# Abre Git Bash y ejecuta:
#    g++ --version

# 4. EJECUTAR EL SCRIPT DE GENERACIÓN

# Opción A: Desde Git Bash (Recomendado)
# ========================================
# 1. Abre Git Bash
# 2. Navega a la carpeta del proyecto:
#    cd "c:\Users\JaimeEspin\Desktop\02Area\01Universidad\01Apuntes\ALG\Práctica 1\Material para la práctica"
# 3. Dale permiso al script:
#    chmod +x generar_datos.sh
# 4. Ejecuta el script:
#    ./generar_datos.sh
# 5. Espera a que termine (puede tomar varios minutos)
# 6. Los archivos CSV aparecerán en la carpeta

# Opción B: Abre Git Bash Aqui (Más fácil)
# ==========================================
# 1. Abre Explorer y navega a la carpeta del proyecto
# 2. Presiona Shift + Click derecho → "Git Bash Here"
# 3. En Git Bash, ejecuta:
#    chmod +x generar_datos.sh
#    ./generar_datos.sh

# Opción C: Compilar y ejecutar un algoritmo individual
# ======================================================
# En Git Bash:
#    g++ -O2 -o burbuja_bin burbuja.cpp
#    ./burbuja_bin 100000

# 5. ARCHIVOS GENERADOS

# Después de ejecutar el script, tendrás estos archivos:
# - burbuja_resultados.csv
# - insercion_resultados.csv
# - seleccion_resultados.csv
# - mergesort_resultados.csv
# - quicksort_resultados.csv
# - floyd_resultados.csv
# - dijkstra_resultados.csv
# - fibonacci_resultados.csv
# - hanoi_resultados.csv

# 6. IMPORTAR EN EXCEL

# Método 1: Copiar y pegar
# =======================
# 1. Abre el archivo CSV con Notepad (o un editor de texto)
# 2. Selecciona todo (Ctrl+A) y copia (Ctrl+C)
# 3. Abre Excel
# 4. Pega en una celda (Ctrl+V)
# 5. Excel reconocerá automáticamente el formato CSV

# Método 2: Abrir directamente
# =============================
# 1. En Excel: Archivo → Abrir
# 2. Selecciona el archivo CSV
# 3. Excel te pedirá seleccionar el delimitador
# 4. Selecciona "Coma" como delimitador
# 5. Haz clic en Aceptar

# Método 3: Importar datos (más control)
# =======================================
# 1. En Excel: Pestaña "Datos" → Obtener datos externos → Desde texto
# 2. Selecciona el archivo CSV
# 3. En el asistente:
#    - Step 1: Selecciona "Delimitado"
#    - Step 2: Marca "Coma" como delimitador
#    - Step 3: Revisa que las columnas se importan correctamente
# 4. Haz clic en "Finalizar"

# 7. CREAR GRÁFICOS EN EXCEL

# Para análisis comparativo:
# 1. Selecciona los datos (Columna de tamaños + columna de tiempos)
# 2. Menú: Insertar → Gráfico
# 3. Elige "Gráfico de líneas"
# 4. Personaliza títulos, ejes, etiquetas

# Para comparar múltiples algoritmos:
# 1. Combina datos de varios CSV en una sola hoja
# 2. Usa gráficos de líneas con múltiples series

# 8. SOLUCIONAR PROBLEMAS

# Problema: "generar_datos.sh: command not found"
# Solución: Asegúrate de estar en la carpeta correcta
#          y usa ./generar_datos.sh (con punto y barra)

# Problema: "g++: command not found"
# Solución: 
#   a) Instala MinGW-w64
#   b) Añade la carpeta bin al PATH de Windows
#   c) Reinicia Git Bash

# Problema: El script tarda mucho tiempo
# Solución: Es normal para rangos grandes (especialmente N log N)
#          Puedes interrumpir con Ctrl+C y revisar los CSV creados hasta ese momento

# Problema: Los CSV están vacíos o tienen solo encabezados
# Solución:
#   a) Verifica que los binarios se compilaron (busca los archivos *_bin)
#   b) Prueba compilar uno manualmente:
#      g++ -O2 -o test burbuja.cpp
#      ./test 100
#   c) Asegúrate que la salida es exactamente: "100,0.000123"

# 9. EJEMPLOS DE COMANDOS

# Compilar solo Burbuja
g++ -O2 -o burbuja_bin burbuja.cpp

# Ejecutar Burbuja con n=100000
./burbuja_bin 100000

# Compilar solo Mergesort
g++ -O2 -o mergesort_bin mergesort.cpp

# Ejecutar Mergesort múltiples veces con diferentes n
for n in 100000 200000 300000; do
  echo "Ejecutando Mergesort con n=$n"
  ./mergesort_bin $n
done

# Compilar todos sin usar el script
for file in burbuja insercion seleccion mergesort quicksort floyd dijkstra fibonacci hanoi; do
  g++ -O2 -o ${file}_bin ${file}.cpp
done

# 10. INFORMACIÓN DE VERSIONES

# Versiones recomendadas:
# - Git Bash: 2.30 o superior
# - g++: 5.0 o superior
# - MinGW-w64: versión reciente

# Verificar versión de g++:
g++ --version

# Verificar que estás en Git Bash (no cmd.exe):
echo $SHELL

# 11. EJECUTAR SCRIPT PASO A PASO (para depuración)

# Si algo falla, ejecuta los comandos manualmente:

# Compilar
g++ -O2 -o burbuja_bin burbuja.cpp

# Crear CSV con encabezado
echo "Tamaño,Tiempo" > burbuja_resultados.csv

# Ejecutar un ciclo pequeño
for n in 10000 20000; do
  ./burbuja_bin $n >> burbuja_resultados.csv
done

# Verificar resultado
cat burbuja_resultados.csv

# Si esto funciona, El script completo debería funcionar sin problemas.
