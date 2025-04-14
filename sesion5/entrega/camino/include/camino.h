#ifndef CAMINO_H
#define CAMINO_H

#include <string>

struct Punto2D{
	int x, y;
};
struct Camino{
	Punto2D *path=0;
	int util=0;
};

void agregarPunto(Camino & c, const Punto2D &p);
void borrarPunto(Camino & c, Punto2D p);
double distanciaPuntos(Punto2D p1, Punto2D p2);
double distancia(Punto2D p1, Punto2D p2);
void masLejanos(Camino & c, Punto2D & p1, Punto2D & p2);
double longitud(Camino & c);
void unirCaminos(Camino &c, Camino c1, Camino c2);
void mostrarCamino(Camino c);
std::string toString(Punto2D p);
void liberaMemoria(Camino &c);

#endif
