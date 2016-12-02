#include "Vector4.h"

Vector4::Vector4(void)
{
}

Vector4::Vector4(double xp, double yp, double zp, double wp){
        _w = wp;
        _x = xp;
        _y = yp;
        _z = zp;
}

Vector4::Vector4(Vector3 vec){	
	_x = vec.getX();
	_y = vec.getY();
	_z = vec.getZ();
	_w = 1;
}

Vector4::Vector4(Vector3 vec, double wp){	
	_x = vec.getX();
	_y = vec.getY();
	_z = vec.getZ();
	_w = wp;
}

Vector4::~Vector4(void)
{
}


double Vector4::getX(){ return _x; }
double Vector4::getY(){ return _y; }
double Vector4::getZ(){ return _z; }
double Vector4::getW(){ return _w; }
void Vector4::setX(double i){ _x = i; }
void Vector4::setY(double i){ _y = i; }
void Vector4::setZ(double i){ _z = i; }
void Vector4::setW(double i){ _w = i; }
double Vector4::dot(Vector4 rhs){
	return _x*rhs.getX() +
		   _y*rhs.getY() + 
		   _x*rhs.getZ() +
		   _w*rhs.getW();
}
Vector4 Vector4::operator +(Vector4 rhs){
        return Vector4(_x+rhs.getX(), _y+rhs.getY(), _z+rhs.getZ(),_w+rhs.getW());
}
Vector4 Vector4::operator -(Vector4 rhs){
        return Vector4(_x-rhs.getX(), _y-rhs.getY(), _z-rhs.getZ(),_w-rhs.getW());
}
bool Vector4::operator ==(Vector4 rhs){
        if(_x==rhs.getW() && _x==rhs.getX() && _y==rhs.getY() && _z==rhs.getZ())
                return true;
        return false;
}
Vector4 Vector4::getNormalized(){
	double magnitude = sqrt(_x*_x + _y*_y + _z*_z + _w*_w);
	return Vector4(_x/magnitude,
				   _y/magnitude,
				   _z/magnitude,
				   _w/magnitude);
}

void Vector4::normalize(){
	double magnitude = sqrt(_x*_x + _y*_y + _z*_z + _w*_w);
	_x/=magnitude;
	_y/=magnitude;
	_z/=magnitude;
	_w/=magnitude;
}
Vector4 Vector4::operator*(double num){
	return Vector4(_x*num,
				   _y*num,
				   _z*num,
				   _w*num);
}
Vector4 Vector4::operator*(Vector4 rhs){
	return Vector4(_x*rhs.getX(),
				   _y*rhs.getY(),
				   _z*rhs.getZ(),
				   _w*rhs.getW());
}

Vector4 Vector4::operator=(Vector3 rhs){
	return Vector4(rhs);
}
