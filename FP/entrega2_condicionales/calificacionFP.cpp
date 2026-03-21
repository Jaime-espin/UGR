/**
  * @file calificacionFP.cpp
  * @brief Programa para calcular la calificación de una asignatura
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * El programa debe leer dos números reales en el rango [0,10]
  * y calcular la calificación final de una asignatura.
  *
  * Se supone que la calificación es la media ponderada con pesos del
  * 60% y 40% respectivamente. Además, deberá tener una nota mínima
  * en la primera nota. Si no se alcanza, la calificación final será
  * directamente esta primera nota.
  *
  * Para que el programa pueda adaptarse fácilmente a cambios en los
  * umbrales de calificación, deberá crear las constantes que considere
  * oportunas.
  *
  * Un ejemplo de su ejecución:
  *    Introduzca las dos notas: 3.9 7
  *    Calificación: 3.9
  *
  * Otro ejemplo:
  *    Introduzca las dos notas: 4 7
  *    Calificación: 5.2
  *
  * Otro ejemplo:
  *    Introduzca las dos notas: 10.5 4
  *    Notas no válidas.
  *
  * donde puede ver que si las dos notas no están en el rango esperado
  * el programa deberá imprimir un mensaje de error y terminar.
  * 
  */
#include <iostream>

using namespace std;

int main() {
  double nota1, nota2;
  double calificacion;
  cout << "Introduzca las dos notas: ";
  cin >> nota1 >> nota2;
  const double peso1 = 0.6;
  const double peso2 = 1 - peso1;
  const double notaMinima = 4.0;

  if (nota1 < 0 || nota1 > 10 || nota2 < 0 || nota2 > 10) {
    cout << "Notas no validas." << endl;
  }
  if (nota1 <= notaMinima && nota1 <= 10) {
    cout << "Calificacion: " << nota1 << endl;
  }
  else {
    calificacion = (nota1 * peso1) + (nota2 * peso2);
    cout << "Calificacion: " << calificacion << endl;
  }
  return 0;
}


