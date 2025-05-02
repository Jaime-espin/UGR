#ifndef VECTOR_H
#define VECTOR_H

#include <string>

class Vector2D{
private:
	double x, y;
public:
	Vector2D(const double _x=0, const double _y=0){
		x=_x;
		y=_y;
	}
	double getX() const;
	double getY() const;
	void setX(double nuevaX);
	void setY(double nuevaY);
	void setXY(double nuevaX, double nuevaY);
	Vector2D sumar(Vector2D v);
	Vector2D escalar(double n);
	double modulo();
	void normalizar();
	double distancia(Vector2D v);
	std::string toString();
};

#endif
