# Práctica 3: Algoritmos Voraces - Problema 2: Cámaras de Vigilancia

## Descripción del problema
El objetivo de este problema es buscar la mejor solución para garantizar la seguridad de un complejo formado por intersecciones y pasillos.
Una cámara colocada en una intersección es capaz de vigilar todos los pasillos que llegan a ella.
Se busca una solución óptima, es decir, que minimice el número de cámaras instaladas.

## Partes del problema
Para poder analizar mejor el problema, lo hemos dividido en dos soluciones muy diferentes entre sí:

1. Algoritmo de fuerza bruta
    - Garantiza encontrar la solución óptima absoluta evaluando todo el espacio.
    - Puede llegar a ser muy lento si el tamaño del problema es grande.
    
2. Algoritmo voraz (Greedy)
    - No garantiza la solución óptima.
    - Es mucho más rápido que el algoritmo de fuerza bruta.
    - Garantiza una solución "suficientemente" buena (muy cercana a la óptima).

## Algoritmo de fuerza bruta
El algoritmo de fuerza bruta se basa en la idea de probar de forma recursiva todas las combinaciones posibles de colocar cámaras o no en las intersecciones.

Sigue el siguiente esquema:
1. Se decide si en la intersección actual se coloca una cámara (1) o no (0).
2. Se llama recursivamente a la siguiente intersección para ambas decisiones.
3. Cuando se han tomado decisiones para todas las intersecciones (caso base de la recursión), se comprueba mediante la matriz si la combinación actual es válida (no deja pasillos sin vigilar).
4. Si es válida y mejora la mejor solución encontrada hasta el momento, se guarda.

## Análisis de eficiencia teórica del algoritmo de fuerza bruta
El algoritmo de fuerza bruta divide el problema de tomar $n$ decisiones en 2 subproblemas de tamaño $n-1$, sumándole un trabajo constante en cada nodo recursivo. El tamaño de la entrada que decrece lo llamaremos $m$, donde la recursión empieza en $m = n$ intersecciones restantes por evaluar.
La ecuación en recurrencia que modela el número de nodos del árbol recursivo es:

$T(m) = 2T(m-1) + c$

Para resolverla aplicamos la **ecuación característica**:
1. Planteamos la recurrencia como: $T(m) - 2T(m-1) = c$
2. Buscamos la solución a la parte homogénea ($T^{(h)}(m) - 2T^{(h)}(m-1) = 0$). Su polinomio característico es $r - 2 = 0$, cuya raíz es $r = 2$.
   Por tanto, $T^{(h)}(m) = c_1 \cdot 2^m$.
3. Buscamos una solución particular para la constante $c$. Como 1 no es raíz de la homogénea, proponemos $T^{(p)}(m) = c_2$.
   Sustituyendo: $c_2 - 2c_2 = c \implies c_2 = -c$.
4. La solución general de la recurrencia es: 
   $T(m) = c_1 \cdot 2^m - c$

Vemos que el árbol de llamadas recursivas crece en $\mathcal{O}(2^n)$. 
Sin embargo, al llegar a las $2^n$ hojas del árbol (cuando ya se han tomado las decisiones para los $n$ nodos, $m=0$), se ejecuta la función de comprobación `Factiblefb()`. Esta función recorre la mitad superior de la matriz de adyacencia buscando aristas y comprobando si están cubiertas, lo cual tiene un coste de $\mathcal{O}(n^2)$.

Como este coste final se ejecuta $2^n$ veces, la **complejidad temporal final del algoritmo es $\mathcal{O}(n^2 \cdot 2^n)$**.

## Algoritmo Voraz (Greedy)
El algoritmo voraz se basa en la idea de ir eligiendo en cada iteración la intersección que cubra la mayor cantidad de pasillos ciegos. Es decir, elige el nodo que posea el mayor grado en la matriz restante.

Sigue el siguiente esquema:
1. Se crea una matriz auxiliar `aux` que se copiará, para no perder la información original.
2. Comienza un bucle que se repite mientras sigan quedando pasillos sin vigilar en la matriz.
3. Se recorre la matriz para determinar qué intersección tiene más conexiones (grado).
4. Se guarda esa intersección como parte de la solución.
5. Se marcan como "vigilados" todos los pasillos de esa intersección (borrando su respectiva fila y columna de la matriz `aux`).

## Análisis de eficiencia teórica del algoritmo voraz
Dentro del código, la función principal `greedy()` consta de un bucle `while` y tres operaciones internas:

