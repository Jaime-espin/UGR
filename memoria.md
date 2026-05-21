1. Descripción del Problema Asignado

Enunciado:
"Disponemos de K euros para hacer la compra y tenemos una lista de n posibles productos
que podemos comprar. Cada producto i tiene un precio, p(i) (que ser ́a siempre un n ́umero
entero), y una utilidad, u(i). De cada producto estamos dispuestos a comprar como m ́aximo
2 unidades. Pero hay una oferta 3X2 en todos los productos, de manera que si compramos
2 unidades de un producto nos regalan una tercera unidad. Queremos elegir los productos a
comprar, y cu ́antos de cada tipo, maximizando la utilidad de los productos comprados.
Por ejemplo para un problema con n = 3, K = 10, p = (3,4,5) y u = (7,8,9), la soluci ́on
 ́optima consiste en llevarnos 3 unidades del primer producto y una unidad del segundo, con un
precio total de 10 y una utilidad de 29.
Dise ̃nad e implementad un algoritmo de Programaci ́on Din ́amica que resuelva este problema,
indicando la utilidad m ́axima obtenida, cu ́ales tipos de productos adquirimos y cu ́antos de cada
tipo. Determinad cu ́al es su eficiencia te ́orica.
Aplicadlo para resolver el ejemplo anterior y el siguiente caso del problema, construyendo
la(s) tabla(s) correspondiente(s)"

Resumen: Contamos con un presupuesto máximo y una lista de productos con un precio y una utilidad determinada. El objetivo es maximizar la utilidad total comprando como máximo 2 unidades pagadas de cada producto, aprovechando que existe una oferta 3x2 (si pagamos 2, nos llevamos 3 unidades).

2. Planteamiento mediante Programación Dinámica

2.1 Planteamiento de la solución como secuencia de decisiones:

El problema se divide en $n$ etapas, una por cada producto. En cada etapa, debemos decidir cuántas unidades del producto actual vamos a comprar teniendo en cuenta el dinero que nos queda. Las opciones son:
- No comprar el producto (0 unidades).
- Comprar 1 unidad pagando su precio.
- Comprar 2 unidades pagando el doble de su precio, lo que nos da 3 unidades por la oferta.

2.2 Verificación del principio de optimalidad:

Para que nuestra compra final sea la más óptima, cualquier decisión intermedia que tomemos con los primeros $i$ productos y un presupuesto $k$ debe ser también la mejor combinación posible para ese subproblema. Si encontramos la mejor forma de gastar el presupuesto en los primeros $i-1$ productos, al añadir el producto $i$ evaluamos si mejora o no la utilidad máxima ya calculada.

2.3 Definición recursiva del valor de la solución óptima:

Definimos $T(i, k)$ como la utilidad máxima que podemos obtener considerando los primeros $i$ productos con un presupuesto disponible $k$. La ecuación de recurrencia es la siguiente:
$$T(i, k) = \max \begin{cases} T(i-1, k) & \text{(No comprar)} \\ T(i-1, k - p_i) + u_i & \text{si } k \ge p_i \text{ (Comprar 1)} \\ T(i-1, k - 2p_i) + 3u_i & \text{si } k \ge 2p_i \text{ (Comprar 2 y llevar 3)} \end{cases}$$

- Caso $T(i-1, k)$: Representa la opción de no comprar el producto $i$. La utilidad acumulada no varía y el presupuesto disponible $k$ se mantiene intacto para los primeros $i-1$ productos.
- Caso $T(i-1, k - p_i) + u_i$: Modela la decisión de comprar exactamente 1 unidad. Se añade la utilidad de dicha unidad ($u_i$) y se reduce el presupuesto disponible en el coste de un solo producto ($p_i$).
- Caso $T(i-1, k - 2p_i) + 3u_i$: Justifica matemáticamente la oferta 3x2 del enunciado. Si decidimos adquirir el producto aprovechando la promoción, pagamos un máximo de 2 unidades (reduciendo el presupuesto en $2p_i$). A cambio, el problema nos regala una tercera unidad, lo que significa que nos llevamos 3 unidades completas y sumamos el triple de su utilidad ($3u_i$) pagando solo el precio de dos. El algoritmo evalúa mediante la función $\max$ cuál de estas tres decisiones alternativas proporciona el mayor beneficio.

Donde $p_i$ es el precio del producto $i$ y $u_i$ es su utilidad o beneficio. El caso base es $T(0, k) = 0$ y $T(i, 0) = 0$, que en el código se maneja inicializando la matriz entera a 0.

2.4 Cálculo del valor de la solución óptima (enfoque ascendente):

Creamos una matriz (tabla) de dimensiones $(n+1) \times (K+1)$. Con dos bucles anidados, iteramos primero por cada producto (filas) y luego por cada posible cantidad de dinero desde 1 hasta el presupuesto máximo (columnas). Para cada celda, calculamos el máximo de las tres decisiones posibles apoyándonos en los resultados de la fila anterior (que ya están calculados), evitando así recálculos redundantes.

2.5 Determinación de la solución óptima (uso de tablas):

