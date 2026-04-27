set terminal pngcairo size 800,600 enhanced font 'Verdana,10'

# Grafica Tiempos General
set output 'grafica_tiempos_general.png'
set title 'Comparación de Tiempos: Voraz vs Fuerza Bruta (Grafos Generales)'
set xlabel 'Número de Intersecciones (n)'
set ylabel 'Tiempo de ejecución (s)'
set grid
set key left top
plot 'tiempos_general.dat' using 1:3 with linespoints lw 2 pt 7 title 'Fuerza Bruta', \
     'tiempos_general.dat' using 1:2 with linespoints lw 2 pt 7 title 'Voraz'

# Grafica Tiempos Arboles
set output 'grafica_tiempos_arbol.png'
set title 'Comparación de Tiempos: Voraz vs Voraz Árbol vs Fuerza Bruta (Árboles)'
plot 'tiempos_arbol.dat' using 1:4 with linespoints lw 2 pt 7 title 'Fuerza Bruta', \
     'tiempos_arbol.dat' using 1:2 with linespoints lw 2 pt 7 title 'Voraz Genérico', \
     'tiempos_arbol.dat' using 1:3 with linespoints lw 2 pt 7 title 'Voraz Árbol'

# Grafica Tiempos Voraces (Solo Voraces) Arboles
set output 'grafica_tiempos_voraces_arbol.png'
set title 'Comparación de Tiempos: Voraz Genérico vs Voraz Árbol'
plot 'tiempos_arbol.dat' using 1:2 with linespoints lw 2 pt 7 title 'Voraz Genérico', \
     'tiempos_arbol.dat' using 1:3 with linespoints lw 2 pt 7 title 'Voraz Árbol'

# Grafica Camaras General
set output 'grafica_camaras_general.png'
set title 'Comparación de Cámaras: Voraz vs Fuerza Bruta (Grafos Generales)'
set xlabel 'Número de Intersecciones (n)'
set ylabel 'Número de Cámaras'
set grid
set key left top
plot 'camaras_general.dat' using 1:3 with linespoints lw 2 pt 7 title 'Fuerza Bruta (Óptimo)', \
     'camaras_general.dat' using 1:2 with linespoints lw 2 pt 7 title 'Voraz'

# Grafica Camaras Arboles
set output 'grafica_camaras_arbol.png'
set title 'Comparación de Cámaras: Voraz vs Voraz Árbol vs Fuerza Bruta (Árboles)'
plot 'camaras_arbol.dat' using 1:4 with linespoints lw 2 pt 7 title 'Fuerza Bruta (Óptimo)', \
     'camaras_arbol.dat' using 1:2 with linespoints lw 2 pt 7 title 'Voraz Genérico', \
     'camaras_arbol.dat' using 1:3 with linespoints lw 2 pt 7 title 'Voraz Árbol'
