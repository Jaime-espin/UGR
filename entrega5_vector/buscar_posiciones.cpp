/**
  * @file buscar_posiciones.cpp
  * @brief Programa para buscar las posiciones de un número en una secuencia
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lee una secuencia de números enteros y una vez cargada
  * lee un número a localizar. El resultado consiste listas las posiciones 
  * del número en la secuencia de entrada.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca secuencia: 5  2 3 6 7 1
  *    Valor a localizar: 3
  *    El valor está en posiciones: 1  1
  *
  * Otro ejemplo es:
  *    Introduzca secuencia: 5  2 3 6 7 1
  *    Valor a localizar: 4
  *    El valor está en posiciones: 0
  *
  * Otro ejemplo es con valores repetidos:
  *    Introduzca secuencia: 7  2 3 6 7 1 3 1
  *    Valor a localizar: 3
  *    El valor está en posiciones: 2  1 5
  *
  * Para resolver el problema, deberá escribir en la función main todo el código.
  * En concreto, deberá crear dos vectores-C con espacio suficiente de forma que:
  *    -# Cargamos el vector de entrada.
  *    -# Preguntamos el valor a localizar.
  *    -# Añadimos todas las posiciones localizadas en el segundo vector.
  *    -# Escribimos el resultado.
  *
  * Note que en el resultado primero escribimos el número de posiciones y luego
  * la lista de valores.
  *
  */
#include <iostream>

using namespace std;

int main(){
  int n, v, loc;
  int secuencia[1000];
  int localizar[1000];
  
  cout<<"Introduzca secuencia: ";
  cin >> n;
  for (int i=0; i<n; i++){
    cin >> v;
    secuencia[i]=v;
  }

  cout <<"Valor a localizar: ";
  cin >> loc;
  int posiciones = 0;
  for(int i=0; i<n; i++){
    if(secuencia[i]==loc){
      localizar[posiciones]=i;
      posiciones ++;
    }
  }

  cout <<"El valor está en posiciones: "<<posiciones<<"  ";
  for (int i=0; i<posiciones; i++){
    cout<<localizar[i]<<" ";
  }
}