/**
  * @file plantas.cpp
  * @brief Programa para clasificar plantas (Ej. 2.4)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que permita clasificar una planta y para el que tendrá que
  * incluir instrucciones if/else anidadas. Para ver los detalles, consulte el
  * ejercicio 2.4 que aparece en el libro pdf de la asignatura.
  *
  * En este ejercicio, tendrá que tener en cuenta que hay distintas preguntas:
  *    - ¿Tiene semillas?
  *    - ¿Tiene vasos conductores?
  *    - ¿Tiene frutos?
  *    - ¿Número de cotiledóneas?
  *
  * Y las posibles respuestas deben ser un carácter 's' para "Sí" (s) o un carácter
  * 'n' para "No". Lógicamente, la respuesta con un número se puede leer en un entero,
  * sin embargo, la solución deberá también usar un carácter (note que la respuesta es
  * un simple dígito).
  *
  * Como resultado deberá responder con una palabra que indica su calificación. En concreto,
  * podrá clasificarse como:
  *    - Briofitas
  *    - Pteridofitas
  *    - Monocotiledóneas
  *    - Dicotiledóneas
  *    - Gimnospermas
  *
  * Escriba el programa suponiendo que el usuario introduce una letra o un número sin equivocarse.
  *
  * Consulte ejemplos de ejecución en el pdf.
  * 
  */
#include <iostream>
using namespace std;

int main() {
  char semillas, vasos, frutos;
  int cotiledoneas;
  cout << "¿Tiene semillas? (s/n): ";
  cin >> semillas;

  if (semillas == 's') {
    cout << "¿Tiene frutos? (s/n): ";
    cin >> frutos;
    if (frutos == 's') {
      cout << "¿Número de cotiledoneas?";
      cin >> cotiledoneas;
      if (cotiledoneas == 1) {
        cout << "Monocotiledóneas" << endl;
      } else {
        cout << "Dicotiledoneas" << endl;
      }
    } else {
      cout << "Gimnospermas" << endl;
    }
  } else {
    cout << "¿Tiene vasos conductores?(s/n)";
    cin >> vasos;
    if (vasos == 's') {
      cout << "Pteridofitas" << endl;
    } else {
      cout << "Briofitas" << endl;
    }
    return 0;
  }
}
