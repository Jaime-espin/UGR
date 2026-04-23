## Práctica 3: Algoritmos Voraces - Problema 1: ¿Es válido el algoritmo?
Partimos de un conjunto de n sustancias, cada una con un intervalo de reacción $I_i = [l_i, h_i]$. Queremos encontrar un conjunto de frecuencias $F = \{f_1, f_2, \dots, f_k\}$ tal que cada intervalo contenga al menos un $f_j$.

## Nuestro Algoritmo Voraz
Actualmente nuestro algoritmo evalúa los intervalos solapados y coloca siempre el láser $f_1$ (primer disparo) en el valor más a la derecha posible de la intersección actual, siendo entonces $f_1 = \min(h_i)$ de los intervalos que se solapan.

## Demostración por reducción al absurdo (Primer Disparo):
- Partimos de la premisa de que nuestro algoritmo $V$ no es óptimo. Por ende, existe una solución óptima alternativa $O$ que utiliza menos disparos, es decir, $|O| < |V|$.
- Sea $I_1$ el intervalo que termina antes del primer grupo solapado, con $I_1 = [l_1, h_1]$. Nuestro algoritmo dispara por primera vez en la posición $f_V = h_1$.
- La alternativa óptima $O$ debe disparar un láser $f_O$ para cubrir el intervalo $I_1$; y para que sea un disparo válido, se debe cumplir obligatoriamente que $f_O \le h_1$.
- Si $f_O = f_V$, ambos algoritmos coinciden en el primer disparo.
- Sin embargo, si $f_O < f_V$, el disparo óptimo está situado más a la izquierda que el nuestro. Mover un disparo hacia la izquierda nunca puede cubrir nuevos intervalos a la derecha que no estuvieran ya cubiertos por $f_V$. 
- Por lo tanto, podemos sustituir $f_O$ por $f_V$ en la solución $O$ sin dejar de cubrir ninguna sustancia y sin aumentar el número de disparos.

## Paso inductivo (El disparo siguiente):
Si eliminamos del problema todos los intervalos que ya han sido cubiertos por este primer disparo $f_V$, nos queda un subproblema idéntico pero más pequeño. Al aplicar de nuevo este mismo razonamiento a los intervalos restantes, comprobamos paso a paso que podemos transformar todos los disparos de la solución óptima $O$ en los disparos de nuestra solución voraz $V$ sin que el tamaño del conjunto aumente en ningún momento.Es por ello que podemos transformar completamente $O$ en $V$ sin añadir frecuencias adicionales, lo que hace imposible que $|O| < |V|$. Por lo tanto, el conjunto devuelto por el algoritmo voraz $V$ es siempre el mínimo posible.