/**
  * @file positivos_negativos.cpp
  * @brief Cuenta los números positivos y negativos (lectura anticipada y centinela)
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Se desea implementar un programa que cuente la cantidad de datos que son positivos y
  * negativos en una secuencia de valores enteros. Implemente un programa que lea datos hasta
  * que se lea el valor cero. Como resultado, indicará en la salida estándar cuántos han sido
  * positivos y cuántos negativos.
  *
  * Un ejemplo de ejecución es:
  *
  *    Introduzca datos: 2.5 -33 6 7.1 1 0
  *    Negativos: 1
  *    Positivos: 4
  * 
  */
#include <iostream>
using namespace std;

int main() {
  int positivos = 0;
  int negativos = 0;
  double n;

  cout << "Introduzca datos: ";
  cin >> n;

  while(n != 0) {
    if (n > 0) {
      positivos++;
    } else {
      negativos++;
    }
    cin >> n;
  }

  cout << "Negativos: " << negativos << endl;
  cout << "Positivos: " << positivos << endl;
}