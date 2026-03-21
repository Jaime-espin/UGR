#include "tiempo.h"

int TiempoEnSegundos(const Tiempo &t){
	return t.hh*SEG_HORA+t.mm*SEG_MIN+t.ss;
}

Tiempo segundosEnTiempo(const int segs){
	Tiempo t;
	t.hh = segs / 3600;
	t.mm = (segs % 3600) / 60;
	t.ss = segs % 60;
	return t;
}

bool esPosterior(const Tiempo &t1, const Tiempo &t2){
	return TiempoEnSegundos(t1)>TiempoEnSegundos(t2);
}

bool sonIguales(const Tiempo &t1, const Tiempo &t2){
	return TiempoEnSegundos(t1)==TiempoEnSegundos(t2);
}

Tiempo calcularNuevoTiempo(const Tiempo &t, const int segs){
	int ts=TiempoEnSegundos(t)+segs;
	return segundosEnTiempo(ts);
}

string toStringT(const Tiempo &t){
	string resultado;
	resultado = to_string(t.hh) + ":" + to_string(t.mm) + ":" + to_string(t.ss);
	return resultado;
}
