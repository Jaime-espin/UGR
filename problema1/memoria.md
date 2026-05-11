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

Como cada nodo interno del árbol puede generar hasta 4 hijos, el tamaño del árbol crece de forma exponencial. En el peor de los casos, la longitud máxima de una ruta (sin ciclos) en una matriz de $n \times n$ es $n^2$ casillas. Es decir, la complejidad espacial y temporal teórica es de orden $\mathcal{O}(4^{n^2})$. Por ello, es estrictamente obligatorio emplear mecanismos para descartar ramas masivamente.

## Función de Factibilidad y Cotas
Como se indicaba en el aprtado anterior, es sumamente necesario incluir en los algoritmos algún mecanismo que nos permita reducir de alguna forma el número de nodos que podemos llegar a explorar. 
Es por ello que en nuestra clase ``EstadoCamino`` tenemos una función ``avanzarEstado``, que permite que un estado hijo solo se consolida en el árbol si cumple dos condiciones:

- Límites espaciales: Las coordenadas calculadas para el destino se encuentran dentro del rango válido de la matriz ($[0, n-1]$).  
- Prevención de ciclos: La matriz booleana de control verifica que el pilar de destino no forma parte de la ruta actual, evitando bucles infinitos.  

No obstante, descartando los movimientos no factibles, el número de rutas válidas puede ser muy alto. Es por ello, que para el algoritmo de minimización de saltos (``caminoHaciaAltar``) hemos podido incluir una técnica de poda por cota superior: 
- Cota global: ``min_saltos`` representa el mejor valor conocido, almacenando el tamaño de la ruta óptima encontrada hasta este momento. Al principio es inicializada en infinito. 
- Cota local: Representa el número de saltos que el explorador ya ha dado en la rama actual (el tamaño del vector ruta).
- Lógica de Poda: Si durante la expansión de un nodo se detecta que la cota local iguala o supera a la cota global (ruta >= min_saltos), el algoritmo asume que cualquier solución derivada de esa rama será subóptima. En ese instante, se aborta la exploración de ese subárbol (poda) y se realiza el backtracking para evaluar la siguiente alternativa.

## Implementación
Como se menciona en el guion, hemos desarrollado dos algoritmos distintos. Ambos se basan en la misma estructura de exploración y de factibilidad, pero con objetivos distintos. 

No obstante, como ambos usarán las clases ``Lianas`` y ``EstadoCamino`` vamos a describirlas brevemente.

La clase ``Lianas`` no es más que un wrapper, en donde en su interior contiene la matriz del problema. Es decir, que en el interior de la clase existe la variable miembro ``vector<vector<int>> lianas;`` en donde cada casilla ``(i,j)`` contiene el valor ``k`` de dicha posición, haciendo referecia a la longitud de la liana. Además, se le ha sobrecargado ciertos operadores para hacer más fácil su uso. 

La importancia reside en la clase ``EstadoCamino``, por lo que la describiremos en más detalle. Como se indicaba en apartados anteriores, esta clase contiene las coordenadas exactas de la posición del explorador en este mismo momento ``(fila, columna)``; así como el vector ``ruta`` que hace referencia a la ruta actual (desde la posición inicial hasta la actual); y por último la matriz de estado ``visitados`` que nos permite saber en todo momento los pilares que ya han sido visitados o no. No obstante, es de suma importancia describir dos funciones que hemos implementado en esta clase: 

- ``bool avanzarEstado(const Lianas& l, Direccion movimiento)``: Dado una referencia de la clase liana y el movimiento que queremos hacer (IZQUIERDA, DERECHA, ARRIBA, ABAJO) esta clase obtiene el salto (gracias a nuestra posición actual) y evalúa dependiendo del movimiento en qué coordenada final sería el destino. Si podemos avanzar, es decir, seguimos en los límites permitidos y no hemos visitado dicho pilar, pues lo incluimos tanto en nuestra ``ruta`` como en nuestro ``visitados`` y devolvemos ``true``. En caso contrario, se devuelve ``false``.

- `` void deshacerEstado(int fila_anterior, int columna_anterior)``: Esta función nos permite ir un paso hacia atrás. Por lo que si le pasamos una fila_anterior y una columna_anterior, marcará nuestras coordenadas *actuales* como *no* visitadas, eliminará de la ruta ese pilar, y nos situará en la posición anterior determinada por ``fila_anterior`` y ``columna_anterior``.

### Algoritmo Básico: Búsqueda de la primera solución
En este algoritmo nos centraremos en encontrar (si existe) la primera solución posible para llegar del punto de partida hacia el altar. 
Para ello nos hemos definido la función ``bool caminoSencillo(const Lianas &mapa, EstadoCamino &estado, pair<int, int> destino)`` que recibe una referencia del mapa, nuestro estado y la casilla de destino. Esta función devuelve ``true`` si encuentra un camino posible (el primer camino que encuentra) y la ruta de pasos es devuelto mediante ``estado``.
Lo primero que tenemos que hacer, es plantear nuestro caso base. En este momento, acabamos cuando las coordenadas de nuestro ``estado`` coincidan exactamente con las coordenadas de ``destino``: 
```cpp
if (estado.fila == destino.first && estado.columna == destino.second) {
    return true; 
} 
```

