#ifndef CONJUNTOPARTICULAS_H
#define CONJUNTOPARTICULAS_H

#include "particula.h"
using namespace std;

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
    void agregar(Particula p);
    void borrar(int pos);
    Particula obtener(int pos);
    void reemplazar(int pos, Particula p);
    void mover(int tipo_mov=0);
    void gestionarColisiones();
    std::string toString();

    //Parte2
    Particula operator[](const int indice);
    ConjuntoParticulas & operator=(const ConjuntoParticulas & c);
    ConjuntoParticulas & operator+=(Particula & p);
    ConjuntoParticulas & operator-=(const int & indice);

    //funciones auxiliares
    bool pertenece(Particula & p);
    int getNumeroParticulas();
};

ostream& operator<<(ostream &flujo, ConjuntoParticulas &c);
istream& operator>>(istream &flujo, ConjuntoParticulas &c);

#endif