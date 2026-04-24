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

Nuestro algoritmo subóptimo comienza con una asignación `vector<pair<double, double>> intervalos = intervalosOriginales`
que no vamos a tener en cuenta en el cálculo principal ya que esto lo hacemos únicamente para que sea `const` el conjunto de invervalos original al realizar las diferentes pruebas. Por el mismo motivo, descartamos del análisis la sentencia `frecuencias.clear()`.

Por lo que, empezamos el análisis en la ordenación. En este caso hemos preferido usar `std::sort` para
ordenar por el inicio del intervalo. El coste estándar de hacer esta operación es $O(n \log n).

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
