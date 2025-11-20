/**
  * @file suma_matrices.cpp
  * @brief Lee dos matrices y escribe la suma, si es posible.
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa para leer dos matrices de números reales y, en caso de
  * tener iguales dimensiones, escriba la suma.
  * 
  * Recuerde que, dadas dos matrices, la matriz suma tendrá en la posición (f,c)
  * la suma de los elementos de dicha posición en cada una de las matrices de entrada.
  * 
  * La escritura de la matriz tiene el mismo formato de entrada, es decir, las 
  * dimensiones --filas y columnas-- seguida de los elementos que la componen.
  * 
  * Por ejemplo, la ejecución puede ser:
  *     2 3
  *     1 2 3
  *     4 5 6
  *     2 3
  *     1 1 1
  *     1 1 1
  *     
  *     2 3
  *     2 3 4
  *     5 6 7
  * donde las dos primeras matrices las ha introducido el usuario y la última es el
  * resultado de la suma.
  * 
  * Otro ejemplo:
  *     2 3
  *     1 2 3
  *     4 5 6
  +     2 2
  +     1 1
  *     1 1
  *     Error: no es posible sumar matrices de distintas dimensiones.
  *
  * El código deber realizarse completamente en la función main.
  * 
  */
#include<iostream>

using namespace std;

int main(){
  const int N=30;
  const int M=30;
  double m1[N][M];
  double m2[N][M];
  double m[N][M];
  int fila, colum, fila2, colum2;

  cin>>fila>>colum;
  for(int i = 0; i<fila;i++){
    for(int j = 0; j<colum; j++){
      cin >> m1[i][j];
    }
  }
  cin>>fila2>>colum2;
  for(int i = 0; i<fila2;i++){
    for(int j = 0; j<colum2; j++){
      cin >> m2[i][j];
    }
  }
  if(fila!=fila2 || colum!=colum2){
    cout<<"Error: no es posible sumar matrices de distintas dimensiones.";
  }else{
    for(int i = 0; i<fila;i++){
      for(int j = 0; j<colum; j++){
        m[i][j]=m1[i][j]+m2[i][j];
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