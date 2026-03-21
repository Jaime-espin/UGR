/**
  * @file op_infijo.cpp
  * @brief Programa para realizar una operación simple entre dos números
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que haga las funciones de una calculadora básica. Para ello,
  * deberá leer una operación y escribir en la salida el resultado.
  * 
  * La operación se escribe en notación infija, es decir, como de forma habitual
  * especificando un operando, el operador y el segundo operando.
  * 
  * Por ejemplo, antes esta entrada:
  *    34.5 + 12
  * el programa mostrará la salida:
  *    46.5
  * 
  * Los operandos son valores reales y los operadores pueden ser:
  *    - Suma: +
  *    - Resta: -
  *    - Producto: *
  *    - División: /
  *    - Módulo: %
  *    - Potencia: ^
  * 
  * Tenga en cuenta que son números reales, por tanto, el módulo debe resolverse con 
  * la función fmod y la potencia con pow.
  * 
  * Si el usuario usa un carácter distinto a los que se han listado, deberá terminar
  * con un mensaje: "Error: operación desconocida."
  * 
  * La solución para seleccionar la operación debe implementarse mediante una
  * instrucción switch.
  */
#include <iostream>
#include <cmath>
using namespace std;

int main() {
  double a, b;
  char op;
  cout << "Introduzca la operacion que desee realizar: "<<endl;
  cin >> a >> op >> b;
  cout << "El resultado de la operacion es: ";
  switch(op){
    case '+':
      cout << a + b << endl;
      break;
    case '-':
      cout << a - b << endl;
      break;
    case '*':
      cout << a * b << endl;
      break;
    case '/':
      cout << a / b << endl;
      break;
    case '%':
      cout << fmod(a, b) << endl;
      break;
    case '^':
      cout << pow(a, b) << endl;
      break;
    default:
      cout << "Error: operación desconocida." << endl;
  }
}
