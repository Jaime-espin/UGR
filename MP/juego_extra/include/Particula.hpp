#ifndef PARTICULA_H
#define PARTICULA_H

#include <string>
#include "Vector2D.hpp"
#include "escudo.hpp"

class Escudo;

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
    Vector2D getPosicion() const;
    Vector2D getVelocidad() const;
    Vector2D getAceleracion() const;
    double getRadio() const;
    int getTipo() const;
    void mover();
    void rebotar();     //Para cuando choca con las paredes
    bool colision(Particula p);     //Si choca con particula
    void choque(Particula &p);      //Para cuando choca con particula
    std::string toString();
    //Parte1
    void wrap();
    //funciones auxiliares
    bool operator==(Particula &p);
    bool operator!=(Particula &p);
    //extra de mi juego
    void rebotarEscudo(Escudo e, bool &rebota);
};

//Parte2
ostream& operator<<(ostream &flujo, Particula &p);
istream& operator>>(istream &flujo, Particula &p);

#endif