/**
  * @file recuadro.cpp
  * @brief Programa para enmarcar un saludo
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea un número entero N desde la entrada estándar
  * y que a continuación dibuje con asteriscos, en la salida estándar, un
  * rectángulo de ancho N con un mensaje centrado con la palabra "Hola".
  * 
  * Para poder centrar la palabra, deberá tener al menos un valor de 8 y
  * ser par. Por tanto, si introducimos un valor menor, se escribrá con
  * tamaño 8 y si es mayor que 8 e impar, se añadirá uno al ancho.
  * 
  * A continuación vemos el resultado de tamaño N=7:
  *
  *      ********
  *      * Hola *
  *      ********
  * 
  * El resultado con tamaño N=9:
  *
  *      **********
  *      *  Hola  *
  *      **********
  * 
  */
#include <iostream>
using namespace std;

int main(){
  int N;

  cout << "Introduzca el ancho del recuadro: ";
  cin >> N;

  if(N<8){
    N = 8;
  }else if(N%2!=0){
    N++;
  }

  for(int i=1; i<=N; i++){
    cout << "*";
  }
  cout << endl;

  cout << "*";
  for(int i=1; i<=(N-6)/2; i++){
    cout << " ";
  }
  cout << "Hola";
  for(int i=1; i<=(N-6)/2; i++){
    cout << " ";
  }
  cout << "*";
  cout << endl;

  for(int i=1; i<=N; i++){
    cout << "*";
  }
  cout << endl;
}