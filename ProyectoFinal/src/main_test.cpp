#include <iostream>
#include <cassert>
#include <cmath>
#include "util.hpp" // El módulo util proporciona la función aleatorio
#include "params.hpp" // El archivo de cabecera params.hpp proporciona las constantes
#include "particula.h"
using namespace std;

/* Conjunto de tests para Vector 2D */
void test_constructor_getset();
void test_suma();
void test_escalar();
void test_distancia();
void test_normalizar();
void test_toString();

/* Conjunto de tests para Particula */
void test_constructor_getset_particula();
void test_mover();
void test_rebotar();
void test_colision();
void test_choque();
void test_toString_particula();

int main() {
  
  cout << "\nEjecutando tests para Vector2D..." << endl;
  test_constructor_getset();
  test_suma();
  test_distancia();
  test_escalar();
  test_normalizar();
  test_toString();
  cout << "✅ Todos los tests de Vector2D han pasado bien." << endl;
  
  cout << "\nEjecutando tests para Particula..." << endl;
  test_constructor_getset_particula();
  test_mover();
  test_rebotar();
  test_colision();
  test_choque();
  test_toString_particula();
  cout << "✅ Todos los tests de Particula han pasado bien." << endl;
  
  return 0;
}


/* Conjunto de tests para Vector 2D */

void test_constructor_getset() {
  Vector2D v1;
  Vector2D v2(3.0, 4.0);
  
  assert(v1.getX() == 0.0);
  assert(v1.getY() == 0.0);
  v1.setXY(1.0, 2.0);
  assert(v1.getX() == 1.0);
  assert(v1.getY() == 2.0);
  
  assert(v2.getX() == 3.0);
  assert(v2.getY() == 4.0);
  v2.setX(5.0);
  v2.setY(5.0);
  assert(v2.getX() == 5.0);
  assert(v2.getY() == 5.0);
}


void test_suma() {
  Vector2D v1(1.0, 2.0), v2(3.0, 4.0);
  Vector2D v3 = v1.sumar(v2);
  
  assert(v3.getX() == 4.0);
  assert(v3.getY() == 6.0);
}


void test_distancia() {
  Vector2D v1(1.0, 2.0), v2(3.0, 4.0);

  assert(v1.distancia(v2) == sqrt(8.0));
}

void test_escalar() {
  Vector2D v1(1.0, 2.0);
  Vector2D v2 = v1.escalar(2.0);
  
  assert(v2.distancia(Vector2D(2.0, 4.0)) == 0.0);
}

void test_normalizar() {
  Vector2D v1(3.0, 4.0);
  v1.normalizar();
  assert(v1.modulo() == 1.0);
}

void test_toString() {
  Vector2D v1(1.0, 0.0);
  assert(v1.toString() == "(1.000000,0.000000)");
}


/* Conjunto de tests para Particula */

void test_constructor_getset_particula() {
  Particula p;
  assert(p.getTipo() == 0);
  assert(p.getRadio() >= 0.0);
  
  Particula p2(Vector2D(1, 2), Vector2D(0.1, 0.2), Vector2D(0.5, 0.6), 1.5, 2);
  assert(p2.getPosicion().getX() == 1);
  assert(p2.getPosicion().getY() == 2);
  assert(p2.getVelocidad().getX() == 0.1);
  assert(p2.getAceleracion().getY() == 0.6);
  assert(p2.getRadio() == 1.5);
  assert(p2.getTipo() == 2);
  
  p2.setPosicion(Vector2D(3, 3));
  p2.setAceleracion(Vector2D(2, 1));
  p2.setVelocidad(Vector2D(0.5, 2));
  p2.setRadio(3.0);
  assert(p2.getPosicion().getX() == 3);
  assert(p2.getPosicion().getY() == 3);
  assert(p2.getAceleracion().getY() == 1);
  assert(p2.getVelocidad().getX() == 0.5);
  assert(p2.getRadio() == 3.0);
}



