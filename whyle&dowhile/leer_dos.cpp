/**
  * @file leer_dos.cpp
  * @brief Programa para comprobar la lectura de dos valores enteros
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Realice un programa que permita leer dos valores enteros, el primero negativo y el
  * segundo positivo. El programa debe repetir la lectura de cada uno de ellos hasta que se
  * cumpla la correspondiente condición.
  * 
  * El programa tendrá dos partes diferenciadas, la primera para leer el primer valor y 
  * la segunda para leer el segundo.
  * 
  * En el primero valor, se debe usar un bucle do-while, mientras que en el segundo debe
  * usarse un bucle while. Como condición, en el programa sólo habrá dos instrucciones
  * de lectura desde cin (una para el primer dato y otra para el segundo).
  *
  * Como resultado final, el programa escribe los dos números introducidos. Un ejemplo
  * de ejecución es:
  *    Introduzca negativo: -5
  *    Introduzca positivo: 10
  *    Los números son: -5 10
  *
  * Otro ejemplo, donde nos equivocamos varias veces es:
  *    Introduzca negativo: 5
  *    Introduzca negativo: 0
  *    Introduzca negativo: 3
  *    Introduzca negativo: -10
  *    Introduzca positivo: 0
  *    Introduzca positivo: 10
  *    Los números son: -10 10
  * 
  */
#include <iostream>
using namespace std;

int main() {
    int negativo;
    do {
        cout << "Introduzca negativo: ";
        cin >> negativo;
    } while (negativo >= 0);

    int positivo;
    while (positivo <= 0) {
        cout << "Introduzca positivo: ";
        cin >> positivo;
    }

    cout << "Los numeros son: " << negativo << " " << positivo << endl;
    return 0;
}
