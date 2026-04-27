## Práctica 3: Algoritmos Voraces - Problema 1: ¿El algoritmo nos garantiza siempre la solucion más óptima?
Partimos de un conjunto de n sustancias, cada una con un intervalo de reacción $I_i = [l_i, h_i]$. Queremos encontrar un conjunto mínimo de frecuencias $F = \{f_1, f_2, \dots, f_k\}$ tal que $\forall I_i, \exists $ al menos un $f_j \in I_i$.

## Nuestro Algoritmo Voraz
Actualmente nuestro algoritmo ordena los intervalos de manera ascendente por su $l_i$, luego evalúa los intervalos solapados y coloca siempre el láser $f_1$ (primer disparo) en el valor más a la derecha posible de la intersección actual, siendo entonces $f_1 = \min(h_i)$ de los intervalos que se solapan.

## Demostración por reducción al absurdo 

Sea $I_1 = [l_1,h_1]$ el intervalo más a la izquierda sin cubrir. Toda solución valida deberá disparar en algún $f \in [l_1,h_1]$ para cubrirlo.

- Nuestro algoritmo elige como punto de disparo $p^*$ el valor mínimo de los extremos derechos de los intervalos que se solapan en la iteración actual. Es decir, $p^* = \min \{h_i \mid I_i \in G\}$, siendo $G$ el conjunto de intervalos solapados.

Sea $S^*$ una solución optima que dispara en algún $p \in [l_1,h_1]$. Si $p \neq p^*$, construimos $S’$ reemplazando $p$ por $p^*$.

- Como $p*$ es el mínimo derecho del grupo, $p^* \leq h_1$, asi que $p^* \in [l_1,h_1]$
- Entonces todo $I_i = [l_i,h_i]$ cubierto por $p$ con $l_i \leq p \leq h_i$ satisface $l_i \leq p^* \leq h_i$ porque:
  - $l_i \leq p^*$: como el intervalo está en el grupo solapado, $l_i \leq$ cota_sup en algún paso.
  - $p^* \leq h_i:$ por definición, $p^*$ es el mínimo de los extremos derechos del grupo.

Por tanto, $S’$ cubre al menos lo mismo que $S^*$ con el mismo número de disparos. $|S’| = |S^*|$, luego nuestro algoritmo greedy no puede ser subóptimo.