1. **Bucle `while`**: En el peor de los casos, colocamos una cámara por intersección, por lo que el bucle itera como máximo $n$ veces.
2. **`quedanPasillosSinVigilar(aux)`**: Escanea toda la matriz de tamaño $n \times n$ buscando pasillos. Coste: $\mathcal{O}(n^2)$.
3. **`verticeMayorGrado(aux)`**: Recorre la matriz entera de tamaño $n \times n$ contabilizando cuántas conexiones tiene cada vértice. Coste: $\mathcal{O}(n^2)$.
4. **`marcarPasillosVigilados(aux, índice)`**: Pone a $0$ todos los elementos de la fila y la columna del vértice seleccionado. Coste: $\mathcal{O}(n)$.

Coste total de una iteración: $\mathcal{O}(n^2) + \mathcal{O}(n^2) + \mathcal{O}(n) = \mathcal{O}(n^2)$.
Multiplicando esto por el número de iteraciones (acotado por $n$), la **complejidad temporal del algoritmo voraz es $\mathcal{O}(n^3)$**.

## Análisis Empírico: Voraz vs Fuerza Bruta
Para comprobar la viabilidad del algoritmo Voraz y entender cómo difiere de la solución Óptima obtenida por Fuerza Bruta, es necesario ponerlos frente a frente. 
Sabemos que la Fuerza Bruta crece de manera exponencial $\mathcal{O}(n^2 \cdot 2^n)$, lo que implica que llega un tamaño del problema ($n \approx 30$) donde el algoritmo colapsa y no puede darnos un resultado en un tiempo razonable. El Voraz crece polinómicamente $\mathcal{O}(n^3)$, siendo capaz de manejar recintos con miles de pasillos en muy pocos segundos.

Para ilustrar tanto la diferencia de tiempo como el margen de error de la solución aportada por el algoritmo Greedy, hemos recogido una serie de mediciones reales que se plasman en la siguiente sección.

## Tabla de resultados
Para obtener los resultados, se ha compilado el código original en C++ (`camaras-fb.cpp`) asegurándonos de aplicar los flags de optimización del compilador. Se ha ejecutado el programa utilizando el generador automático de grafos que incorpora el código para varios valores de tamaño del problema (desde $n=20$ intersecciones hasta $n=28$). 

En cada ejecución:
- Se generó una matriz aleatoria bajo una misma probabilidad de generar aristas.
- Se ha medido y tabulado el tiempo y la cantidad de cámaras resultantes al ejecutar la función `greedy()`.
- Se ha medido y tabulado el tiempo y la cantidad de cámaras resultantes al ejecutar la función `fb_recursivo(0)`.

| Intersecciones ($n$) | Cámaras (Voraz) | Cámaras (Fuerza Bruta) | Tiempo Voraz (s) | Tiempo Fuerza Bruta (s) |
|:---:|:---:|:---:|:---:|:---:|
| **20** | 12 | 11 | 0.000089 | 0.1118 |
| **22** | 14 | 14 | 0.000134 | 0.4398 |
| **24** | 17 | 16 | 0.000228 | 1.8788 |
| **25** | 18 | 18 | 0.000183 | 3.4564 |
| **26** | 18 | 17 | 0.000189 | 7.1207 |
| **27** | 18 | 18 | 0.000236 | 15.4157 |
| **28** | 21 | 20 | 0.000511 | 28.7832 |

Observando la tabla, se confirma que:
1. El algoritmo Voraz acierta y da la solución óptima algunas veces, pero frecuentemente añade entre 1 y 2 cámaras adicionales en grafos tan complejos.
2. La Fuerza Bruta para $n=28$ tarda más de 6 segundos completos. El Voraz tarda 0.000047 segundos. Es una prueba empírica contundente de la necesidad y bondad de utilizar algoritmos voraces para problemas NP-Completos de la vida real.

Para tener mas muestras, veámos los resultados del ordenador de Fran:

| Intersecciones ($n$) | Cámaras (Voraz) | Cámaras (Fuerza Bruta) | Tiempo Voraz (s) | Tiempo Fuerza Bruta (s) |
|:---:|:---:|:---:|:---:|:---:|
| **20** | 11 | 11 | 0.000221 | 0.2004 |
| **22** | 15 | 15 | 0.000371 | 0.5047 |
| **24** | 16 | 16 | 0.000420 | 1.9274 |
| **25** | 16 | 16 | 0.000376 | 3.8893 |
| **26** | 18 | 18 | 0.000515 | 7.5035 |
| **27** | 19 | 18 | 0.000563 | 16.850 |
| **28** | 19 | 18 | 0.000552 | 32.495 |

