#ifndef TIEMPO_H
#define TIEMPO_H

#include <string>
using namespace std;

struct Tiempo{
	int hh, mm, ss;
};

const int SEG_MIN = 60;
const int SEG_HORA = 3600;
const int SEG_DIA = 86400;

int TiempoEnSegundos(const Tiempo &);
Tiempo segundosEnTiempo(const int);
bool esPosterior(const Tiempo &,const Tiempo &);
bool sonIguales(const Tiempo &, const Tiempo &);
Tiempo calcularNuevoTiempo(const Tiempo &, const int );
string toString(const Tiempo &);

#endif TIEMPO_H
