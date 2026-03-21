/**
  * @file maximo_medias.cpp
  * @brief Programa para calculas el máximo de las medias
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa que lea una serie de temperaturas de diferentes ciudades
  * con el siguiente formato:
  *    N
  *    T11 T12 ... -300
  *    T21 T22 ... -300
  *    T31 T32 ... -300
  *    ...
  *    TN1 TN2 ... -300
  *
  * En donde N es el número de ciudades. Cada fila es la secuencia de temperaturas
  * de una ciudad. Cada fila puede tener un número diferente de medidas y siempre
  * acabará con un valor especial igual a -300 (centinela).
  *
  * El programa deberá calcular la temperatura media de cada ciudad y mostrará la
  * máxima de las temperaturas medias así como el número de ciudad a la que corresponde.
  *
  * A continuación puede ver un ejemplo de ejecución:
  *
  *    4
  *    13 15 15.6 14 -300
  *    8 12 -300
  *    24.5 27 23.2 24 25 -300
  *    23.7 27.4 29.1 -300
  *    Mayor temperatura media: 26.73333
  *    Ciudad: 4
  *
  * Observe que en este ejemplo hay 4 ciudades. A continuación se introducen 4
  * secuencias de datos (una por cada ciudad) y el programa obtiene la salida en las
  * dos últimas líneas.
  *
  * Cada secuencia consta de un número arbitrario de mediciones acabadas siempre
  * con un valor igual a -300. En concreto las medias para cada ciudad son:
  * 14.4, 10, 24.74 y 26.73 y por tanto, la media mayor es 26.73 que se  corresponde
  * con la ciudad número 4.
  *
  */
#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int N;
  const int centinela = -300;
  int numT=0;
  double T;
  int cityMax;
  double suma=0;
  double media=0;
  double mediaMax=0;

  cin >> N;

  for(int i=1; i<=N; i++){
    numT=0;
    suma=0;
    media=0;
    cin >> T;
    while(T!=centinela){
      suma = suma+T;
      cin >> T;
      numT ++;
    }
    media=suma/numT;
    if(media>mediaMax){
      mediaMax=media;
      cityMax=i;
    }
  }
  cout<<"Mayor temperatura media: "<<mediaMax<<endl;
  cout<<"Ciudad: "<<cityMax<<endl;
}