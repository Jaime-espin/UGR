# graficar.gnuplot
set terminal png size 800,600
set output 'imagenes/comparacion.png'

set xlabel 'Size (n)'
set ylabel 'Time (s)'
set title 'Comparación de Algoritmos'
set logscale x
set logscale y
set grid

plot 'data/algoritmoBasico.dat' using 1:2 with linespoints title 'Algoritmo Básico', \
     'data/algoritmoDivideVenceras.dat' using 1:2 with linespoints title 'Divide y Venceras'