# Análisis Teórico

El enfoque teórico nos permite determinar la eficiencia de un algoritmo sin tener que depender de una máquina o lenguje.
Para ello, contamos expresaremos el tiempo de ejecución T(n) en función del tamaño de entrada n.

## Algoritmo Obvio

Este algoritmo usa un bucle for que recorre el vector desde i=0 hasta n-1

- El mejor caso, será por tanto, cuando el elemento que falta es el 0. Se cumple la condición i != vec[i] y el algoritmo termina. Su coste temporal es constante, O(n)

- El peor caso ocurrirá cuando el elemento que falta es el último(o cuando no falta ningún elemento y devuelve vec.size()). El bucle for se ejecutará n veces, por lo tanto su eficiencia en el peor caso es lineal, O(n)

## Algoritmo Divide y Vencerás

// Aquí 0 representa a Theta
// Y esta O representa a Omega

Este algoritmo divide el vector a la mitad en cada llamada recursiva y solo explora una de los 2 mitades.

- La función divide el problema de tamaño n en un subproblema de tamaño n/2 y realiza un trabajo de combinación y división del vector constante O(1). Esto nos deja con la siguiente recurrencia.

T(n) = T(n/2) + c

Usando la fórmula maestra -> T(n) = aT(n/b) + cn^k
Podemos resolver la recurrencia:

a = 1 (número de subproblemas)
b = 2 (factor de división)
k = 0 (el trabajo es constante)

Como a = b^k -> 1 = 2^0, aplicamos el segundo caso del Teorema Maestro

T(n) = 0(n^k*log(n)) = 0(n^0*log(n)) = 0(log(n))

Por tanto el tiempo de ejecución es logarítmico, O(log(n)), el algoritmo 'Divide y Vencerás' es más eficiente que el 'Algoritmo Obvio'

# Análisis Empírico
El enfoque empírico consiste en implementar los algoritmos y medir sus tiempo de ejecución real para diferentes tamaños de entradas.

// Falta esta parte
