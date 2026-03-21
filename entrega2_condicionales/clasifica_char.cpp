/**
  * @file clasifica_char.cpp
  * @brief Programa para clasificar un carácter ASCII
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que permita conocer la clasificación de un carácter. Para ello,
  * supondremos que se introduce un carácter ASCII puro, es decir, de la primera mitad
  * de la tabla ASCII extendida.
  * 
  * El programa debe declarar variables booleanas que almacenen si el carácter es:
  * 
  *    - Un dígito numérico.
  *    - Una letra mayúscula del alfabeto inglés.
  *    - Una letra minúscula del alfabeto inglés.
  *    - Una letra del alfabeto inglés.
  *    - Un operador aritmético (+,-,*,/)
  *    - Otro carácter (ninguno de los anteriores)
  * 
  * Una vez tenemos las variables con el valor correspondiente, el programa deberá
  * escribir en la salida estándar su valor. Por ejemplo, una ejecución del programa
  * podría ser:
  *    Introduzca un carácter: A
  *    El carácter A, con código ASCII 65, se puede clasificar:
  *       Dígito: 0
  *       Mayúscula: 1
  *       Minúscula: 0
  *       Letra: 1
  *       Operador: 0
  *       Otros: 0
  * 
  * donde se puede ver que la escritura de valores booleanos produce un valor numérico.
  *
  * Otro ejemplo de ejecución podría ser:
  *    Introduzca una carácter: @
  *    El carácter @, con código ASCII 64, se puede clasificar:
  *       Dígito: 0
  *       Mayúscula: 0
  *       Minúscula: 0
  *       Letra: 0
  *       Operador: 0
  *       Otros: 1
  * 
  * Recuerde que en la solución no será necesaria ninguna instrucción if/else, sólo el
  * manejo de booleanos.
  * 
  * Para la escritura del valor ASCII correspondiente, puede usar un casting de conversión
  * a entero.
  * 
  */
#include <iostream>
using namespace std;

int main() {
  char c;
  bool digito, mayus, minus, letra, operador, otro;

  cout << "Introduzca un caracter: ";
  cin >> c;

  digito = (c >= '0' && c <= '9');
  mayus = (c >= 'A' && c <= 'Z');
  minus = (c >= 'a' && c <= 'z');
  letra = (mayus || minus);
  operador = (c == '+' || c == '-' || c == '*' || c == '/');
  otro = (!digito && !letra && !operador);

  cout << "El caracter " << c << ", con codigo ASCII " << (int)c << ", se puede clasificar:" << endl;
  cout << "   Digito: " << digito << endl;
  cout << "   Mayuscula: " << mayus << endl;
  cout << "   Minuscula: " << minus << endl;
  cout << "   Letra: " << letra << endl;
  cout << "   Operador: " << operador << endl;
  cout << "   Otros: " << otro << endl;

  return 0;
}
