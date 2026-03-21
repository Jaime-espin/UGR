/**
  * @file racional_struct.cpp
  * @brief Leer y escribir un número racional
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * El formato de lectura/escritura de un racional consta de:
  *    - Número entero correspondiente al numerador.
  *    - Carácter '/'.
  *    - Número entero correspondiente al denominador.
  * 
  * admitiendo, opcionalmente, separadores blancos en medio de dichos componentes.
  * 
  * Escriba un programa en C++ que lea un racional desde la entrada estándar y
  * vuelva a escribirlo en la salida estándar.
  *
  * En la solución debe:
  *    - Definir una estructura para almacenar un racional.
  *    - Definir una función que lee un racional desde la entrada estándar.
  *    - Definir una función que escribe un racional en la salida estándar.
  *    - Definir una función que calcula el irreducible de un racional.
  *
  * Para probar el código, se  implementará un sencillo main donde básicamente se
  * lee un racional y se vuelva a escribir de forma irreducible. Un ejemplo de
  * ejecución sería:
  *
  *    Introduzca un racional: 10/2
  *    El racional irreducible es: 5/1
  *
  * Otro ejemplo:
  *
  *    Introduzca un racional: -14/-70
  *    El racional irreducible es: -1/-5
  *
  * Para finalizar, pruebe el código introduciendo un racional como "10/0".
  * ¿Qué ocurre? ¿Cómo podemos evitar esta situación?
  * 
  */
#include <iostream>

using namespace std;

struct Racional{
  int numerador;
  int denominador;
};

Racional LeerRacional(){
  Racional r;
  char c;
  cin >> r.numerador >> c >> r.denominador;
  return r;
}
void EscribirRacional(Racional r){
  cout<<r.numerador<<"/"<<r.denominador;
}

int MCD(Racional r){
  int resto=r.numerador%r.denominador;
  while(resto!=0){
    r.numerador=r.denominador;
    r.denominador=resto;
    resto=r.numerador%r.denominador;
  }
  return r.denominador;
}

int main(){
  cout<<"Introduzca un racional: ";
  Racional r = LeerRacional();
  int mcd = MCD(r);
  r.numerador=r.numerador/mcd;
  r.denominador=r.denominador/mcd;
  cout<<"El racional irreducible es: ";
  EscribirRacional(r);
}