/**
  * @file sumatoria.cpp
  * @brief Suma la secuencia de números de la entrada.
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Se desea implementar un programa que calcule la sumatoria de los números que se leen en la
  * entrada. No se sabe cuántos hay, pero sí que todos son positivos. Por tanto, la secuencia
  * termina en cuanto aparece un número no positivo.
  *
  * Un ejemplo de ejecución es:
  *
  *    Introduzca datos: 2.5 3 0
  *    La sumatoria es: 5.5
  *
  * Otro ejemplo es:
  *
  *    Introduzca datos: 2.5 3 -1
  *    La sumatoria es: 5.5
  *
  * Otro ejemplo es:
  *
  *    Introduzca datos: -5
  *    La sumatoria es: 0
  * 
  */
#include <iostream>
using namespace std;

int main() {
  double suma = 0;
  double n=1;

  cout << "Introduzca datos: ";
  cin >> n;

  while(n > 0) {
    suma += n;
    cin >> n;
  }

  cout << "La sumatoria es: " << suma << endl;
}
