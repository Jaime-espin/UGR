#ifndef VECTOR_H
#define VECTOR_H

#include <string>

using namespace std;
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
	//Parte2
	Vector2D operator+(const Vector2D &v);
	Vector2D operator*(const double &n);
	bool operator==(const Vector2D &v);
	bool operator!=(const Vector2D &v);
	
};
ostream& operator<<(ostream &flujo, Vector2D &v);
std::istream& operator>>(std::istream &flujo, Vector2D &v);

#endif
