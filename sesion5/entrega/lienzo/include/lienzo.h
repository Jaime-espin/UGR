/*
NOMBRE Y APELLIDOS: Jaime Espín Rodríguez
DNI: 75571535K
GRUPO DE PR´ACTICAS: Jueves
*/
#ifndef LIENZO_H
#define LIENZO_H

struct Lienzo {
	char ** m = 0;
	int nf = 0, nc = 0;
};

void reservarLienzo(Lienzo & l, int nf, int nc);
void liberarLienzo(Lienzo & l);
void rellenarLienzo(Lienzo & l, char c);
void imprimirLienzo(Lienzo l);
void dibujarRectangulo(Lienzo & l, int fil, int col, int ancho, int alto, char c);
void rotarLienzo(Lienzo & l);
void unirLienzos(Lienzo & l, Lienzo l1, Lienzo l2);
void copiarRectangulo(Lienzo & l1, Lienzo l, int fil, int col, int alto, int ancho);
bool sonIguales(Lienzo l1, Lienzo l2);
void copiarLienzo(Lienzo & lcopia, Lienzo l);

#endif LIENZO_H