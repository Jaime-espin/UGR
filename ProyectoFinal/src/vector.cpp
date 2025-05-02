#include "vector.h"
#include <cmath>

using namespace std;

double Vector2D::getX() const{
  return x;
}

double Vector2D::getY() const{
  return y;
}

void Vector2D::setX(double nuevaX){
  x=nuevaX;
}

void Vector2D::setY(double nuevaY){
  y=nuevaY;
}

void Vector2D::setXY(double nuevaX, double nuevaY){
  setX(nuevaX);
  setY(nuevaY);
}

Vector2D Vector2D::sumar(Vector2D v){
  Vector2D suma;
  suma.setX(getX()+v.x);
  suma.setY(getY()+v.y);
  return suma;
}

Vector2D Vector2D::escalar(double n){
  Vector2D nuevov;
  nuevov.setX(getX()*n);
  nuevov.setY(getY()*n);
  return nuevov;
}

double Vector2D::modulo(){
  return sqrt(pow(getX(),2)+pow(getY(),2));
}

void Vector2D::normalizar(){
  double mod=modulo();
  setX(getX()/mod);
  setY(getY()/mod);
}

double Vector2D::distancia(Vector2D v){
  return sqrt((getX()-v.x)*(getX()-v.x) + (getY()-v.y)*(getY()-v.y));
}

string Vector2D::toString(){
  return "(" + to_string(getX()) + "," + to_string(getY()) + ")";
}
