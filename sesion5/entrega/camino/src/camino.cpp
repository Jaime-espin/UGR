/*
NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
DNI: 75571535K
GRUPO DE PR´ACTICAS: Jueves
*/

#include <iostream>
#include <cmath>
#include <string>
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
  int pos=-1;
  for(int i = 0; i<c.util; i++){
    if(p.x==c.path[i].x && p.y==c.path[i].y){
      pos=i;
    }
  }
  return pos;
}
void borrarPunto(Camino & c, Punto2D p){
  int i = puntoPertence(c, p);
  if(i >= 0 && i < c.util){
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

double distancia(Punto2D p1, Punto2D p2){
  double distancia;
  distancia= sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
  return distancia;
}
void masLejanos(Camino & c, Punto2D & p1, Punto2D & p2){
  double distMax=0;
  for(int i=0; i<c.util; i++){
    for(int j=i+1; j<c.util;j++){
      if(distancia(c.path[i],c.path[j])>distMax){
        distMax=distancia(c.path[i],c.path[j]);
        p1=c.path[i];
        p2=c.path[j];
      }
    }
  }
}

Punto2D siguientePunto(Camino c, Punto2D p, bool* visitados){
  double distMin = 1e10;
  Punto2D siguiente;
  bool encontrado = false;

  for(int i=0; i<c.util; i++){
    if(!visitados[i]){
      double dist = distancia(p, c.path[i]);
      if(dist < distMin && dist > 0){
        distMin = dist;
        siguiente = c.path[i];
        encontrado = true;
      }
    }
  }
  return siguiente;
}

double longitud(Camino & c){
  

  Punto2D p1, p2;
  masLejanos(c, p1, p2);

  double longitudTotal = 0.0;
  Punto2D actual = p1;
  Punto2D siguiente;

  int puntosVisitados = 1;
  bool* visitados = new bool[c.util];
  for(int i = 0; i < c.util; i++) {
    visitados[i] = false;
  }
  bool encontrado=false;
  for(int i = 0; i < c.util || !encontrado; i++) {
    if(c.path[i].x == p1.x && c.path[i].y == p1.y) {
      visitados[i] = true;
      encontrado=true;
    }
  }
  encontrado=false;
  while(puntosVisitados < c.util) {
    siguiente = siguientePunto(c, actual, visitados);
    
    for(int i = 0; i < c.util || !encontrado; i++) {
      if(c.path[i].x == siguiente.x && c.path[i].y == siguiente.y && !visitados[i]) {
        visitados[i] = true;
        puntosVisitados++;
        encontrado=true;
      }
    }

    longitudTotal += distancia(actual, siguiente);
    actual = siguiente;
  }
  
  delete [] visitados;
  if(c.util < 2) {
    longitudTotal=0.0;
  }
  return longitudTotal;
}

void unirCaminos( Camino &c, Camino c1, Camino c2){
  c.path = nullptr;
  c.util = 0;

  int total = c1.util + c2.util;
  Punto2D* todos = new Punto2D[total];
  int k = 0;

  for (int i = 0; i < c1.util; i++) {
    todos[k++] = c1.path[i];
  }
  for (int i = 0; i < c2.util; i++) {
    todos[k++] = c2.path[i];
  }

  bool* visitados = new bool[total];
  for(int i=0; i<total; i++){
    visitados[i]=false;
  }
  Punto2D actual = c1.path[0];
  agregarPunto(c, actual);

  bool encontrado=false;
  for (int i = 0; i < total || !encontrado; i++) {
    if (todos[i].x == actual.x && todos[i].y == actual.y) {
      visitados[i] = true;
      encontrado=true;
    }
  }

  for (int usados = 1; usados < total; usados++) {
    double minDist = 1e10;
    int indiceMin = -1;

    for (int i = 0; i < total; i++) {
      if (!visitados[i]) {
        double d = distancia(actual, todos[i]);
          if (d < minDist) {
          minDist = d;
          indiceMin = i;
        }
      }
    }

    if (indiceMin != -1) {
      agregarPunto(c, todos[indiceMin]);
      visitados[indiceMin] = true;
      actual = todos[indiceMin];
    }
  }

  delete[] todos;
  delete[] visitados;
}
void mostrarCamino(Camino c){
  cout<<c.util<<" -> ";
  for(int i=0; i<c.util; i++){
    cout<<"(" << c.path[i].x << "," << c.path[i].y << ") ";
  }
  cout<<endl;
}

string toString(Punto2D p){
  return "(" + to_string(p.x) + "," + to_string(p.y) + ")";
}

void liberaMemoria(Camino &c) {
    delete[] c.path;
    c.path = nullptr;
    c.util = 0;
}