Ahora la idea es sencilla. Como vimos en el apartado del árbol de exploración, debemos de crear para el nodo actual sus cuatro hijos correspondientes. Para manejar las direcciones hemos creado un array de la siguiente forma: 
```cpp
static const Direccion direcciones[] = {ABAJO, DERECHA, IZQUIERDA, ARRIBA};
```
Este orden no es establecido "porque sí"; sino que tiene una razón. A la hora de decidir qué punto será el de destino ``(a, b)`` teníamos dos opciones: elegirlo al azar para cada mapa o establecer uno idéntico para todos. Nosotros hemos preferido elegir que el punto de destino sea siempre la posición última de la matriz (abajo a la derecha). Es por eso que están en ese orden en el vector, para que se encuentre más rápido. No obstante, si el orden se cambiara solo afectaría  al tiempo. Para dejarlo más claro en la sección de Análisis Empírico cambiaremos el orden para ver como afecta. 

Ahora solo nos queda, para cada una de esas posibilidades, avanzar el estado y llamar recursivamente a nuestra función. 

```cpp
for (const Direccion& dir : direcciones) {
    const int fila_origen = estado.fila;
    const int col_origen = estado.columna;
    // Intentamos avanzar
    if (estado.avanzarEstado(mapa, dir)) {
        //Llamada recursiva
        if (caminoSencillo(mapa, estado, destino)) return true; 
        
        // Si llegamos aquí, es que la ruta elegida no llevó al altar. Deshacer los cambios.
        estado.deshacerEstado(fila_origen, col_origen);
    }
} 
```

### Algoritmo Óptimo: Minimización de saltos
Este algoritmo tiene la esencia del anterior, pero aquí no podemos únicamnete pararnos al encontrar la primera ruta posible, sino que tenemos que seguir explorando hasta poder encontrar la ruta mínima. Es en este algoritmo donde haremos uso de la técnica de poda que describimos con anterioridad. 

La función para este algoritmo es ``vector<pair<int,int>> caminoHaciaAltar(const Lianas& mapa, EstadoCamino& estado, pair<int,int> destino, int &min_saltos, int &nodos_podados, int &nodos_generados)``. A esta función se le pasa por parámetros el mapa, el estado actual, las coordenadas de destino, la cantidad mínima de saltos conocida, cuántos nodos hemos podado y cuántos nodos hemos generado. Estos últimos parámetros son únicamente para establecer conclusiones. Además, retorna un vector con la ruta óptima. 

Lo primero que tenemos que hacer es saber si esta rama nos interesa explorarla o no (poda). Para ello establecemos la condición de, si los saltos que llevamos actualmente (identificado como el tamaño del vector de la ruta) es mayor que nuestra variable de saltos mínimos *no nos interesa* esta rama. 
```cpp
//si no mejorará la solución que ya tenemos, podamos
if (estado.ruta.size() >= min_saltos){
    nodos_podados++; //Para las métricas
    return vector<pair<int, int>>(); //Devuelve una ruta vacía
}
```

Posteriormente, verificamos si hemos alcanzado el destino. Gracias a que la condición de poda se evalúa primero, si llegamos a este bloque de código está matemáticamente garantizado que estado.ruta.size() < min_saltos, por lo que automáticamente registramos esta nueva ruta como el nuevo mínimo global:

```cpp

//si llegamos al destino
if (estado.fila == destino.first && estado.columna == destino.second) {
    min_saltos = estado.ruta.size();
    return estado.ruta;
}
```

Como en el algoritmo sencillo, si hemos llegado hasta aquí tenemos que expandir los cuatro hijos posibles de este nodo, aplicarles el avance del estado y llamar de forma recursiva a la función: 

```cpp
{
    ...

    vector<pair<int, int>> mejor_ruta;

    for (const Direccion& dir : direcciones) {

        const int fila_origen = estado.fila;
        const int col_origen = estado.columna;
        //intentamos avanzar
        if (estado.avanzarEstado(mapa, dir)) {
            //exploramos
            const vector<pair<int,int>> camino_encontrado = caminoHaciaAltar(mapa, estado, destino, min_saltos, nodos_podados, nodos_generados);
            if (!camino_encontrado.empty()) {
                mejor_ruta = camino_encontrado; //si encontramos un mejor camino
            }
            //restauramos hacia al estado que tenia antes de ejecutar avanzarEstado
            estado.deshacerEstado(fila_origen, col_origen);
        }
    }

    return mejor_ruta;
}

```

## Análisis Empírico
Para evaluar el rendimiento y la eficiencia de ambos algoritmos, se ha diseñado un marco de pruebas en el archivo principal (main.cpp). Se han implementado funciones auxiliares para la lectura automatizada de los mapas desde archivos .txt proporcionados por el profesor, así como rutinas de medición de tiempo utilizando la librería estándar <chrono>. Para evitar el ruido del sistema, el tiempo es la media aritmética de 10 ejecuciones.

