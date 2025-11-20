/**
  * @file pares_impares.cpp
  * @brief Clasificar una secuencia de enteros
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa para clasificar los valores de entrada en pares e impares. 
  * 
  * La entrada de datos se realizará leyendo valores hasta que se lea un valor no
  * positivo.  El resultado será escribir en la salida estándar los valores pares
  * seguidos de los impares, ambos como secuencias encabezadas con el número de
  * datos.
  * 
  * Una posible ejecución puede ser:
  *     1 2 3 4 5 6 7 8 9 -1
  *     4   2 4 6 8
  *     5   1 3 5 7 9
  * 
  * Otra posible ejecución es:
  *     1 1 3 1 -1
  *     0
  *     4   1 1 3 1
  * 
  * Observe que la primera línea son los datos de entrada (terminados en no
  * positivo) y las dos siguientes son el resultado.
  * 
  * Para resolverlo, escriba el código completamente en la función main, sin
  * otras funciones auxiliares. 
  * 
  */
#include <iostream>

using namespace std;

int main(){
  int n;
  int pares[1000];
  int impares[1000];
  int tamañoP = 0;
  int tamañoI = 0;
  
  cin >> n;
  while ( n > 0 && (tamañoP + tamañoI) < 1000) {
    if(n%2==0){
        pares[tamañoP] = n;
        tamañoP++;
      }else{
        impares[tamañoI] = n;
        tamañoI++;
      }
      cin >> n;
  }

  cout << tamañoP<<"   ";
  for (int i = 0; i < tamañoP; i++) {
        cout <<" "<< pares[i];
    }
  cout << endl;
  cout << tamañoI<<"   ";
  for (int i = 0; i < tamañoI; i++) {
        cout <<" "<< impares[i];
    }
}