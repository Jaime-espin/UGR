/**
  * @file invertir_letras.cpp
  * @brief Invierte los caracteres de una cadena
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que obtenga en la salida estándar los mismos caracteres que
  * hemos introducido pero en orden inverso.
  *
  * La entrada es un texto que acaba en un carácter centinela '#'. El texto tiene
  * un tamaño indeterminado. Para evitar problemas de la codificación al probarlo,
  * supondremos que los caracteres corresponden a la primera parte de la tabla ASCII,
  * es decir, sin caracteres especiales como las letras 'ñ', 'ç', etc.
  *
  * Para realizar la lectura de los caracteres usaremos la operación "get" de cin,
  * es decir, extraeremos un carácter desde la entrada con el código:
  *    char c;
  *    c= cin.get();
  *
  * Operación que se repetirá hasta que el carácter sea el centinela.
  *
  * Un ejemplo de ejecución es:
  *    abcde#
  *    edcba
  *
  * donde la primera línea es la entrada que hemos introducido y la segunda es la
  * salida del programa.
  *
  * Para resolverlo, escriba un programa con dos partes: la primera lee el vector
  * de objetos char hasta el centilena y la segunda escribe el vector al revés,
  * es decir, comenzando en el último carácter y terminando en el primero.
  *
  * Pruebe el programa insertando un texto más complejo, como:
      En un lugar de la Mancha, de cuyo nombre no quiero acordarme, no ha mucho
      tiempo que vivia un hidalgo de los de lanza en astillero, adarga antigua,
      rocin flaco y galgo corredor.#
  *
  * Note que el último carácter es el centinela para que el programa determine el final.
  */
  #include <iostream>

using namespace std;

int main(){
    const int MAX = 1000;
    char caracteres[MAX];
    int n = 0;
    char c;

    cout << "Introduzca una secuencia de caracteres terminada en '#': ";
    c = cin.get();
    
    while ( c != '#' && n < MAX) {
        caracteres[n] = c;
        n ++;
        c= cin.get();
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << caracteres[i];
    }
    cout << endl;

}
