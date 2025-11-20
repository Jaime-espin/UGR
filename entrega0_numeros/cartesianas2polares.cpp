/**
  * @file cartesianas2polares.cpp
  * @brief Convierte pareja de cartesianas a polares
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que transforme las coordenadas cartesianas de un
  * punto a coordenadas polares.
  *
  * Tenga en cuenta que dado un punto (x,y), sus coordenadas polares
  * corresponden a los valores (r,theta) donde el valor de r es la distancia
  * del punto al origen y el valor de theta es el ángulo que forma con el
  * eje de abscisas.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca punto x,y: 1 1
  *    Coordenadas polares: 1.41421 45
  *
  * Otro ejemplo de ejecución es:
  *    Introduzca punto x,y: -1 -1
  *    Coordenadas polares: 1.41421 -135
  *
  */
  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    double x, y;
    double r, theta;

    cout<<"escribe la coordenada x: "<<endl;
    cin>>x;

    cout<<"escribe coordenada y: "<<endl;
    cin>>y;

    r=sqrt(pow(x,2)+pow(y,2));
    theta=atan(x/y)*180/3.1416;

    cout<<"Las coordenadas cartesianas resultatntes son r = " << r << " e theta = " << theta << ""<<endl;

  }
