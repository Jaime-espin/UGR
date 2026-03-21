#include "Punto2D.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>



using namespace std;

// constructor sin parametros.

Punto2D::Punto2D() {
    x = rand() % MIN_DIM;
    y = rand() % MIN_DIM;
}

// distancia entre dos puntos
float Punto2D::distancia(const Punto2D & otro) const {
    float xx = otro.x - this->x;
    float yy = otro.y - this->y;

    return (sqrt(xx * xx + yy * yy));
}

bool Punto2D::colision(const Punto2D & otro) const {
    float d = this->distancia(otro);
    return (d <= UMBRAL);
}

float Punto2D::getX() const {
    return (x);
}

float Punto2D::getY() const {
    return (y);
}


void Punto2D::setXY(float _x, float _y){
    x = _x;
    y = _y;
}


void Punto2D::mover(float dx, float dy) {
    x += dx;
    y += dy;
}

// rota el punto alrededor de otro punto (posX, posY) cierta cantidad de rads (radianes)
void Punto2D::rotar(const Punto2D & pivot, float rads) {
    float deltaX = x - pivot.getX();
    float deltaY = y - pivot.getY();

    x = pivot.getX() + deltaX * cos(rads) - deltaY * sin(rads);
    y = pivot.getY() + deltaX * sin(rads) + deltaY * cos(rads);

}  

std::string Punto2D::toString() const{
    string s = "";
    s = "(x: " + to_string(x) + ", y: " + to_string(y) + ")";
    
    return s;
}

// mueve el punto en dirección a otro. 
// se utiliza un factor que simula la velocidad
void Punto2D::moverHacia(const Punto2D & destino, float speed){
//calculo del desplazamiento
float dx= getX()- destino.getX();
float dy= getY()- destino.getY();
float modulo = sqrt(dx*dx+dy*dy);
//recuerdas vectores unitarios?
dx=-dx/modulo;
dy=-dy/modulo;

x += speed*dx;
y += speed*dy;
}