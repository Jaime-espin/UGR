#include "registro.h"

int tiempoEnTramo(const Registro &r){
	return (TiempoEnSegundos(r.tsalida)-TiempoEnSegundos(r.tentrada))/60;
}

double velocidadPromedio(const Registro &r){
	return LONG_TRAMO/(tiempoEnTramo(r)/60.0);
}

void corrigeRegistro(Registro &r){
	if(esPosterior(r.tentrada, r.tsalida)){
		Tiempo aux = r.tentrada;
		r.tentrada = r.tsalida;
		r.tsalida = aux;
	}
}

string controlVehiculo(const Registro &r){
	string respuesta;
	respuesta="Vehículo matrícula"+ r.matricula+", velocidad promedio"+to_string(velocidadPromedio(r))+"km/h";
	if(velocidadPromedio(r)>VELOC_LIMITE){
		respuesta+="MULTA";
	}
	return respuesta;
}

string toStringR(const Registro &r){
	string resultado;
	resultado="Entra: "+toStringT(r.tentrada)+" Sale: "+toStringT(r.tsalida);
	return resultado;
}

void extraerDatos(const ControlDiario &d, ControlDiario &multa, ControlDiario &nomulta){
	int f = 0, j = 0;
	multa.util = 0;
	nomulta.util = 0;
	
	for(int i=0; i<d.util; i++){
		if(velocidadPromedio(d.conjunto[i])>VELOC_LIMITE){
			multa.conjunto[j]=d.conjunto[i];
			j++;
			multa.util++;
		}else{
			nomulta.conjunto[f]=d.conjunto[i];
			f++;
			nomulta.util++;
		}
	}
}
