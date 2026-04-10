# graficar.gnuplot
set terminal png size 800,600
set output 'comparacion.png'

set xlabel 'Tamaño de entrada (n)'
set ylabel 'Tiempo (segundos)'
set title 'Comparación de Algoritmos'
set logscale x
set logscale y
set grid

plot 'data/algoritmoBasico.dat' using 1:2 with linespoints title 'Algoritmo Básico', \
     'data/algoritmoDivideVenceras.dat' using 1:2 with linespoints title 'Divide y Venceras', \
     9.89498e-09 * log(x) with lines title 'Fit: 9.89e-09*log(x)'