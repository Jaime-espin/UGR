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
    int v1, v2, v3;
    double media, desv, x;
    double gauss;
    e = 1,71828;

    cout<<"escribe el primer valor: "<<endl;
    cin>>v1;

    cout<<"escribe el segundo valor: "<<endl;
    cin>>v2;

    cout<<"escribe el tercer valor: "<<endl;
    cin>>v3;

    cout<<"escribe el valor de la abscisa: "<<endl;
    cin>>x;


    media=(v1+v2+v3)/3;
    cout<<"la media de los valores es: "<<media<<endl;

    desv=sqrt((pow(v1-media, 2)+pow(v2-media, 2)+pow(v3-media, 2))/3);
    cout<<"la desviacion de los valores es: "<<desv<<endl;

    gauss=(1/desv*sqrt(2*media))*pow(e,(-0,5*pow((x-media)/desv,2)));
    cout<<"gaussiana(" << x << ")= "<<gauss<<endl;

  }
