# graficar.gnuplot
set terminal png size 800,600
set output 'imagenes/algoritmoBasico.png'

set xlabel 'Size (n)'
set ylabel 'Time (s)'
set title 'Algoritmo Basico'

plot 'data/algoritmoBasico.dat' using 1:2 with lines title 'data'

set terminal png size 800,600
set output 'imagenes/algoritmoDivideVenceras.png'

set xlabel 'Size (n)'
set ylabel 'Time (s)'
set title 'Algoritmo Divide y Vencerás'
set logscale x
set logscale y

plot 'data/algoritmoDivideVenceras.dat' with lines title 'data'


set terminal png size 800,600
set output 'imagenes/algoritmoDivideVencerasAjustada.png'
f(x)=a0*log(x)
set title 'Algoritmo Divide y Vencerás Ajustado'
fit f(x) "data/algoritmoDivideVenceras.dat" via a0
plot 'data/algoritmoDivideVenceras.dat' with points title 'empirico', f(x) with lines title 'Curva Ajustada'