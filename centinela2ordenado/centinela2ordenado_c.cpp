/**
  * @file centinela2ordenado_c.cpp
  * @brief Programa para transformar secuencia con centinela a secuencia con número de datos
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Escriba un programa que transforme una secuencia de longitud indeterminada marcada con 
  * un centinela a una secuencia que comienza con el número de datos y sigue con los mismos 
  * valores ordenados pero sin centinela.
  * 
  * El programa lee una secuencia de valores reales hasta que se introduce un valor negativo.
  * 
  * Una vez cargada la secuencia, deberá escribirla de forma ordenada, encabezada con el 
  * número de datos y sin centinela.
  * 
  * Un ejemplo de ejecución donde hay 6 datos es:
  *     2.5 3.2 1.2 5.3 9 0.5 -1
  *     6  0.5 1.2 2.5 3.2 5.3 9
  * 
  * donde la primera línea corresponde a la entrada y la segunda a la salida.
  * 
  * Otro ejemplo, con una secuencia vacía:
  *     -1
  *     0
  * 
  * Para resolver el problema, debe tener en cuenta las siguientes condiciones:
  * - Deberá escribir en la función main todo el código.
  * - Deberá declarar un vector-C con una capacidad máxima de 10.
  * - En caso de que la secuencia no se pueda almacenar, terminará con un mensaje de aviso.
  * 
  * Por tanto, otro ejemplo de ejecución es:
  *     2.5 3.2 1.2 5.3 9 0.5 2.5 3.2 1.2 5.3 9 0.5 -1
  *     No hay capacidad para resolver el problema.
  * 
  */
#include <iostream>
using namespace std;

int main(){
  const int MAX = 10;
  double C[MAX];
  double valor;
  int n = 0;

  cin >> valor;
  while (valor >= 0 && n < MAX){
      C[n] = valor;
      n++;
      cin >> valor;
  }

  if (n >= MAX){
      cout << "No hay capacidad para resolver el problema." << endl;
  }else{
    double aux;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < n - i; j++) {
        if (C[j] > C[j + 1]) {
          aux = C[j];
          C[j] = C[j + 1];
          C[j + 1] = aux;
        }
      }
    }

    cout<<n<<"  ";
    for(int i=0; i<n; i++){
      cout<<C[i]<<" ";
    }
  }
}