/**
  * @file equilibrio_rango.cpp
  * @brief Programa para calcular el rango donde se sitúan los datos y su simetría
  * 
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que:
  *   - lee una secuencia de valores en un vector
  *   - calcula el mínimo y máximo de los valores introducidos y 
  *   - finalmente indica si hay más datos en la primera mitad del intervalo, 
  *     en la segunda o están equilibrados.
  * 
  * La entrada de datos consisten en un número entero (el número de datos)
  * seguido de tantos valores reales como indica dicho número.
  * 
  * Por ejemplo, una ejecución de este programa podría ser:
  *    5  -9 4 8 11 4
  *    Rango de datos en [-9 , 11]
  *    Mayoría en la derecha: 80%
  * 
  * Otro ejemplo:
  *    0
  *    Rango de datos no calculable.
  *
  * Otro ejemplo:
  *    5  -9 4 -6 11 1
  *    Rango de datos en [-9 , 11]
  *    Sin mayoría: equilibrado
  *
  * donde puede ver que el mensaje de equilibrio se debe a que hay 2 datos a la
  * izquierda del centro y 2 datos a la derecha. Note que dado que la izquierda
  * es -9 y la derecha es 11, el centro es 1.
  *
  * En el caso de un solo dato o un rango de tamaño cero, también indicaremos 
  * que no hay equilibrio. Por ejemplo:
  *    2  3 3
  *    Rango de datos en [3 , 3]
  *    Sin mayoría: rango no divisible
  * 
  * Para resolverlo, escriba el código completamente en la función main, sin
  * otras funciones auxiliares. La función main tendrá dos partes, la primera
  * para cargar los datos en un vector y la segunda para resolver el problema.
  * 
  */
#include <iostream>

using namespace std;

int main(){
  int n;
  int vector[100];

  cout << "Introduzca secuencia: ";
  cin >> n;

  if (n<=0){
      cout <<"Rango de datos no calculable."<<endl;
  }else{

    int sumaMed=0;
    for (int i = 0; i < n; i++) {
      cin >> vector[i];
      sumaMed = sumaMed + vector[i];
    }
    cout << endl;

    int media = sumaMed/n;

    int min = vector[0];
    int max = vector[0];
    for (int i = 0; i < n; i++){
      if (vector[i]>max){
        max = vector[i];
      }else if (vector[i]<min){
      min = vector[i];
      }
    }

    cout << "Rango de datos ["<<min<<","<<max<<"]"<<endl;

    double suma1 = 0.0;
    double suma2 = 0.0;
     for (int i = 0; i < n; i++) {
      if (vector[i] == sumaMed){
      } else if (vector[i] > media){
        suma2 ++;
      } else if (vector[i] < media){
        suma1 ++;
      }
    }

    double porcentaje;
    if (min == max || n == 1){
      cout<<"Sin mayoría: rango no divisible";
    }else if(suma1 == suma2){
      cout<<"Sin mayoría: equilibrado";
    } else if (suma1 > suma2){
      porcentaje=(suma1/n)*100;
      cout<<"Mayoria en la izquierda: "<<porcentaje<<"%";
    } else if(suma2 > suma1){
      porcentaje=(suma2/n)*100;
      cout<<"Mayoria en la derecha: "<<porcentaje<<"%";
    }
  }
}