/**
  * @file ordenar2.cpp
  * @brief Lee dos números y los escribe ordenados
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea dos valores reales desde la entrada estándar y los
  * escriba en la salida de menor a mayor.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca dos valores: 2.4 7.3
  *    Los valores ordenados son: 2.4 7.3
  *
  * Otro ejemplo de ejecución, donde los valores se introducen desordenados, es:
  *    Introduzca dos valores: 5 2
  *    Los valores están desordenados, intercambiando...
  *    Los valores ordenados son: 2 5
  *
  * Para resolver el problema deberá tener en cuenta que:
  *    - Los dos valores se leen en dos variables en una misma línea.
  *    - Si no están ordenados, se escribirá el aviso de intercambio y se
  *      intercambiarán los valores de las dos variables.
  *    - El resultado es, en cualquier caso, escribir las dos variables.
  *    - La variable auxiliar para el intercambio tendrá un ámbito mínimo.
  *
  */
#include<iostream>
using namespace std;
int main() {
  double v1, v2;
  cout<<"Introduce dos valores: "<<endl;
  cin >> v1 >> v2;

  if (v1<v2) {
    cout<<"Los valores ordenados son: "<<endl;
    cout << v1 << v2 << endl;
  }
  else {
    cout<<"los valores ordenados son. "<<endl;
    cout << v2 << v1 << endl;
  }

}