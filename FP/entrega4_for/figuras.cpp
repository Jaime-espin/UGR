/**
  * @file figuras.cpp
  * @brief Programa para dibujar figuras en la consola
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea un número entero N desde la entrada estándar
  * y que a continuación dibuje con asteriscos, en la salida estándar, las 
  * siguientes figuras:
  *    - Triángulo de lado N
  *    - Cuadrado hueco de lado N
  * A continuación vemos una muestra de estas figuras para N=7:
  *
  *      *
  *      **
  *      ***
  *      ****
  *      *****
  *      ******
  *      *******
  *
  *      *******
  *      *     *
  *      *     *
  *      *     *
  *      *     *
  *      *     *
  *      *******
  * 
  */
#include <iostream>
using namespace std;

int main(){
  int N;

  cout << "Introduzca N: ";
  cin >> N;

  for(int i=1; i<=N; i++){
    for(int j=1;j<=i;j++){
      cout << "*";
    }
    cout << endl;
  }
  cout << endl;
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      if(i==1 || i==N || j==1 || j==N){
        cout << "*";
      }else{
        cout << " ";
      }
    }
    cout << endl;
  }

  
}