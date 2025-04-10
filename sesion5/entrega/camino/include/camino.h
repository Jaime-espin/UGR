#ifndef CAMINO_H
#define CAMINO_H

struct Punto2D{
	int x, y;
};
struct Camino{
	Punto2D *path=0;
	int util=0;
};

void agregarPunto(Camino & c, const Punto2D &p);
void borrarPunto(Camino & c, Punto2D p);
void masLejanos(Camino & c, Punto2D & p1, Punto2D & p2);
double longitud(Camino & c);
void unirCaminos(Camino c1, Camino c2, Camino &c);
void mostrarCamino(Camino c);

#endif
