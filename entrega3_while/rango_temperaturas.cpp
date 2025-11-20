/**
  * @file rango_temperaturas.cpp
  * @brief Calcula el rango de temperaturas (mínimo, máximo, lectura anticipada, centinela)
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Escriba un programa que lee una secuencia de valores de temperatura hasta que se 
  * introduce una temperatura menor que el cero absoluto (-273,15 grados centígrados).
  * 
  * El programa debe escribir como resultado el intervalo mínimo donde se sitúan el
  * conjunto de temperaturas.
  * 
  * Por ejemplo, si se introducen los siguientes valores:
  *      2.5 3 6 7.1 1 -300
  * El programa deberá escribir: 5 datos en el rango [1,7.1]
  * 
  * Si se introducen los valores:
  *      -5 -4 -10 -2 -300
  * El programa deberá escribir: 4 datos en el rango [-10,-2]
  * 
  * Si se introduce:
  *      -300
  * El programa deberá escribir: No hay datos
  * 
  */
#include <iostream>
using namespace std;

int main() {
  double n;
  double maximo = -273.15;
  int contador = 0;

  cout << "Introduzca datos: ";
  cin >> n;
  double minimo = n;
  while(n > -273.15) {
    if (n > maximo) {
      maximo = n;
    } else if (n < minimo) {
      minimo = n;
    }
    contador++;
    cin >> n;
  }
  if (contador == 0) {
    cout << "No hay datos" << endl;
  } else {
    cout <<"Hay " << contador << " datos en el rango [" << minimo << "," << maximo << "]" << endl;
  }

}