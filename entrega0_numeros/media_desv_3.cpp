/**
  * @file media_desv_3.cpp
  * @brief Programa para calcular media y desviación con 3 valores (Ej. 1.17)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Lectura de tres valores desde el teclado y salida de dos valores:
  * la media aritmética y la desviación estándar. Las expresiones son las siguientes:
  *
  *  (véase ejercicio 1.17)
  */

  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    double v1, v2, v3;
    double media, desv;

    cout<<"escribe el primer valor: "<<endl;
    cin>>v1;

    cout<<"escribe el segundo valor: "<<endl;
    cin>>v2;

    cout<<"escribe el tercer valor: "<<endl;
    cin>>v3;

    media=((v1+v2+v3)/3);
    cout<<"la media de los valores es: "<<media<<endl;

    desv=(sqrt((pow(v1-media, 2)+pow(v2-media, 2)+pow(v3-media, 2))/3));
    cout<<"la desviacion de los valores es: "<<desv<<endl;
  }
