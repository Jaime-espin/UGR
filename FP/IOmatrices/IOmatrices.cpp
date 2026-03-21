/*
  * @file IOmatrices.cpp
  * @brief Operaciones básicas de leer/escribir matriz
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa para leer y escribir una matriz rectangular.
  * 
  * El programa recibe desde la entrada estándar una secuencia de datos que 
  * componen la matriz, recorriéndola por filas de arriba a abajo y de izquierda
  * a derecha. Estos datos vendrán precedidos por el número de filas y columnas.
  * 
  * El resultado es escribir la misma matriz. Puede probar a introducir la matriz:
  *    2 3
       1 2 3
       4 5 6
  *
  * Para que escriba con ese formato, es decir, primero las dimensiones y luego
  * cada fila en una línea.
  * 
  * La entrada asume que los elementos están separados por espacios blancos, por lo 
  * que puede dar la entrada en un formato distinto:
  *   3 2 1.2 4.5 2.3 5.6 3.4 6.7
  * 
  * Pero la salida la presentará separando las líneas (primera para las dimensiones y
  * una fila por línea):
  *    3 2
  *    1.2 4.5
  *    2.3 5.6
  *    3.4 6.7
  *
  *  Además, debe tener en cuenta que si alguna de las dimensiones es cero o negativa,
  *  las dos se consideran cero. Por ejemplo, con la entrada:
  *    0 3
  *  Deberá escribir la salida:
  *    0 0
  * 
  */
#include<iostream>

using namespace std;

int main(){
     const int N=30;
     const int M=30;
     double m[N][M];
     int fila, colum;

     cin>>fila>>colum;
     if(fila<=0 || fila<=0){
          fila=0;
          colum=0;
          cout<<fila<<" "<<colum<<endl;
     }else if(fila>N || colum>M){
          cout<<"Error: el numero de datos supera la memoria.";
     }else{
          for(int i = 0; i<fila;i++){
               for(int j = 0; j<colum; j++){
                    cin >> m[i][j];
               }
          }

          cout<<fila<<" "<<colum<<endl;
          for(int i = 0; i<fila;i++){
               for(int j = 0; j<colum; j++){
                    cout << m[i][j] << " ";
               }
               cout<<endl;
          }
     }
}