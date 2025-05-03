#ifndef CONJUNTOPARTICULAS_H
#define CONJUNTOPARTICULAS_H

#include "particula.h"

const int TAM_BLOQUE=3;

class ConjuntoParticulas {
private:
    Particula *conjunto; //un array de particulas
    int capacidad; //capacidad del array
    int num_particulas; //posiciones ocupadas
public:
    ConjuntoParticulas(int n=0);
    ConjuntoParticulas(const ConjuntoParticulas &cp);
    ~ConjuntoParticulas();
    int size();
    void agergar(Particula p);
    void borrar(int pos);
    Particula obtener(int pos);
    void reemplazar(int pos, Particula p);
    void mover(int tipo_mov=0);
    void gestionarColisiones();
    std::string toString();
};

#endif