/**
  * @file polar2cartesianas.cpp
  * @brief Convierte pareja de polares a cartesianas
  *
  * @author Fulanito...
  * @date Mes-Año
  *
  * Escriba un programa C++ que transforme las coordenadas polares de un
  * punto a coordenadas cartesianas.
  *
  * Tenga en cuenta que dado un punto (x,y), sus coordenadas polares
  * corresponden a los valores (r,theta) donde el valor de r es la distancia
  * del punto al origen y el valor de theta es el ángulo que forma con el
  * eje de abscisas.
  *
  * Un ejemplo de ejecución es:
  *    Introduzca coordenadas polares: 1.4142 45
  *    Coordenadas cartesianas: 1 1
  *
  */
  #include <iostream>
  #include <cmath>
  using namespace std;

  int main(){
    double x, y;
    double r, theta;

    cout<<"escribe la coordenada polar r: "<<endl;
    cin>>r;

    cout<<"escribe coordenada polar theta: "<<endl;
    cin>>theta;

    x=r*cos(theta * 3.1416/180);
    y=r*sin(theta * 3.1416/180);

    cout<<"Las coordenadas polares resultatntes son X = " << x << " e Y = " << y << ""<<endl;

  }
