#include "letras.h"

Letra::Letra(char l, unsigned long r, int p) : letra(l),num_repeticiones(r),puntuacion(p)
{}

bool Letra::operator==(const Letra & l) const{
   return letra == l.letra;
}

bool Letra::operator <(const Letra & l) const{
    return letra < l.letra;
}