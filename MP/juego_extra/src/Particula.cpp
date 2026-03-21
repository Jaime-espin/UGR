#include <cmath>
#include <iostream>
#include "Particula.hpp"
#include "Vector2D.hpp"
#include "util.hpp"
#include "params.hpp"
#include "escudo.hpp"

using namespace std;

Particula::Particula(int tipoP){
    tipo=tipoP;
    if(tipoP!=0){
        radio=3.0;
        posicion.setXY(0.0, 0.0);
        velocidad.setXY(0.0, 0.0);
        aceleracion.setXY(0.0, 0.0);
    } else{
        radio=aleatorio(MIN_R, MAX_R);
        posicion.setXY(aleatorio(MIN_X, MAX_X), aleatorio(MIN_Y, MAX_Y));
        velocidad.setXY(aleatorio(-MAX_VEL, MAX_VEL), aleatorio(-MAX_VEL, MAX_VEL));
        aceleracion.setXY(aleatorio(-MAX_ACC, MAX_ACC), aleatorio(-MAX_ACC, MAX_ACC));
    }
}

Particula::Particula(Vector2D pos, Vector2D vel, Vector2D ace, double rad, int tipoP): posicion(pos), velocidad(vel), aceleracion(ace), radio(rad), tipo(tipoP){}

void Particula::setPosicion(Vector2D newPos){
    posicion=newPos;
}
void Particula::setVelocidad(Vector2D newVel){
    velocidad=newVel;
}
void Particula::setAceleracion(Vector2D newAce){
    aceleracion=newAce;
}
void Particula::setRadio(double newRadio){
    radio=newRadio;
}
Vector2D Particula::getPosicion()const{
    return posicion;
}
Vector2D Particula::getVelocidad()const{
    return velocidad;
}
Vector2D Particula::getAceleracion()const{
    return aceleracion;
}
double Particula::getRadio()const{
    return radio;
}
int Particula::getTipo()const{
    return tipo;
}

void Particula::mover(){
    setVelocidad(getVelocidad().sumar(getAceleracion()));

    Vector2D newVel = getVelocidad();
    if(newVel.getX() > MAX_VEL){
        newVel.setX(MAX_VEL);
    } else if(newVel.getX() < -MAX_VEL){
        newVel.setX(-MAX_VEL);
    }
    if(newVel.getY() > MAX_VEL){
        newVel.setY(MAX_VEL);
    } else if(newVel.getY() < -MAX_VEL){
        newVel.setY(-MAX_VEL);
    }
    setVelocidad(newVel);

    setPosicion(getPosicion().sumar(getVelocidad()));

    Vector2D newPos = getPosicion();
    if(newPos.getX() > MAX_X - radio){
        newPos.setX(MAX_X - radio);
    } else if(newPos.getX() < MIN_X + radio){
        newPos.setX(MIN_X + radio);
    }
    if(newPos.getY() > MAX_Y - radio){
        newPos.setY(MAX_Y - radio);
    } else if(newPos.getY() < MIN_Y + radio){
        newPos.setY(MIN_Y + radio);
    }
    
    setPosicion(newPos);
}
void Particula::rebotar(){
    Vector2D newVel;
    Vector2D newAce;
    
    if(getPosicion().getX() + getRadio() >= MAX_X || getPosicion().getX() - getRadio() <= MIN_X){
        newVel.setXY(getVelocidad().getX()*-1, getVelocidad().getY());
        setVelocidad(newVel);
        
        newAce.setXY(getAceleracion().getX()*-1, getAceleracion().getY());
        setAceleracion(newAce);
    }
    
    if(getPosicion().getY() + getRadio() >= MAX_Y || getPosicion().getY() - getRadio() <= MIN_Y){
        newVel.setXY(getVelocidad().getX(), getVelocidad().getY()*-1);
        setVelocidad(newVel);
        
        newAce.setXY(getAceleracion().getX(), getAceleracion().getY()*-1);
        setAceleracion(newAce);
    }
}
void Particula::rebotarEscudo(Escudo e, bool &rebota){
    Vector2D newVel;
    Vector2D newAce;
    rebota = false;
    Vector2D escudoPos = e.getPosicion();
    double escudoWidth = e.getAncho();
    double escudoLeft = escudoPos.getX() - escudoWidth/2;
    double escudoRight = escudoPos.getX() + escudoWidth/2;
    double escudoTop = escudoPos.getY();

    if(getPosicion().getX() + getRadio() >= escudoLeft && getPosicion().getX() - getRadio() <= escudoRight){
        if (fabs(getPosicion().getY() + getRadio() - escudoTop) < 5.0){
            newVel.setXY(getVelocidad().getX(), getVelocidad().getY()*-1);
            setVelocidad(newVel);
            
            newAce.setXY(getAceleracion().getX(), getAceleracion().getY()*-1);
            setAceleracion(newAce);

            rebota =true;
        }
    }
    
}

bool Particula::colision(Particula p){
    double diferx = p.getPosicion().getX() - getPosicion().getX();
    double difery = p.getPosicion().getY() - getPosicion().getY();
    double distancia = sqrt(diferx*diferx + difery*difery);
    double sumaRadios = p.getRadio() + getRadio();
    return(distancia<=sumaRadios); 
}
void Particula::choque(Particula &p){
    Vector2D Vaux;
    Vaux.setXY(p.getVelocidad().getX(), p.getVelocidad().getY());
    p.setVelocidad(getVelocidad());
    setVelocidad(Vaux);

    Vector2D Aaux;
    Aaux.setXY(p.getAceleracion().getX(), p.getAceleracion().getY());
    p.setAceleracion(getAceleracion());
    setAceleracion(Aaux);
}
string Particula::toString(){
    return "{("+to_string(getPosicion().getX())+","+to_string(getPosicion().getY())+"),("+to_string(getVelocidad().getX())+","+to_string(getVelocidad().getY())+"),("+to_string(getAceleracion().getX())+","+to_string(getAceleracion().getY())+")"+","+to_string(radio)+","+to_string(tipo)+"}";
}

//Parte1

void Particula::wrap(){
    Vector2D pos = getPosicion();
    
    if (pos.getX() + radio >= MAX_X) {
        pos.setX(MIN_X + radio);
    } else if (pos.getX() - radio <= MIN_X) {
        pos.setX(MAX_X - radio);
    }

    if (pos.getY() + radio >= MAX_Y) {
        pos.setY(MIN_Y + radio);
    } else if ((pos.getY() - radio) <= MIN_Y) {
        pos.setY(MAX_Y - radio);
    }
    
    setPosicion(pos);
}

//auxiliares
bool Particula::operator==(Particula &p){
    bool igual=false;
    if(getPosicion()==p.getPosicion()){
        igual=true;
    }
    return igual;
}

bool Particula::operator!=(Particula &p){
    return !(*this==p);
}

//Parte2

ostream& operator<<(ostream &flujo, Particula &p){
    flujo<<p.toString();
    return flujo;
}
istream& operator>>(istream &flujo, Particula &p){
    string nombre;
    double pos_x, pos_y, vel_x, vel_y, ace_x, ace_y, radio;
    int tipo;

    flujo>>nombre>>pos_x>>pos_y>>vel_x>>vel_y>>ace_x>>ace_y>>radio>>tipo;
    
    p=Particula({pos_x, pos_y}, {vel_x, vel_y}, {ace_x, ace_y}, radio, tipo);
    return flujo;
}