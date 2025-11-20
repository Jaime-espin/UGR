/**
  * @file 3digitos.cpp
  * @brief Operar con dígitos enteros (Ej. 1.13)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que lea en una variable de tipo int un valor entero de 3
  * dígitos (podemos suponer que el usuario escribirá sin equivocarse un número
  * de 3 dígitos). A continuación el programa mostrará los 3 dígitos del número: uno
  * en cada línea.
  *
  */

  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    int num;
    int d1, d2, d3;

    cout<<"Intrduzca un número de tres dígitos"<<endl;
    cin>>num;

    d1=(num/100);
    cout<<d1<<endl;
    d2=((num/10) % 10);
    cout<<d2<<endl;
    d3=(num % 10);
    cout<<d3<<endl;
  }
