# Problema 1

## Enunciado

"Eres un famoso explorador que ha encontrado el Santuario de la Niebla. El suelo de la cámara principal se derrumbó hace milenios, dejando solo una cuadrícula de $n \times n$ pilares de piedra emergiendo de un abismo sin fondo.
El objetivo es ir desde el Pilar de Entrada (posición (0, 0)) hasta el Pilar del Altar (posición (a, b)) para recuperar el  ́ıdolo sagrado.
No se puede saltar entre pilares (están demasiado lejos). Hay que usar las lianas antiguas que cuelgan del techo justo encima de cada pilar. Cada pilar en la posición $(i, j)$ tiene una liana con una longitud exacta, determinada por el valor de la matriz $m[i][j]$. Al agarrar la liana y dejarte llevar, la física del péndulo te transportar a exactamente esa cantidad de casillas en línea recta. Si estás en $(i, j)$ y la liana mide $k$, puedes elegir aterrizar en $(i + k, j), (i −k, j), (i, j + k) o (i, j −k).$ Si un balanceo te lleva fuera de los límites de la matriz (contra una pared o al vacío), esa dirección está prohibida. Una vez usada una liana, esta se rompe. No puedes volver a aterrizar en un pilar que ya has visitado en tu ruta actual."

## Representación

En este tipo de algoritmos es de suma importancia dejar claro como vamos a representar tanto el problema descrito como también dejar claro qué será para nosotros una solución. Por lo que en este apartado dejaremos constancia de nuestra representación, tanto del problema como de la solución.

### Representación del Problema

El problema es representado mediante una matriz bidimensional de $n \times n$, la cual la vamos a encapsular en una clase llamada ``Lianas``. Dentro de esta clase tendremos un ``vector<vector<int>>`` que representará dicha matriz, y en donde cada casilla ``(i,j)`` contiene un valor ``k`` que representa la longitud de la liana en dicha posición.

### Representación de la Solución (Estado)

Para modelar el estado de búsqueda hemos optado por encapsularlo en otra clase denominada ``EstadoCamino``, la cual contiene: 
- La coordenadas exactas del explorador en este momento ``(fila,columna)``.
- La ruta construida. Este concepto hace referencia a un vector de coordenadas que representa el orden secuencial de las coordenadas visitadas desde el punto de partida ``(0,0)`` hasta la posición actual ``(fila, columna)``. En la clase, este concepto está definido como ``vector<pair<int, int>> ruta``.
- Matriz de control. Es necesario que tengamos en todo momento constancia de qué pilares ya hemos incluido en nuestra ruta (ya hemos pasado por él). Por ello, hemos pensado en generar una matriz del mismo tamaño que el mapa ($n \times n$) de booleanos, por ello cada casilla ``(i,j)`` de esta matriz representará ``true`` si ya hemos visitado el pilar y ``false`` en caso contrario. Dentro de la clase, se representa como ``vector<vector<bool>> visitados;``.

Entonces, consideraremos que la solución será nuestra ruta construida cuando su último elemento sea exactamente la posición del altar ``(a,b)`` representando entonces la secuencia de coordenadas desde el inicio al altar.

## Restricciones del Problema

Para que un movimiento transite de un estado válido a otro debe cumplir un conjunto de reglas. Estas pueden ser explícitas o implícitas. A continuación mostraremos cuáles son las reglas a seguir para este problema.

### Restricciones Explícitas
Estas reglas son dictadas por el propio enunciado del problema, ya que hacen referencia a la física del problema. Entonces, nosotros hemos concluido las siguientes restricciones explícitas: 

- Dirección del movimiento: Al utilizar una liana y balancearnos, no se puede permitir cualquier tipo de movimiento con ella, sino que únicamente podemos realizar movimientos en línea recta (Arriba, Abajo, Izquierda y Derecha).
- Longitud exacta del salto: Si el explorador se encuentra en la posición ``(i, j)`` cuya longitud de la liana es ``k``, el aterrizaje debe de producirse exactamente a una distancia ``k`` desde el origen. Por lo tanto, los únicos destinos matemáticamente posibles son $(i+k, j)$, $(i-k, j)$, $(i, j+k)$ o $(i, j-k)$.

