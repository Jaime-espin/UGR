#include <iostream>
#include <cmath>
#include "camino.h"
using namespace std;

void agregarPunto(Camino & c, const Punto2D &p){
    Punto2D* nuevo = new Punto2D[c.util + 1];
    for (int i = 0; i < c.util; i++){
          nuevo[i + 1] = c.path[i];
    }
    nuevo[0] = p;
    delete [] c.path;
    c.path = nuevo;
    c.util++;
}

int puntoPertence(Camino & c, Punto2D p){
  for(int i = 0; i<c.util; i++){
    if(p.x==c.path[i].x && p.y==c.path[i].y){
      return i;
    }else{
      return c.util+1;
    }
  }
}
void borrarPunto(Camino & c, Punto2D p){
  int i = puntoPertence(c, p);
  if(i < c.util){
    Punto2D* nuevo = new Punto2D[c.util - 1];
    for(int j = 0; j < i; j++){
      nuevo[j] = c.path[j];
    }
    for(int j = i; j < c.util - 1; j++){
      nuevo[j] = c.path[j + 1];
    }
    delete [] c.path;
    c.path = nuevo;
    c.util--;
  }
}

double distanciaPuntos(Punto2D p1, Punto2D p2){
  double distancia;
  distancia= sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
  return distancia;
}
void masLejanos(Camino & c, Punto2D & p1, Punto2D & p2){
  double distMax=0;
  for(int i=0; i<c.util; i++){
    for(int j=1; j<c.util;j++){
      if(distanciaPuntos(c.path[i],c.path[j])>distMax){
        distMax=distanciaPuntos(c.path[i],c.path[j]);
        p1=c.path[i];
        p2=c.path[j];
      }
    }
  }

}

double longitud(Camino & c){ //Tengo que pasar los puntos de forma ordenada
  double longitud=0;
  for(int i=0; i<c.util; i++){
    for(int j=1; j<c.util; j++){
      longitud+=distanciaPuntos(c.path[i],c.path[j]);
    }
  }
  return longitud;
}
void unirCaminos(Camino c1, Camino c2, Camino &c){

}
void mostrarCamino(Camino c){
  cout<<c.util<<" -> ";
  for(int i=0; i<c.util; i++){
    cout<<"(" << c.path[i].x << "," << c.path[i].y << ") ";
  }
  cout<<endl;
}
