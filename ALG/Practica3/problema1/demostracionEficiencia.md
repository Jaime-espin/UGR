## Algoritmo Voraz - Eficiencia Teórica (Óptimo)

Nuestro algoritmo comienza en la función `minFrecuencias`  donde introducimos `n` intervalos
en un `set<pair<double,double>>`. Internamente, C++ gestiona el `set` como un árbol binario de búsqueda
balanceado, por lo que la inserción de los `n` elementos tiene una eficiencia $O(n \log n)$.

Posteriormente, entramos en el núcleo del algortimo al realizar el bucle `while`, para analizarlo tendremos que 
ver qué hacemos dentro de la función `encuentraIntersecciones`. Dentro de dicha función, solo hacemos un 
`subconjunto.erase(subconjunto.begin())`, es decir, solamente usa un intervalo y lo elimina; eliminar el primer
elemento de un `set` tiene una eficiencia $O(\log n)$, por lo que si en el bucle `while` llamamos recursivamente 
para los `n` intervalos, el coste de esta fase es $O(n) · O(\log n) = O(n \log n)$. 
Si sumamos el coste de la funcion `encuentraIntersecciones` con el coste de la inserción en el `set` nos queda que la 
eficiencia de nuestro algoritmo voraz es $O(n \log n) + O(n \log n) = \mathbf{O(n \log n)}$.


## Algoritmo Voraz - Eficiencia Teórica (Subóptimo)

Empezamos el análisis en la ordenación. En este caso hemos preferido usar `std::sort` para
ordenar por el inicio del intervalo. El coste estándar de hacer esta operación es $O(n \log n)$.

Posteriormente tenemos un doble bucle: 
```cpp
for(const auto& intervalo : intervalos){ 
        bool alcanzado = false;
        for(int i = 0; i < frecuencias.size() && !alcanzado; i++){
            const auto& f = frecuencias[i];
            if(f >= intervalo.first && f <= intervalo.second) alcanzado = true;
        }

        //push_back...
}
```

En el mejor de los casos, es decir, que los intervalos se solapen tanto que el vector de frecuencias se mantenga en tamaño 1, el bucle interno tendrá un coste constante $O(1)$, dejando el coste de recorrer todos los intervalos en $O(n)$.

Sin embargo, en el peor de los casos (donde ningún intervalo se solapa y el vector de frecuencias crece hasta tamaño $n$), el bucle interno iterará hasta el final en cada paso. Esto genera una suma aritmética que nos deja una complejidad cuadrática de $O(n^2)$.

Por lo tanto, si al coste de la ordenación le sumamos el coste del bucle anidado, nos queda que la eficiencia asintótica de este algoritmo es $O(n \log n) + O(n^2) = \mathbf{O(n^2)}$

## Análisis Empírico
Para el análisis empírico hemos decidido realizar una función `realizarEstudioEmpirico` que hará uso de las funciones
descritas a lo largo del desarrollo del problema. Para realizar las mediciones, hemos utilizado una clase auxiliar (que ya
hemos utilizado en prácticas anteriores) para tener acceso al reloj preciso del ordenador y así poder realizar las tomas
de tiempo. 

Como tenemos que analisar dos algoritmos de diferente eficiencia, hemos prefijado tamaños que se puedan adecuar a ambos, 
definiendo un vector de la siguiente forma: `vector<int> tams = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};`.
Además, para evitar ruidos del sistema, hemos preferido hacer `k` iteraciones para cada tamaño, para posteriormente realizar
la media. 

Una vez definida la función, los tamaños y el valor de k, hemos compilado y tomado los tiempos: 

## Análisis Empírico (óptimo)
Para el algoritmo óptimo hemos obtenido los siguientes tiempos: 
> [!NOTE]
> Véase el archivo `datosMemoria/algoritmoOptimo.dat` donde están todos los datos en bruto generados por el algoritmo.

| n | Tiempo |
| :--- | :--- |
| 1000 | 0.00039126 |
| 2000 | 0.000798587 |
| 4000 | 0.00193449 |
| 8000 | 0.0032115 |
| 16000 | 0.00754194 |
| 32000 | 0.0174643 |
| 64000 | 0.0356389 |
| 128000 | 0.0801229 |

A partir de los datos obtenidos, y utilizando la herramienta Gnuplot, hemos podido realizar la gráfica correspondiente:


![Gráfica del algoritmo Voraz Óptimo](./datosMemoria/algoritmoOptimo.png)

## Análisis Empírico (Subóptimo)
Para el algoritmo subóptimo hemos obtenido los siguientes tiempos: 
> [!NOTE]
> Véase el archivo `datosMemoria/algoritmoSuboptimo.dat` donde están todos los datos en bruto generados por el algoritmo.

| n | Tiempo |
| :--- | :--- |
| 1000 | 0.0015957 |
| 2000 | 0.00608971 |
| 4000 | 0.0257527 |
| 8000 | 0.0925139 |
| 16000 | 0.352638 |
| 32000 | 1.69736 |
| 64000 | 6.50092 |
| 128000 | 25.9147 |

A partir de los datos obtenidos, y utilizando la herramienta Gnuplot, hemos podido realizar la gráfica correspondiente:


![Gráfica del algoritmo Voraz Subóptimo](./datosMemoria/algoritmoSuboptimo.png)
> [!NOTE]
> En esta gráfica se ha empleado escala logarítmica.

## Comparación Empírica
![Gráfica comparativa de los tiempos de ejecución del algoritmo Voraz Óptimo frente al Subóptimo](./datosMemoria/comparativa.png)


En la gráfica superior se presenta la comparativa empírica del tiempo de ejecución (en segundos) de ambos algoritmos en función del número de intervalos ($n$). Para facilitar la visualización de ambas curvas y apreciar sus órdenes de magnitud, se ha empleado una escala logarítmica en ambos ejes.
A partir de esta representación gráfica, podemos extraer conclusiones que respaldan directamente nuestro análisis teórico previo:
- Algoritmo Voraz Subóptimo (Línea verde): Muestra una pendiente pronunciada y constante. Tiene una mayor inclinación, lo que es el rasgo característico de una función polinómica de mayor grado, lo que corrobora visualmente nuestra cota teórica cuadrática de $O(n^2)$. El efecto es evidente: a medida que el tamaño de la entrada crece, el coste de cómputo se dispara debido a los bucles anidados.

- Algoritmo Voraz Óptimo (Línea morada): Presenta una pendiente mucho más suave. En la escala logarítmica, una complejidad de $O(n \log n)$ se asemeja a una recta con una pendiente cercana a 1. Como se observa en los datos empíricos, el algoritmo escala de manera excelente, resolviendo problemas de hasta 128.000 intervalos en apenas milésimas de segundo gracias a la eficiencia del árbol binario balanceado `(std::set)`.
