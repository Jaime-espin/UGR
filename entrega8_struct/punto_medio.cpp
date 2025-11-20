/**
  * @file punto_medio.cpp
  * @brief Punto medio entre dos puntos
  *
  * @author Fulanito...
  * @date Mes-Año
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
  * el punto central. Este punto es el que se sitúa entre los dos a igual distancia,
  * es decir, el punto medio.
  * 
  * En la solución debe:
  *    - Definir una estructura para almacenar un punto en el plano.
  *    - Definir una función que lee un punto desde la entrada estándar.
  *    - Definir una función que escribe un punto en la salida estándar.
  *    - Definir una función que calcula el punto medio desde dos puntos.
  *
  * Recuerde que el punto medio entre dos puntos se puede calcular como el punto
  * con coordenadas la media de las X y la media de las Y.
  * 
  * La entrada consta de dos puntos con el formato anterior y la salida se deberá
  * escribir con el mismo formato. Por ejemplo, una posible ejecución es:
  *
  *    Introduzca dos puntos: (0,0) (1,1)
  *    El punto medio es: (0.5,0.5)
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

void EscribePunto(Punto p){
  cout<<"("<<p.x<<","<<p.y<<")";
}

Punto Media(Punto p1, Punto p2){
  Punto media;
  media.x = (p1.x+p2.x)/2;
  media.y = (p1.y+p2.y)/2;
  return media;
}

int main(){
  cout<<"Introduzca dos puntos: ";
  Punto p1 = LeerPunto();
  Punto p2 = LeerPunto();
  Punto media;
  media = Media(p1, p2);
  cout << "El punto medio es: ";
  EscribePunto(media);
}