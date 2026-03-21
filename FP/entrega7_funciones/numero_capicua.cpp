/**
  * @file numero_capicua.cpp
  * @brief Determina si un número entero es capicúa mediante cálculos numéricos
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Escriba un programa para determinar si un número positivo es capicúa. Para ello, 
  * deberá incluir tres funciones:
  * 
  *  - Una función que pide repetidamente un número hasta que sea positivo.
  *  - Una función que recibe un entero positivo y devuelve el número resultante tras
  *    invertir el orden de los dígitos. Por ejemplo, si recibe el 123, deberá devolver 
  *    el entero 321. Note que deberá trabajar con el tipo int, es decir, lo debe 
  *    resolver mediante cálculos numéricos.
  *  - Una función que recibe un entero y devuelve si es capicúa. Si el entero es no 
  *    positivo, se considera no capicúa. Si es positivo, deberá compararlo con el número
  *    que resulta de dar la vuelta a los dígitos.
  * 
  * Por ejemplo, una ejecución podría ser la siguiente:
  *    Introduzca un entero: -3
  *    El entero debe ser positivo, introduzca otro: 18
  *    El número 18 no es capicúa.
  * 
  * Otro ejemplo, con un número capicúa puede ser:
  *    Introduzca un entero: 123454321
  *    El número 123454321 es capicúa.
  * 
  */
#include <iostream>

using namespace std;

int Positivo(int n){
  while(n<0){
    cout<<"El entero debe ser positivo, introduzca otro: ";
    cin>>n;
  }
  return n;
}
int InvertirNumero(int n){
  int n_invert=0;
  while(n>0){
    int digito=n%10;
    n_invert = n_invert*10+digito;
    n=n/10;
  }
  return n_invert;
}
bool EsCapicua(int n){
  int n_invert=InvertirNumero(n);
  cout << n_invert;
  if(n==n_invert){
    return true;
  }else{
    return false;
  }
}

int main(){
  int n;
  cout<<"Introduzca un número entero positivo: ";
  cin>>n;
  n=Positivo(n);
  if (EsCapicua(n)){
    cout<<"El número "<< n <<" es capicúa.";
  }else{
    cout<<"El número "<< n <<" no es capicúa.";
  }
}