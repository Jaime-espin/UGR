#include "tiempo.h"

int TiempoEnSegundos(const Tiempo t){
	return t.hh*SEG_HORA+t.mm*SEG_MIN+t.ss;
}

Tiempo segundosEnTiempo(const int segs){
	Tiempo t;
	t.hh  = segundos / 3600;
	t.mm = (segundos % 3600) / 60;
	t.hh = segundos % 60;
}

bool esPosterior(const Tiempo t1,const Tiempo t2){
	return TiempoEnSegundos(t1)>TiempoEnSegundos(t2);
}

bool sonIguales(const Tiempo t1, const Tiempo t2){
	return TiempoEnSegundos(t1)=TiempoEnSegundos(t2);
}

Tiempo calcularNuevoTiempo(const Tiempo t, const int segs){
	int ts=TiempoEnSegundos(t)+segs;
	return segundosEnTiempo(ts);
}

string toString(const Tiempo t){
	//to_string
}
