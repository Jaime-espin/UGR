/**
  * @file divisor.cpp
  * @brief Programa para comprobar si un número divide a otro
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * El programa pretende leer dos números enteros no negativos y comprobar
  * si el segundo divide al primero. La versión que se ofrece no funciona.
  * Debe corregir los errores.
  *
  * Un ejemplo de ejecución:
  *    Introduzca dividendo y divisor: 10 3
  *    No es divisible
  *
  * Otro ejemplo:
  *    Introduzca dividendo y divisor: -9 3
  *    El programa no admite números negativos
  *
  * Otro ejemplo:
  *    Introduzca dividendo y divisor: 9 3
  *    3 divide a 9
  *
  * Otro ejemplo:
  *    Introduzca dividendo y divisor: 0 3
  *    3 divide a 0
  *
  * Otro ejemplo:
  *    Introduzca dividendo y divisor: 9 0
  *    No es divisible
  *
  * 
  */

#include <iostream>
using namespace std;

int main() {
  int dividendo, divisor;

  cout << "Introduzca dividendo y divisor: ";
  cin >> dividendo >> divisor;

  if (dividendo < 0 || divisor < 0 ) {
    cout << "El programa no admite números negativos" << endl;
  } else {
    if (divisor != 0 && dividendo % divisor == 0)
      cout << divisor << " divide a " << dividendo << endl;
    else cout << "No es divisible" << endl;
    }
  }

