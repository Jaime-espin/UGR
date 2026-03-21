/**
  * @file distancia_puntos.cpp
  * @brief Distancia entre dos puntos
  *
  * @author Fulanito...
  * @date Noviembre-2021
  * 
  * El formato de escritura de un punto en el plano consta de la secuencia:
  *    - Carácter '('.
  *    - Coordenada X.
  *    - Carácter ','.
  *    - Coordenada Y.
  *    - Carácter ').
  * 
  * admitiendo, opcionalmente, separadores blancos en medio de dichos componentes.
  * 
  * Escriba un programa en C++ que lea dos puntos y escriba en la salida estándar
  * la distancia euclídea entre los dos puntos.
  * 
  * En la solución debe:
  *    - Definir una estructura para almacenar un punto en el plano.
  *    - Definir una función que lee un punto desde la entrada estándar.
  *    - Definir una función que calcula la distancia euclídea entre dos puntos.
  * 
  * La entrada consta de dos puntos con el formato anterior. Por ejemplo,
  * una posible entrada es:
  *
  * Un ejemplo de ejecución es el siguiente:
  *    Introduzca dos puntos: (0,0) (1,1)
  *    La distancia es: 1.41421
  * 
  * Puede suponer que el usuario introduce el formato indicado. No será necesario,
  * por tanto, controlar posibles errores de entrada.
  * 
  */
#include <iostream>
#include <cmath>

using namespace std;

struct Punto{
  double x;
  double y;
};

Punto LeerPunto(){
  Punto p;
  char parentesis1, coma, parentesis2;
  cin >> parentesis1 >> p.x >> coma >> p.y >> parentesis2;
  return p;
}
double Dist(Punto p1, Punto p2){
  double d;
  d = sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2));
  return d;
}

int main(){
  cout<<"Introduzca dos puntos: ";
  Punto p1 = LeerPunto();
  Punto p2 = LeerPunto();
  cout << "La distancia es: " << Dist(p1, p2) << endl;
}