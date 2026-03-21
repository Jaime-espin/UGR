/**
  * @file contar_vocales.cpp
  * @brief Cuenta el número de vocales de un texto
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Escriba un programa que cuenta el número de vocales que contiene un texto. La
  * entrada del programa consiste en un texto que termina con el carácter 
  * delimitador '#' (también llamado centinela).
  * 
  * Un ejemplo de ejecución es:
  *    Esto es una prueba con
  *    un texto que finaliza con un centinela.#
  *    El número de vocales es: 24.
  *
  * Para resolver el problema, debe incluir una función que recibe un carácter y
  * devuelve si es una vocal.
  * 
  */
#include <iostream>

using namespace std;

bool esVocal(char c) {
   return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main() {
    char c;
    int contVocales = 0;

    cout << "Ingrese el texto que finaliza con un centinela (#):" << endl;
    cin.get(c);
    while ( c != '#') {
      if(esVocal(c)){
        contVocales++;
      }
      cin.get(c);
    }

    cout << "El número de vocales es: " << contVocales << endl;

}