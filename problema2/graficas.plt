# Configuración general
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set datafile separator ","
set key left top
set grid

# 1. Gráfica de Tiempo vs n
set output 'tiempo_ejecucion.png'
set title 'Tiempo de Ejecucion vs Tamano del Problema (n)'
set xlabel 'Numero de intersecciones (n)'
set ylabel 'Tiempo (segundos)'
set logscale y
plot 'resultados_backtracking.csv' skip 1 using 1:(strcol(2) eq "aleatorio" ? $5 : 1/0) with linespoints pt 7 title "Aleatorio", \
     'resultados_backtracking.csv' skip 1 using 1:(strcol(2) eq "arbol" ? $5 : 1/0) with linespoints pt 5 title "Arbol"

# 2. Gráfica de Nodos Generados vs n
set output 'nodos_generados.png'
set title 'Nodos Generados vs Tamano del Problema (n)'
set ylabel 'Cantidad de Nodos Generados'
plot 'resultados_backtracking.csv' skip 1 using 1:(strcol(2) eq "aleatorio" ? $3 : 1/0) with linespoints pt 7 title "Aleatorio", \
     'resultados_backtracking.csv' skip 1 using 1:(strcol(2) eq "arbol" ? $3 : 1/0) with linespoints pt 5 title "Arbol"

# 3. Gráfica de Eficacia de Poda vs n
set output 'eficacia_poda.png'
set title 'Eficacia de la Poda (Nodos Podados / Nodos Generados)'
set ylabel 'Ratio de Poda'
unset logscale y
set yrange [0:1.1]
plot 'resultados_backtracking.csv' skip 1 using 1:(strcol(2) eq "aleatorio" ? ($3>0 ? $4/$3 : 0) : 1/0) with linespoints pt 7 title "Aleatorio", \
     'resultados_backtracking.csv' skip 1 using 1:(strcol(2) eq "arbol" ? ($3>0 ? $4/$3 : 0) : 1/0) with linespoints pt 5 title "Arbol"