Como podemos ver, para tamaños n = 27 y n = 28 el algoritmo voraz devuelve 19 cámaras, mientras que el óptimo real es 18. Esto prueba que la heurística no siempre es óptima. 
Podemos ver un crecimiento exponencial del tiempo, lo que coincide con la estimación de la práctica(30s para n = 28).
El tiempo de ejecución en el algoritmo Voraz se mantiene plano en el orden de microsegundos demostrando una eficiencia extrema.
Por tanto, concluimos que dicho algoritmo sacrifica una fracción mínima de precisión a cambio de una reduccion extrema en el tiempo de ejecución.

## Optimización para arboles (Greedy) - Opcional
El algoritmo voraz optimizado para arboles busca las hojas (nodos con una única conexión) y coloca una camara en el nodo padre de esa forma te aseguras de cubrir los dos nodos mencionados y los hermanos del primer nodo y el padre del segundo.

Sigue el siguiente esquema:
1. Se crea una matriz auxiliar `aux` que se copiará, para no perder la información original.
2. Comienza un bucle que se repite mientras sigan quedando pasillos sin vigilar en la matriz.
3. Se recorre la matriz para buscar una hoja y se obtiene su nodo padre.
4. Se guarda esa intersección como parte de la solución.
5. Se marcan como "vigilados" todos los pasillos de esa intersección (borrando su respectiva fila y columna de la matriz `aux`).

### Análisis de eficiencia teórica (Voraz en Árboles)
Dentro de la función `greedyArbol()`, observamos el siguiente comportamiento:
1. **Bucle `while`**: Al igual que el algoritmo voraz general, iterará como máximo $n$ veces.
2. **`quedanPasillosSinVigilar(aux)`**: Comprueba toda la matriz. Coste: $\mathcal{O}(n^2)$.
3. **`BuscamosHoja(aux)`**: Recorre la matriz contabilizando las conexiones (grado) de cada vértice. Devuelve el padre cuando encuentra un nodo con grado 1. En el peor caso, recorre toda la matriz. Coste: $\mathcal{O}(n^2)$.
4. **`marcarPasillosVigilados(aux, padre_hoja)`**: Pone a $0$ todos los elementos de la fila y columna del vértice seleccionado. Coste: $\mathcal{O}(n)$.

El coste de cada iteración del bucle es $\mathcal{O}(n^2) + \mathcal{O}(n^2) + \mathcal{O}(n) = \mathcal{O}(n^2)$. 
Dado que el bucle se ejecuta un máximo de $n$ veces, la **complejidad temporal final sigue siendo $\mathcal{O}(n^3)$**, al igual que el voraz genérico. Sin embargo, en la práctica suele ser ligeramente más rápido porque `BuscamosHoja` se detiene tan pronto como encuentra la primera hoja, no necesitando evaluar el grafo entero a diferencia de `verticeMayorGrado`.

### Análisis empírico
Se ha utilizado el generador de árboles implementado en el código para comparar el rendimiento de las tres variantes del algoritmo (Fuerza Bruta, Voraz Genérico y Voraz Específico para Árboles).

| Intersecciones ($n$) | Cámaras (Voraz Genérico) | Cámaras (Voraz Árbol) | Cámaras (Fuerza Bruta) | Tiempo Voraz Genérico (s) | Tiempo Voraz Árbol (s) | Tiempo FB (s) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **20** | 8 | 8 | 8 | 0.000017 | 0.000007 | 0.023677 |
| **22** | 10 | 9 | 9 | 0.000027 | 0.000007 | 0.092646 |
| **24** | 11 | 10 | 10 | 0.000043 | 0.000010 | 0.500536 |
| **25** | 10 | 10 | 10 | 0.000027 | 0.000009 | 1.795116 |
| **26** | 11 | 11 | 11 | 0.000036 | 0.000011 | 3.198420 |
| **27** | 12 | 12 | 12 | 0.000037 | 0.000013 | 6.182430 |
| **28** | 10 | 10 | 10 | 0.000026 | 0.000011 | 10.649700 |

Como se puede observar en la tabla:
1. El **Algoritmo Voraz Específico para Árboles encuentra sistemáticamente la solución óptima absoluta**, coincidiendo exactamente con la aportada por la fuerza bruta en todos los casos evaluados (incluidos aquellos donde el Voraz genérico falló añadiendo más cámaras, como en $n=22$ y $n=24$).
2. Respecto a los tiempos de ejecución, la **variante adaptada a árboles es consistentemente más rápida** que la variante voraz genérica (entre el doble y el triple de velocidad), debido a la optimización mencionada previamente de romper el bucle anticipadamente al encontrar hojas.