Además de los tiempos y el número de saltos, se han instrumentado las funciones recursivas para contabilizar los nodos generados (llamadas a la función) y los nodos podados (ramas descartadas), permitiendo así un análisis del comportamiento interno del árbol.

### Resultados 1
En este primer experimento, se ha utilizado el orden de direcciones descrito en la sección anterior: {ABAJO, DERECHA, IZQUIERDA, ARRIBA}. 
Hecmos referencia al algoritmo básico como B y al óptimo como O.
Hemos obtenido estos resultados: 

| MAPA | SALTOS(B) | TIEMPO(B)ms | SALTOS(O) | TIEMPO(O)ms | GENERADOS(O) | PODADOS(O) |
|---|---:|---:|---:|---:|---:|---:|
| lianas10.txt | 26 | 0.0079 | 8 | 0.4172 | 1917.0000 | 657.0000 |
| lianas10b.txt | 17 | 0.0083 | 10 | 0.1611 | 785.0000 | 264.0000 |
| lianas10ss.txt | 0 | 183.5991 | 0 | 225.7415 | 1090343.0000 | 0.0000 |
| lianas12.txt | 15 | 155.1850 | 4 | 181.6170 | 804201.0000 | 2198.0000 |
| lianas15.txt | 4 | 0.0009 | 4 | 0.0051 | 25.0000 | 10.0000 |
| lianas20.txt | 35 | 0.0076 | 7 | 1.0146 | 5642.0000 | 2500.0000 |
| lianas20b.txt | 105 | 0.1469 | 11 | 3.9035 | 21342.0000 | 7697.0000 |
| lianas20c.txt | 112 | 0.0305 | 5 | 4.5957 | 24156.0000 | 9473.0000 |
| lianas20d.txt | 24 | 0.0038 | 7 | 0.9085 | 5154.0000 | 2146.0000 |
| lianas25.txt | 59 | 0.0174 | 7 | 2.6336 | 15213.0000 | 6877.0000 |
| lianas30.txt | 7 | 0.0011 | 7 | 0.0365 | 218.0000 | 108.0000 |
| lianas30b.txt | 261 | 0.0747 | 8 | 22.0141 | 114105.0000 | 47608.0000 |

Como se observa en mapas grandes como ``lianas30b.txt``, el algoritmo básico es extremadamente rápido (0.0747 ms) pero devuelve una ruta completamente ineficiente (261 saltos). Esto demuestra empíricamente su comportamiento: al carecer de restricciones de minimización, simplemente explora por el tablero y se detiene en la primera ruta que casualmente choca con el altar.

El mapa ``lianas30b.txt`` es también el mejor ejemplo para apreciar nuestra cota. Para encontrar la ruta óptima de 8 saltos, el algoritmo generó 114.105 nodos. Sin embargo, la función de poda actuó en 47.608 ocasiones, podando casi el 42% del espacio de búsqueda y logrando un tiempo de apenas 22.0141 ms.

Los datos del mapa ``lianas10ss.txt`` corroboran el comportamiento del Backtracking exhaustivo. Al no existir un camino posible hacia el altar, el algoritmo nunca puede establecer un valor inicial para min_saltos. Como resultado, la cota jamás se activa (0 nodos podados) y el programa se ve forzado a explorar la totalidad del árbol de búsqueda (generando 1.090.343 nodos en una matriz de solo $10 \times 10$). Esto explica por qué es el caso que más tiempo consume (~225 ms) a pesar de su reducido tamaño. 

Para establecer un ejemplo de la salida del algoritmo básico VS el algoritmo óptimo, hemos tomado como ejemplo la salida del mapa ``lianas12.txt``:
```bash
Mapa: lianas12.txt
  [BÁSICO] Saltos: 15 | Tiempo: 155.185 ms
  Trayectoria: (0,0) -> (3,0) -> (9,0) -> (9,5) -> (1,5) -> (1,8) -> (3,8) -> (3,9) -> (11,9) -> (11,0) -> (11,10) -> (11,3) -> (0,3) -> (0,11) -> (1,11) -> (11,11)
  [ÓPTIMO] Saltos: 4 | Tiempo: 181.617 ms
  Trayectoria: (0,0) -> (0,3) -> (0,11) -> (1,11) -> (11,11)
```

Analizando detalladamente las trayectorias obtenidas para el mapa lianas12.txt, se observan peculiaridades clave del comportamiento de ambos algoritmos. En primer lugar, ambas rutas convergen en el mismo tramo final: (0,3) -> (0,11) -> (1,11) -> (11,11). Esto indica que la casilla (0,3) es un punto crítico. Mientras que el algoritmo Óptimo alcanza este nodo directamente en su primer movimiento, el algoritmo Básico por ser "ciego" solamente se empeña en seguir las direcciones descritas; al priorizar el movimiento hacia 'ABAJO', se lanza en picado (0,0) -> (3,0) -> (9,0) alejándose de la ruta ideal y viéndose obligado a dar un rodeo de 11 saltos antes de encontrar el cuello de botella en (0,3).
