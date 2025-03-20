#ifndef TIEMPO_H
#define TIEMPO_H

using namespace std;

#include <string>
#include "tiempo.h"


const float LONG_TRAMO = 17.45;
const int VELOC_LIMITE = 90;

struct Registro{
	Tiempo tsalida, tentrada;
	string matricula;
}

const int MAX = 100;
struct ControlDiario {
Registro conjunto [MAX] ;
int util;
};

int tiempoEnTramo(const Registro &);
double velocidadPromedio(const Registro &);
void corrigeRegistro(const Registro &);
string controlVehiculo(const Registro &);
string toString (const Registro &);
ControlDiario extraerDatos(ControlDiario &);


#endif TIEMPO_H
