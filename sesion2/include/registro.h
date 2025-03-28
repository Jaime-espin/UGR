#ifndef REGISTRO_H
#define REGISTRO_H

using namespace std;

#include <string>
#include "tiempo.h"


const float LONG_TRAMO = 17.45;
const int VELOC_LIMITE = 90;

struct Registro{
	Tiempo tsalida, tentrada;
	string matricula;
};

const int MAX = 100;
struct ControlDiario {
	Registro conjunto[MAX];
	int util;
};

int tiempoEnTramo(const Registro &);
double velocidadPromedio(const Registro &);
void corrigeRegistro(Registro &);
string controlVehiculo(const Registro &);
string toStringR (const Registro &);
void extraerDatos(const ControlDiario &, ControlDiario &, ControlDiario &);


#endif
