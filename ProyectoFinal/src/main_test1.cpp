#include <iostream>
#include <cassert>
#include <cmath>
#include "util.hpp" // El módulo util proporciona la función aleatorio
#include "params.hpp" // El archivo de cabecera params.hpp proporciona las constantes
#include "ConjuntoParticulas.hpp"
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
void test_wrap();


/* Conjunto de tests para ConjuntoParticulas */
void test_constructor_size();
void test_toString_conjunto();
void test_agregar();
void test_obtener_reemplazar();
void test_borrar();
void test_mover_particulas();
void test_gestionarColisiones();


int main() {
  
  cout << "\nEjecutando tests para Vector2D..." << endl;
  test_constructor_getset();
  test_suma();
  test_distancia();
  test_escalar();
  test_normalizar();
  test_toString();
  cout << "✅ Todos los tests de Vector2D han pasado bien." << endl;
  
  cout << "\nEjecutando tests para Particula Extendido..." << endl;
  test_constructor_getset_particula();
  test_mover();
  test_rebotar();
  test_colision();
  test_choque();
  test_toString_particula();
  test_wrap();
  cout << "✅ Todos los tests de Particula han pasado bien." << endl;

  cout << "\nEjecutando tests para Conjunto de Particulas..." << endl;
  test_constructor_size();
  test_toString_conjunto();
  test_agregar();
  test_obtener_reemplazar();
  test_borrar();
  test_mover_particulas();
  test_gestionarColisiones();
  cout << "✅ Todos los tests de ConjuntoParticulas han pasado bien." << endl;

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
  assert(p.getAceleracion().distancia(Vector2D(-1, 0)) == 0.0);
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

void test_wrap() {
  Particula p1(Vector2D(1, 2), Vector2D(3, 4), Vector2D(0, 1), 1.0, 0);
  p1.wrap();
  assert(p1.getPosicion().distancia(Vector2D(MAX_X -1, 2)) == 0.0);
  assert(p1.getVelocidad().distancia(Vector2D(3, 4)) == 0.0);
  assert(p1.getAceleracion().distancia(Vector2D(0, 1)) == 0.0);
  
  Particula p2(Vector2D(30, MAX_X -2), Vector2D(1, -2), Vector2D(1, 1), 2.0, 0);
  p2.wrap();
  assert(p2.getPosicion().distancia(Vector2D(30, 2)) == 0.0);
  assert(p2.getVelocidad().distancia(Vector2D(1, -2)) == 0.0);
  assert(p2.getAceleracion().distancia(Vector2D(1, 1)) == 0.0);
}


/* Conjunto de tests para ConjuntoParticulas */
void test_constructor_size() {
  ConjuntoParticulas conj1;
  assert(conj1.size() == 0);

  ConjuntoParticulas conj2(5);
  assert(conj2.size() == 5);
}

void test_toString_conjunto() {
  Particula p1(Vector2D(1, 2), Vector2D(3, 4), Vector2D(0, 1), 1.0, 0);
  ConjuntoParticulas c;
  c.agregar(p1);
  string output = c.toString();

  int capacidad = stoi(output.substr(0, output.find(',')));
  int num_particulas = stoi(output.substr(output.find(',') + 1, output.find('\n')));
  assert(capacidad == 3);
  assert(num_particulas == 1);  

  string particula = output.substr(output.find('\n') + 1);
  if (!particula.empty() && particula.back() == '\n') { //quito el salto de línea final si lo hay
    particula.pop_back();
  }
  assert(particula == p1.toString());
}

void test_agregar() {
  ConjuntoParticulas c;
  Particula p1(Vector2D(1, 2), Vector2D(3, 4), Vector2D(0, 1), 1.0, 0);
  Particula p2;
  c.agregar(p1);
  c.agregar(p2);
  assert(c.size() == 2); 
   
  c.agregar(Particula());
  c.agregar(Particula()); 

  assert(c.size() == 4);
  string output = c.toString();
  int capacidad = stoi(output.substr(0, output.find(',')));
  assert(capacidad == 6);
}

void test_obtener_reemplazar() {
  ConjuntoParticulas c;
  Particula p1(Vector2D(1, 2), Vector2D(3, 4), Vector2D(0, 1), 1.0, 0);
  Particula p2(Vector2D(5, 6), Vector2D(7, 8), Vector2D(0, -1), 2.0, 1);
  Particula p3(Vector2D(9, 10), Vector2D(11, 12), Vector2D(0, -1), 3.0, 2);

  c.agregar(p1);
  c.agregar(p2);
  c.reemplazar(0, p3);
  
  assert(c.obtener(0).toString() == p3.toString());
  assert(c.obtener(1).toString() == p2.toString());
}


void test_borrar() {
  ConjuntoParticulas c;
  Particula p1, p2, p3;
  c.agregar(p1);
  c.agregar(p2);
  c.agregar(p3);
  assert(c.size() == 3);
  
  c.borrar(0);
  assert(c.size() == 2);
  assert(c.obtener(0).toString() == p3.toString());
  assert(c.obtener(1).toString() == p2.toString());

  c.borrar(5);
  assert(c.size() == 2);
  assert(c.obtener(0).toString() == p3.toString());
  assert(c.obtener(1).toString() == p2.toString());
}

void test_mover_particulas() {
  ConjuntoParticulas c;
  Particula p1(Vector2D(1, 2), Vector2D(2, 3), Vector2D(0, 0), 1.0, 0);
  Particula p2(Vector2D(MAX_X -2, 5), Vector2D(-2, 2), Vector2D(0, 0), 1.0, 0);
  c.agregar(p1);
  c.agregar(p2);
  
  c.mover();
  assert(c.obtener(0).getPosicion().getX() == 3.0);
  assert(c.obtener(0).getPosicion().getY() == 5.0);

  c.mover(1);
  assert(c.obtener(1).getPosicion().getX() == MAX_X - 6.0);
  assert(c.obtener(1).getPosicion().getY() == 9.0);

  c.mover(2);
  assert(c.obtener(1).getPosicion().getX() == MAX_X - 8.0);
  assert(c.obtener(1).getPosicion().getY() == 11.0);
}

void test_gestionarColisiones() {
  ConjuntoParticulas c;
  Particula p1(Vector2D(15, 16), Vector2D(1, 1), Vector2D(0, 0), 1.0, 0);
  Particula p2(Vector2D(1, 2), Vector2D(3, 4), Vector2D(1, 2), 1.0, 0);
  Particula p3(Vector2D(1, 4), Vector2D(5, 6), Vector2D(0, 2), 1.0, 0);
  c.agregar(p1);
  c.agregar(p2);
  c.agregar(p3);
  
  c.gestionarColisiones();

  assert(c.obtener(0).toString() == p1.toString());

  assert(c.obtener(1).getVelocidad().getX() ==  5.0);
  assert(c.obtener(1).getVelocidad().getY() ==  6.0);
  assert(c.obtener(2).getVelocidad().getX() ==  3.0);
  assert(c.obtener(2).getVelocidad().getY() ==  4.0);

  assert(c.obtener(1).getAceleracion().getX() ==  0.0);
  assert(c.obtener(1).getAceleracion().getY() ==  2.0);
  assert(c.obtener(2).getAceleracion().getX() ==  1.0);
  assert(c.obtener(2).getAceleracion().getY() ==  2.0);
}
