#include "escudo.hpp"
        
Escudo::Escudo(Vector2D pos, double anc):posicion(pos), ancho(anc){}
Vector2D Escudo::getPosicion() const { return posicion; }
double Escudo::getAncho() const { return ancho; }
void Escudo::mover(float deltaX) {
    posicion.setX(posicion.getX() + deltaX);
      
    if (posicion.getX() - ancho/2 < 0)
        posicion.setX(ancho/2);
    if (posicion.getX() + ancho/2 > MAX_X)
        posicion.setX(MAX_X - ancho/2);
}