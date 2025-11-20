/**
  * @file mediana_simple.cpp
  * @brief Programa para calcular la mediana de una secuencia de valores
  *
  * @author Fulanito...
  * @date Mes-Año
  * 
  * Escriba un programa que procese una secuencia de datos encabezada con 
  * la longitud para obtener el valor de la mediana. 
  * 
  * Recuerde que la mediana es el valor que se sitúa en el centro cuando 
  * los datos están ordenados. En caso de que haya un número par de datos, 
  * puede seleccionar cualquiera de los dos centrales.
  * 
  * Un ejemplo de ejecución es:
  *     9   6.1  1.5  2  1.9  2.6  6  2.1  2.2  4   
  *     Mediana de 9 valores: 2.2
  * 
  * donde la primera línea es la entrada del programa y la segunda el resultado.
  *
  * Para resolverlo, escriba el código completamente en la función main, sin
  * otras funciones auxiliares. La función main tendrá tres partes, la primera
  * para cargar los datos en un vector, la segunda para ordenar los valores y
  * la tercera para obtener el resultado consultando el elemento central.
  *
  */
#include <iostream>

using namespace std;

int main(){
  int n;
  double v;
  double secuencia[1000];
  
  cin >> n;
  for (int i=0; i<n; i++){
    cin >> v;
    secuencia[i]=v;
  }

  double aux;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n - i; j++) {
      if (secuencia[j] > secuencia[j + 1]) {
        aux = secuencia[j];
        secuencia[j] = secuencia[j + 1];
        secuencia[j + 1] = aux;
      }
    }
  }

  int posMed;
  posMed=n/2;
  cout << "Mediana de "<<n<<" valores: "<< secuencia[posMed];
}