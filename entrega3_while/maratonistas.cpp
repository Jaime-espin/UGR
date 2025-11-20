/**
  * @file maratonistas.cpp
  * @brief Procesa tiempos de llegada y determina el ganador
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Suponga una serie de datos correspondientes al resultado de una maratón. Los datos
  * consisten en varios valores por maratonista:
  * 
  *    - Número de dorsal. Los dorsales de corredores son número positivos.
  *    - Tiempo obtenido. El tiempo que ha necesitado para acabar la maratón. Está compuesto 
  *      de dos valores: horas y minutos.
  * 
  * Escriba un programa que lea los resultados de una carrera e indique quién es el ganador. 
  * El formato de entrada de valores será un valor de dorsal más el tiempo que ha necesitado
  * para terminar. El tiempo se especifica con un formato horas:minutos (vea el ejemplo más
  * abajo). 
  * 
  * Una ejemplo de ejecución es el siguiente:
  *      Introduzca los dorsales y tiempos correspondientes. Termine con el dorsal 0:
  *      5 1:37
  *      2 0:59
  *      9 1:04
  *      0
  *      Número de participantes: 3
  *      Primera posición corresponde al dorsal 2 con un tiempo de 0:59
  * 
  * donde puede ver que los datos terminan cuando se introduce un dorsal de número 0. 
  * El resultado del programa corresponde a las dos últimas líneas, donde aparece el número
  * de participantes seguido por el dorsal ganador y el tiempo correspondiente.
  * 
  * Debe tener en cuenta que también puede haber cero participantes; en este caso, el 
  * programa responde como sigue:
  * 
  *      Introduzca los dorsales y tiempos correspondientes. Termine con el dorsal 0:
  *      0
  *      Número de participantes: 0
  *      No hay ganador
  * 
  */
#include <iostream>
using namespace std;

int main() {
  int dorsal;
  char c;
  int dorsal_ganador;
  int horas, minutos;
  int horas_ganador, minutos_ganador;
  int participantes = 0;
  int tiempo_ganador = 1000000;

  cout << "Introduzca los dorsales y tiempos correspondientes. Termine con el dorsal 0:" << endl;
  cin >> dorsal;
  while(dorsal != 0) {
    cin >> horas >> c >> minutos;
    participantes++;
    if (horas*60 + minutos < tiempo_ganador) {
      tiempo_ganador = horas*60 + minutos;
      dorsal_ganador = dorsal;
      horas_ganador = horas;
      minutos_ganador = minutos;
    }
    cin >> dorsal;
  }

  if (participantes == 0) {
    cout << "Número de participantes: 0" << endl;
    cout << "No hay ganador" << endl;
  } else {
    cout << "Número de participantes: " << participantes << endl;
    cout << "Primera posición corresponde al dorsal " << dorsal_ganador << " con un tiempo de " << horas_ganador << ":" << minutos_ganador << endl;
  }
}