/**
  * @file traspuesta.cpp
  * @brief Matriz traspuesta
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa para leer una matriz rectangular y escribir su traspuesta.
  * 
  * El programa recibe desde la entrada estándar una secuencia de datos que 
  * componen la matriz, recorriéndola por filas de arriba a abajo y de izquierda
  * a derecha. Estos datos vendrán precedidos por el número de filas y columnas.
  * 
  * El resultado es escribir la misma matriz pero traspuesta. Recuerde que es la
  * matriz que tiene en la posición (f,c) el elemento que estaba en la posición
  * (c,f). Por ejemplo, si introducimos la matriz:
  *    2 3
       1 2 3
       4 5 6
  * 
  * Escribirá la matriz:
  *    3 2
  *    1 4
  *    2 5
  *    3 6
  *  
  * Observe que las dimensiones están en orden inverso y los elementos han cambiado
  * de posición (i,j) -> (j,i).
  * 
  * Recuerde que las dimensiones son enteros y los datos pueden tener decimales. Por
  * ejemplo, con la entrada:
  *   2 3
      1.2 2.3 3.4
      4.5 5.6 6.7
  *
  * Obtenemos la siguiente salida:
  *    3 2
  *    1.2 4.5
  *    2.3 5.6
  *    3.4 6.7
  * 
  */
#include <iostream>

using namespace std;

int main(){
    const int N=30;
    const int M=30;
    double m[N][M];
    int fila, colum;

    cin>>fila>>colum;
    for(int i = 0; i<fila;i++){
      for(int j = 0; j<colum; j++){
        cin >> m[i][j];
      }
    }

    cout<<colum<<" "<<fila<<endl;
    for(int i = 0; i<colum;i++){
      for(int j = 0; j<fila; j++){
        cout << m[j][i] << " ";
      }
      cout<<endl;
    }
}