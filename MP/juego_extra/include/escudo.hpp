#ifndef ESCUDO_HPP
#define ESCUDO_HPP

#include "Particula.hpp"
#include "Vector2D.hpp"
#include "util.hpp"
#include "params.hpp"

class Escudo{
    private:
        Vector2D posicion;
        double ancho;
    public:
        Escudo(Vector2D pos={MAX_X/2,MAX_Y-MAX_Y/4}, double anc=50);
        Vector2D getPosicion() const;
        double getAncho() const;
        void mover(float deltaX);
    };

#endif