void test_mover() {
  Vector2D pos(0, 0), acel(1, 2), vel(3, 4);
  Particula p(pos, vel, acel, 1.0, 0);
  p.mover();
  assert(p.getPosicion().getX() == 4.0);
  assert(p.getPosicion().getY() == 6.0);
  assert(p.getAceleracion().getX() == 1.0);
  assert(p.getAceleracion().getY() == 2.0);
  assert(p.getVelocidad().getX() == 4.0);
  assert(p.getVelocidad().getY() == 6.0);
  
  // Prueba para verificar el paso 2
  Vector2D pos2(4, 5), acel2(4, 4), vel2(5, 5);
  Particula p2(pos2, vel2, acel2, 1.0, 0);
  p2.mover();
  assert(p2.getPosicion().getX() == 11.0);
  assert(p2.getPosicion().getY() == 12.0);
  assert(p2.getAceleracion().getX() == 4.0);
  assert(p2.getAceleracion().getY() == 4.0);
  assert(p2.getVelocidad().getX() == 7.0);
  assert(p2.getVelocidad().getY() == 7.0);
  
  // Prueba para verificar el paso 4
  Vector2D pos3(1, 1), acel3(5, 5), vel3(-10, -10);
  Particula p3(pos3, vel3, acel3, 2.0, 0);
  p3.mover();
  assert(p3.getPosicion().getX() == 2.0);
  assert(p3.getPosicion().getY() == 2.0);
  assert(p3.getAceleracion().getX() == 5.0);
  assert(p3.getAceleracion().getY() == 5.0);
  assert(p3.getVelocidad().getX() == -5.0);
  assert(p3.getVelocidad().getY() == -5.0);
}


void test_rebotar() {
  // La partícula está al borde izquierdo, luego cambia de velocidad en x
  Vector2D acel(1, 0), vel(2, -3);
  Particula p(Vector2D(1, 2), vel, acel, 1.0, 0);
  p.rebotar();
  assert(p.getPosicion().distancia(Vector2D(1, 2)) == 0.0);
  assert(p.getAceleracion().distancia(Vector2D(1, 0)) == 0.0);
  assert(p.getVelocidad().distancia(Vector2D(-2, -3)) == 0.0);
  
  // La partícula no llega al borde izquierdo, luego no cambia
  Particula p2(Vector2D(1, 2), vel, acel, 0.5, 0);
  p2.rebotar();
  assert(p2.getPosicion().distancia(Vector2D(1, 2)) == 0.0);
  assert(p2.getAceleracion().distancia(Vector2D(1, 0)) == 0.0);
  assert(p2.getVelocidad().distancia(Vector2D(2, -3)) == 0.0);
}

void test_colision() {
  Particula p1(Vector2D(0, 0), {}, {}, 1.0, 0);
  Particula p2(Vector2D(1.5, 0), {}, {}, 1.0, 0);
  Particula p3(Vector2D(3.0, 0), {}, {}, 1.0, 0);
  assert(p1.colision(p2) == true);
  assert(p1.colision(p3) == false);
  assert(p2.colision(p3) == true);
}

void test_choque() {
  Vector2D v1(1.0, 0.0), v2(2.0, 0.0);
  Particula p1(Vector2D(0, 0), v1, v1, 1.0, 0);
  Particula p2(Vector2D(0, 1), v2, v2, 1.0, 0);
  p1.choque(p2);
  assert(p1.getVelocidad().distancia(v2) == 0.0);
  assert(p2.getVelocidad().distancia(v1) == 0.0);
  assert(p1.getAceleracion().distancia(v2) == 0.0);
  assert(p2.getAceleracion().distancia(v1) == 0.0);
}

void test_toString_particula() {
  Particula p(Vector2D(-1, 2), Vector2D(0, 1), Vector2D(1, 0), 1.0, 1);
  assert(p.toString() == "{(-1.000000,2.000000),(0.000000,1.000000),(1.000000,0.000000),1.000000,1}");
}
