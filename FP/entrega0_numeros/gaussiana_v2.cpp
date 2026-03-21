/**
  * @file gaussiana.cpp
  * @brief Cálculo del valor de una gaussiana (Ej. 1.20)
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * La expresión que define una función gaussiana es la siguiente:
  *
  * (véase ejercicio 1.20)
  *
  * Con valores 1, 2, 3, el resultado es gaussiana(3)= 0.120985
  */
  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    double e;
    double media, desv, x;
    double gauss;
    e = 1,71828;

    cout<<"escribe el la media: "<<endl;
    cin>>media;

    cout<<"escribe la desviacion: "<<endl;
    cin>>desv;

    cout<<"escribe el valor de la abscisa: "<<endl;
    cin>>x;


    gauss=(1/desv*sqrt(2*media))*pow(e,((-1/2)*pow((x-media)/desv,2)));
    cout<<"gaussiana(" << x << ")= "<<gauss<<endl;

  }
