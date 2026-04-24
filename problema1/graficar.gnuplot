# graficar.gnuplot
set terminal png size 800,600
set output 'imagenes/algoritmoOptimo.png'

set xlabel 'Size (n)'
set ylabel 'Time (s)'
set title 'Algoritmo Óptimo'

plot 'data/algoritmoOptimo.dat' using 1:2 with lines title 'data'

set terminal png size 800,600
set output 'imagenes/algoritmoSuboptimo.png'

set xlabel 'Size (n)'
set ylabel 'Time (s)'
set title 'Algoritmo Subóptimo'
set logscale x
set logscale y

plot 'data/algoritmoSuboptimo.dat' with lines title 'data'

set terminal png size 800,600
set output 'imagenes/comparativa.png'

set xlabel 'Size (n)'
set ylabel 'Time (s)'
set title 'Comparativa'
set logscale x
set logscale y

plot 'data/algoritmoOptimo.dat' with lines title 'optimo', 'data/algoritmoSuboptimo.dat' with lines title 'suboptimo'

