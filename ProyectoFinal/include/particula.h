#ifndef PARTICULA_H
#define PARTICULA_H

#include <string>
#include "vector.h"

class Particula{
private:
    Vector2D posicion;
    Vector2D velocidad;
    Vector2D aceleracion;
    double radio;
    int tipo;
public:
    Particula(int tipoP=0);
    Particula(Vector2D pos, Vector2D vel, Vector2D ace, double rad, int tipoP);
    void setPosicion(Vector2D newPos);
    void setVelocidad(Vector2D newVel);
    void setAceleracion(Vector2D newAce);
    void setRadio(double newRadio);
    Vector2D getPosicion();
    Vector2D getVelocidad();
    Vector2D getAceleracion();
    double getRadio();
    int getTipo();
    void mover();
    void rebotar();
    bool colision(Particula p);
    void choque(Particula &p);
    std::string toString();
    //Parte1
    void wrap();
};

#endif