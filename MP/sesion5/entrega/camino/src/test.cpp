#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include "test.h"
#include "camino.h"

using namespace std;

// guarda n puntos con formato (ini, ini), (ini+1, ini+1)....
void rellena(Camino & cam, int n, int ini);
// genera un número entero al azar entre [min, max)
int nroAzar(int min, int max);
void mostrarCartel(string s);



void test1(){
  mostrarCartel("Prueba 1: agregar - mostrar - liberar");
  Camino cam = {0, 0};
  rellena(cam, 10, 0);
  assert(cam.util == 10);
  mostrarCamino(cam);
  liberaMemoria(cam);
}


void test2(){
  mostrarCartel("Prueba 2: agregar - mostrar - borrar");
  Camino cam = {0,0};
  rellena(cam, 11, 0);
  cout << endl;
  mostrarCamino(cam);
  int pos;
  Punto2D aux;
  
  int elems = cam.util;
  for(int i = 0; i < 4; i++){
    pos = nroAzar(0, cam.util-1);
    aux = cam.path[pos];
    borrarPunto(cam, aux);
    agregarPunto(cam, aux);
    assert(cam.util == elems);
    //cout << "Elemento: " << pos << " Tamaño: " << cam.util << endl;
    mostrarCamino(cam);
  }
  liberaMemoria(cam);
}


void test3(){
  mostrarCartel("Prueba 3: longitud - más lejanos");
  Camino cam = {0,0};
  Punto2D p1 = {0,0};
  Punto2D p2 = {0,1};
  Punto2D p3 = {1,1};
  Punto2D p4 = {1,0};
  
  agregarPunto(cam, p1);
  agregarPunto(cam, p2);
  agregarPunto(cam, p3);
  agregarPunto(cam, p4);
  
  mostrarCamino(cam);
  
  float aux = longitud(cam);
  assert(aux == 3.0);
  cout << "Longitud: " << aux  << endl;
  
  cout << "Agrego punto lejos " << endl;
  Punto2D aux1 = {100, 0};
  
  agregarPunto(cam, aux1);
  
  masLejanos(cam, p1, p2);
  assert(p1.x == 100 && p1.y == 0);
  assert(p2.x == 0 && p2.y == 1);
  aux = distancia(p1, p2);
  
  assert(aux > 100);
  
  cout << "Puntos más lejanos " << toString(p1) << " " << toString(p2) << endl;
  cout << "distancia " << aux << endl;
  liberaMemoria(cam);
}

void test4(){
  mostrarCartel("Prueba 4: rellenar - vaciar - rellenar");
  Camino cam = {0,0};
  rellena(cam, 4, 0);
  mostrarCamino(cam);
  Punto2D aux;
  for(int i=0; i<4; i++){
    aux = cam.path[0];
    borrarPunto(cam, aux);
    mostrarCamino(cam);
  }
  rellena(cam, 4, 0);
  mostrarCamino(cam);
  liberaMemoria(cam);
}


void test5(){
  mostrarCartel("Prueba 5: unir caminos");
  Camino c1 = {0,0}, c2 = {0,0}, c3 = {0,0};
  rellena(c1, 3, 0);
  rellena(c2, 3, 5);
  unirCaminos(c3, c1, c2);
  mostrarCamino(c1);
  mostrarCamino(c2);
  mostrarCamino(c3);
  
  liberaMemoria(c1);
  liberaMemoria(c2);
  liberaMemoria(c3);
}

///
/// FUNCIONES AUXILIARES
///

void rellena(Camino & cam, int n, int ini){
  for(int i = ini; i < ini+n; i++){
    Punto2D nuevo = {i, i};
    agregarPunto(cam, nuevo);
  }
}

int nroAzar(int min, int max){
  return  (rand()% (max - min)) + min;
}

void mostrarCartel(string s){
  cout << endl << "*************************************" << endl;
  cout << "  " << s;
  cout << endl << "*************************************" << endl;
}