### Restricciones Implícitas
Por otro lado, las restricciones implícitas son aquellas condiciones lógicas que garantizan la coherencia y validez de los estados generados. Para asegurar la correcta ejecución de la búsqueda, en este problema debemos garantizar el cumplimiento de las siguientes dos reglas:

- Destino Correcto: El destino calculado tras el balanceo (supongamos que el destino es ``(destinoF, destinoC)``) debe ser una posición válida. Es decir, que el destino tiene que estar dentro de la matriz $n \times n$, por lo que se debe cumplir que $0 \le \text{destinoF} < n$ y $0 \le \text{destinoC} < n$. Si esto no se cumple, se considera un destino inválido (choque).
- Evitar Ciclos: Dado que las lianas se rompen tras su uso, no es posible regresar a un pilar ya visitado. Esto se traduce a que si el valor de nuestra matriz de control es ``true``, el movimiento se descarta automáticamente asegurándonos que la búsqueda sea finita.

## Árbol de Exploración
El árbol de búsqueda se va generando de forma dinámica en la búsqueda. Este árbol contiene los siguientes elementos: 
- Raíz: Representa el pilar de entrada, es decir la posición ``(0,0)``.
- Nodos: Cada nodo del árbol es una celda ``(i, j)`` alcanzada tras un balanceo. 
- Ramas / Hijos: Para cada uno de los nodos, pueden crearse hasta 4 hijos. Esto es debido a que solo podemos movernos en 4 direcciones diferentes (Abajo, Derecha, Izquierda, Arriba). En apartados siguientes aclararemos el por qué hemos elegido este orden de exploración en específico. 
- Hojas: Son estados donde no es posible realizar más movimientos válidos o donde se ha alcanzado el Pilar del Altar.

Como cada nodo interno del árbol puede generar hasta 4 hijos, el tamaño del árbol crece de forma exponencial. En el peor de los casos, la longitud máxima de una ruta (sin ciclos) en una matriz de $n \times n$ es $n^2$ casillas. Es decir, la complejidad espacial y temporal teórica es de órden $\mathcal{O}(4^{n^2})$. Por ello, es estrictamente obligatorio emplear mecanismos para descartar ramas masivamente.

## Función de Factibilidad y Cotas
Como se indicaba en el aprtado anterior, es sumamente necesario incluir en los algoritmos algún mecanismo que nos permita reducir de alguna forma el número de nodos que podemos llegar a explorar. 
Es por ello que en nuestra clase ``EstadoCamino`` tenemos una función ``avanzarEstado``, que permite que un estado hijo solo se consolida en el árbol si cumple dos condiciones:

- Límites espaciales: Las coordenadas calculadas para el destino se encuentran dentro del rango válido de la matriz ($[0, n-1]$).  
- Prevención de ciclos: La matriz booleana de control verifica que el pilar de destino no forma parte de la ruta actual, evitando bucles infinitos.  

No obstante, descartando los movimientos no factibles, el número de rutas válidas puede ser muy alto. Es por ello, que para el algoritmo de minimización de saltos (``caminoHaciaAltar``) hemos podido incluir una técnica de poda por cota superior: 
- Cota global: ``min_saltos`` representa el mejor valor conocido, almacenando el tamaño de la ruta óptima encontrada hasta este momento. Al principio es inicializada en infinito. 
- Cota local: Representa el número de saltos que el explorador ya ha dado en la rama actual (el tamaño del vector ruta).
- Lógica de Poda: Si durante la expansión de un nodo se detecta que la cota local iguala o supera a la cota global (ruta >= min_saltos), el algoritmo asume que cualquier solución derivada de esa rama será subóptima. En ese instante, se aborta la exploración de ese subárbol (poda) y se realiza el backtracking para evaluar la siguiente alternativa.