Una vez rellenada la tabla, la utilidad máxima estará en la celda ``tabla[n][K]``. Para saber qué productos hemos comprado, usamos la función auxiliar ``construirSolucion``. Empezamos en la última celda y vamos hacia atrás:
- Si el valor de la celda actual es igual al de la celda justo encima (``tabla[i-1][k]``), significa que no compramos el producto $i$. Subimos una fila.
- Si el valor coincide con el de la oferta (``tabla[i-1][k - 2p] + 3u``), añadimos 3 unidades a la solución, restamos el coste de 2 unidades al presupuesto y subimos.
- En caso contrario, añadimos 1 unidad, restamos su coste al presupuesto y subimos.

3. Diseño del Algoritmo y Eficiencia

3.1 Especificación del algoritmo:

El algoritmo principal (``mejorCombinacionCompra``) inicializa la estructura de datos y evalúa iterativamente la ecuación de recurrencia mediante los siguientes pasos.

    1. Se declara la tabla de programación dinámica y se llena de ceros.

    2. Se itera sobre el número de productos y el presupuesto.

    3. Se verifica que haya presupuesto suficiente (p_actual <= k) para comprar 1 o 2 unidades.

    4. Se guarda el máximo de las tres decisiones en la celda actual.

    5. Se invoca a la función de reconstrucción para devolver el vector de los productos seleccionados y sus cantidades.
3.2 Eficiencia teórica: 
- Complejidad temporal: $O(n \times K)$ donde $n$ es el número total de productos y $K$ es el dinero máximo disponible. Esto se debe a los dos bucles for anidados que recorren la matriz. La función de reconstrucción cuesta $O(n)$, por lo que no altera la eficiencia asintótica
- Complejidad espacial: $O(n \times K)$ porque necesitamos almacenar una matriz de tamaño $(n+1) \times (K+1)$ enteros en memoria para guardar las soluciones a los subproblemas.

4. Ejemplos de Aplicación y Casos de Prueba

4.1 Resolución del ejemplo base: 
Datos del problema: $n = 3$, $K = 10$, $p = (3, 4, 5)$, $u = (7, 8, 9)$.

Salida de la ejecución:

Tabla de Programacion Dinamica T(i,k):
i \ k   | 0     1       2       3       4       5       6       7       8       9       10
--------+-----------------------------------------------------------------------------------------
0       | 0     0       0       0       0       0       0       0       0       0       0
1       | 0     0       0       7       7       7       21      21      21      21      21
2       | 0     0       0       7       8       8       21      21      24      24      29
3       | 0     0       0       7       8       9       21      21      24      24      29

COMPRA OPTIMA 1

Producto 2: 1 unidad(es).
Producto 1: 3 unidad(es).
Utilidad maxima obtenida: 29

Observando la tabla, partimos de la celda final $T(3, 10) = 29$. Como este valor es igual al de la celda superior $T(2, 10) = 29$, deducimos que no se compra el Producto 3. En la fila 2, el valor 29 se obtiene de comprar 1 unidad del Producto 2 (coste 4, utilidad 8), por lo que restamos 4 al presupuesto y pasamos a $T(1, 6) = 21$. Este valor proviene de la oferta 3x2 del Producto 1 (pagamos 2 unidades con coste 6, ganamos 21 de utilidad). El presupuesto queda a 0.

4.2 Resolución de casos adicionales: 

Datos del problema: $n = 6$, $K = 16$, $p = (1, 2, 3, 4, 5, 6)$, $u = (7, 8, 9, 5, 6, 18)$.

Salida de la ejecución:

Tabla de Programacion Dinamica T(i,k):
i \ k   | 0     1       2       3       4       5       6       7       8       9       10      11      12      13      14      15      16
--------+-----------------------------------------------------------------------------------------------------------------------------------------
0       | 0     0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
1       | 0     7       21      21      21      21      21      21      21      21      21      21      21      21      21      21      21
2       | 0     7       21      21      29      31      45      45      45      45      45      45      45      45      45      45      45
3       | 0     7       21      21      29      31      45      45      48      54      56      58      72      72      72      72      72
4       | 0     7       21      21      29      31      45      45      48      54      56      58      72      72      72      72      77
5       | 0     7       21      21      29      31      45      45      48      54      56      58      72      72      72      72      77
6       | 0     7       21      21      29      31      45      45      48      54      56      58      72      72      75      75      83

COMPRA OPTIMA 2

Producto 6: 3 unidad(es).
Producto 2: 1 unidad(es).
Producto 1: 3 unidad(es).
Utilidad maxima obtenida: 83

Comenzamos en la celda $T(6, 16) = 83$. Este valor se forma al pagar 2 unidades del Producto 6 (coste 12) para llevarse 3 gracias a la oferta, lo que suma 54 de utilidad. Nos quedan 4 euros. En $K=4$, el valor máximo es 29, que se arrastra desde la fila 2. Por tanto, no compramos los productos 5, 4 ni 3. En $T(2, 4) = 29$, compramos 1 unidad del Producto 2 (coste 2, utilidad 8). Con los 2 euros restantes, subimos a la fila 1 y pagamos 2 unidades del Producto 1 (coste 2) para llevar 3, sumando los últimos 21 de utilidad.