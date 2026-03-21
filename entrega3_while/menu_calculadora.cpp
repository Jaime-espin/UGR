/**
  * @file menu_calculadora.cpp
  * @brief Menú para realizar operaciones básicas de calculadora
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea dos valores reales y que presente un menú con siete
  * alternativas:
  *    1. Suma
  *    2. Resta
  *    3. Producto
  *    4. División
  *    5. Modificar primer operando
  *    6. Modificar segundo operando
  *    7. finalizar el programa
  *
  * El programa deberá pedir al usuario que seleccione una de las opciones y presentar en la
  * salida estándar el resultado de la operación correspondiente.
  *
  * Tenga en cuenta que el usuario puede responder a la selección también con cualquiera de los
  * cuatro operadores + - * / para seleccionar alguna de las 4 opciones.
  *
  * Para ello, tenga en cuenta que el valor inicial de los operandos es cero, y que la solución
  * debe contener un bucle do-while junto con una instrucción switch para gestionar el menú.
  *
  */
#include <iostream>
using namespace std;

int main() {
  double a = 0;
  double b = 0;
  char opcion;

  cout << "Introduzca dos valores:";
    cin>>a >>b;

  do {
    cout << "Seleccione una opción:" << endl;
    cout << "1. Suma" << endl;
    cout << "2. Resta" << endl;
    cout << "3. Producto" << endl;
    cout << "4. División" << endl;
    cout << "5. Modificar primer operando" << endl;
    cout << "6. Modificar segundo operando" << endl;
    cout << "7. Finalizar" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;
    switch (opcion) {
      case '1':
      case '+':
        cout << "La suma es: " << a+b << endl;
        break;
      case '2':
      case '-':
        cout << "La resta es: " << a-b << endl;
        break;
      case '3':
      case '*':
        cout << "El producto es: " << a*b << endl;
        break;
      case '4':
      case '/':
        cout << "La división es: " << a/b << endl;
        break;
      case '5':
        cout << "Introduzca el primer operando: ";
        cin >> a;
        break;
      case '6':
        cout << "Introduzca el segundo operando: ";
        cin >> b;
        break;
      case '7':
        cout << "Finalizando programa...";
        break;
      default:
        cout << "Opción no valida"<<endl;
    }
  }while(opcion != '7');
}
