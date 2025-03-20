#include "registro.h"

int tiempoEnTramo(Registro r){
	return (TiempoEnSegundos(r.tsalida)-TiempoEnSegundos(r.tentrada))/60;
}
double velocidadPromedio(Registro r){
	return LONG_TRAMO/(tiempoEnTramo(r)/60);
}
void corrigeRegistro(Registro r){
	if(r.tentrada>r.tsalida){
		int aux=r.tentrada;
		r.tentrada=r.tsalida;
		r.tsalida=aux;
	}
}
string controlVehiculo(Registro r){

}
string toString  Registro r){

}

ControlDiario extraerDatos(ControlDiario d){
	
}
