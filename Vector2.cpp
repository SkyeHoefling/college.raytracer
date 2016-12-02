#include "Vector2.h"


Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

Vector2::Vector2(double xv, double yv){
	x = xv;
	y = yv;
}
void Vector2::setX(double xv) { x = xv; }
void Vector2::setY(double yv) { y = yv; }
double Vector2::getX()		 { return x; }
double Vector2::getY()		 { return y; }

double Vector2::dot( Vector2 v2 )
{
	double dot = x*v2.getX() + y*v2.getY();
	return dot;
}

Vector2::~Vector2(void)
{
}
