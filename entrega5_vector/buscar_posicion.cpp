/**
  * @file buscar_posicion.cpp
  * @brief Programa para buscar la posición de un número en una secuencia
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lee una secuencia de números reales y una vez cargada
  * lee un número a localizar. El resultado consiste en la posición del número en
  * la secuencia.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca secuencia: 5  2.5 3 6 7.1 1
  *    Valor a localizar: 3
  *    El valor 3 está en la posición 1.
  *
  * Otro ejemplo es:
  *    Introduzca secuencia: 5  2.5 3 6 7.1 1
  *    Valor a localizar: 4
  *    El valor 4 no está en la secuencia.
  *
  * Otro ejemplo es con valores repetidos:
  *    Introduzca secuencia: 7  2.5 3 6 7.1 1 3 1
  *    Valor a localizar: 3
  *    El valor 3 está en la posición 1.
  *
  * Donde puede ver que devuelve la primera posición donde se encuentra. Para
  * resolverlo, escriba el código completamente en la función main, sin otras
  * funciones auxiliares.
  *
  * El código deberá ser eficiente: concretamenta deberá parar la búsqueda en el
  * momento en que encuentre la posición buscada, sin seguir recorriendo el vector.
  *
  */
#include <iostream>
#include <cmath>

using namespace std;

int main(){
  const int MAX = 100;
  int n;
  double vector[MAX];
  int v, pos;

  cout << "Introduzca secuencia: ";
  cin >> n;

  if (n<0){
      cout <<"0"<<endl;
  }

  for (int i = 0; i < n; i++) {
      cin >> vector[i];
  }
  cout << endl;

  cout << "Valor a localizar: ";
  cin >> v;
  bool estado=false;

  for (int i = 0; i < n; i++) {
      if (vector[i]==v){
        pos = i;
        estado=true;
        cout <<"El valor "<< v << " esta en la posicion " << v;
      } else {
        cout <<"El valor "<< v << " no esta en la secuencia ";
      }
  }
}