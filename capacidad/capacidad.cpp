/**
  * @file capacidad.cpp
  * @brief Programa para introducir conceptos de usados/reservados
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lee una secuencia de valores reales en un vector
  * y los vuelva a escribir en el mismo formato, pero invertidos.
  *
  * La entrada de datos consisten en un número entero (el número de datos)
  * seguido de tantos valores reales como indica dicho número.
  *
  * Debe tener en cuenta que el programa estará limitado a una capacidad máxima
  * de secuencias de 100 elementos. Si el usuario desea más, el programa
  * terminará con un mensaje de error.
  *
  * Además, si el número de datos es 0 o negativo se considerará que no hay
  * datos. El resultado, por tanto, será la secuencia vacía.
  *
  * Por ejemplo, una ejecución puede ser:
  *
  *     Introduzca secuencia: 5  2.5 3 6 7.1 1
  *     5  1 7.1 6 3 2.5
  *
  * donde la primera línea corresponde a la lectura de datos y la segunda al
  * resultado del programa.
  *
  * Otro ejemplo es:
  *
  *     Introduzca secuencia: -5
  *     0
  *
  * donde puede ver que el tamaño no positivo indica que no hay datos. Por tanto,
  * la secuencia resultante es dicho tamaño --el 0-- sin nada más.
  *
  * Otro ejemplo, en este caso mostrando la limitación de capacidad es:
  *
  *     Introduzca secuencia: 10000
  *     Error: capacidad máxima de proceso: 100
  *
  * Observe que no hemos introducido más que el primer entero, pues inmediatamente
  * después de leer este número el programa ya sabe que no podrá procesar la
  * secuencia y termina con el error correspondiente.
  *
  */
#include <iostream>

using namespace std;

int main() {
    const int MAX = 100;
    int n;
    double vector[MAX];

    cout << "Introduzca secuencia";
    cin >> n;

    if (n > MAX) {
        cout << "Error: capacidad máxima de proceso: " << MAX << endl;
    }

    if (n<0){
        cout <<"0"<<endl;
    }

    for (int i = 0; i < n; i++) {
        cin >> vector[i];
    }
    cout << endl;

    for (int i = n-1; i>=0; i--) {
        cout << vector[i] << " ";
    }
}
