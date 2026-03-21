/**
  * @file matriz_simetrica.cpp
  * @brief Calcula si una matriz es simétrica
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa para leer una matriz cuadrada y escriba si es simétrica.
  * 
  * El programa recibe desde la entrada estándar una secuencia de datos que 
  * componen la matriz, recorriéndola por filas de arriba a abajo y de izquierda
  * a derecha. Estos datos vendrán precedidos por el número de filas y columnas.
  * 
  * El resultado es escribir la un mensaje sobre la simetría de la matriz. Recuerde
  * que es una matriz es simétrica si el elemento en la posición (f,c) es igual al que
  * está en la posición (c,f), para todas las posiciones. 
  * 
  * Por ejemplo, la ejecución puede ser:
  *    2 3
       1 2 3
       4 5 6
  *    La matriz no es simétrica porque no es cuadrada.
  *
  * Si introducimos:
  *    3 3
  *    1 2 3
  *    2 4 5
  *    3 5 6
  *    La matriz es simétrica.
  *
  * Si introducimos:
  *    3 3
  *    1 2 3
  *    2 4 5
  *    3 3 6
  *    La matriz no es simétrica.
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
          if(fila != colum){
               cout<<"La matriz no es simétrica porque no es cuadrada.";
          }else{
               int cont = 0;
               for(int i = 0; i<fila;i++){
                    for(int j = 0; j<colum; j++){
                         if(m[i][j]==m[j][i]){
                              cont ++;
                         }
                    }
               }
               if(cont==fila*colum){
                    cout<<"La matriz es simétrica.";
               }else{
                    cout<<"La matriz no es simétrica.";
               }
          }
     }
}