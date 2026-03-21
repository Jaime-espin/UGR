/**
  * @file primos_relativos.cpp
  * @brief Determina si dos números enteros positivos son primos relativos
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Escriba un programa que lee dos números enteros positivos y escribe en la 
  * salida estándar si son primos relativos. Deberá incluir las funciones:
  *  - Una función que pide repetidamente un número hasta que sea positivo.
  *  - Una función que recibe dos enteros positivos y determina su máximo
  *    común divisor. Use el algoritmo de Euclides.
  * 
  * Un ejemplo de ejecución es:
  *    Introduzca un entero positivo: -3
  *    El entero debe ser positivo, inténtelo de nuevo: 18
  *    Introduzca un entero positivo: 11
  *    Los números 18 y 11 son primos relativos.
  * 
  * Otro ejemplo puede ser el siguiente:
  *    Introduzca un entero positivo: 14
  *    Introduzca un entero positivo: 22
  *    Los números 14 y 22 no son primos relativos. Su MCD es: 2
  * 
  * Observe que en caso de que no sean primos relativos, la salida también
  * informa del máximo común divisor.
  * 
  */
#include <iostream>

using namespace std;

int MCD(int n1, int n2){
  int resto=n1%n2;
  while(resto!=0){
    n1=n2;
    n2=resto;
    resto=n1%n2;
  }
  return n2;
}

int main(){
  int n1, n2;

  cout <<"Introduzca un entero positivo: ";
  cin>>n1;
  while (n1<0){
    cout <<"El entero debe ser positivo, inténtelo de nuevo: ";
    cin>>n1;
  }
  cout <<"Introduzca un entero positivo: ";
  cin>>n2;
  while (n2<0){
    cout <<"El entero debe ser positivo, inténtelo de nuevo: ";
    cin>>n2;
  }

  if (MCD(n1, n2)==1){
    cout<<"Los números "<<n1<<" y "<<n2<<" son primos relativos.";
  }else{
    cout<<"Los números "<<n1<<" y "<<n2<<" no son primos relativos. Su MCD es: "<<MCD(n1, n2);
  }
}