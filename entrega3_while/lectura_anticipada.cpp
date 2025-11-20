/**
  * @file lectura_anticipada.cpp
  * @brief Programa para leer un valor real dentro de un intervalo
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Realice un programa que permita leer un número real en el intervalo [0,1]. El programa
  * debe diseñarse mediante una lectura anticipada, es decir, una lectura para el primer dato
  * y un bucle que implementa la repetición de la lectura hasta que el valor sea correcto.
  * 
  * Tenga en cuenta que dado que el primer dato se lee aparte, el mensaje para introducirlo
  * indicará el intervalo válido, mientras que en las siguientes entradas podemos usar un
  * mensaje que avisa de que el valor anterior no es válido.
  * 
  * Como resultado final, el programa debe escribir el dato introducido.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca valor en [0,1]: 2.3
  *    Está fuera, vuelva a intentarlo: -2.4
  *    Está fuera, vuelva a intentarlo: 0.3
  *    El valor introducido con éxito es 0.3
  * 
  */
#include <iostream>
using namespace std;

int main() {
    double valor;
    cout << "Introduzca valor en [0,1]: ";
    cin >> valor;
    while (valor < 0 || valor > 1) {
        cout << "Esta fuera, vuelva a intentarlo: ";
        cin >> valor;
    }
    cout << "El valor introducido con exito es " << valor << endl;
    return 0;
}