#include "Vector3.h"

Vector3::Vector3(void)
{
        x = y = z = 0.0f;
}

Vector3::~Vector3(void)
{
}

Vector3::Vector3(double xp, double yp, double zp){
        x = xp;
        y = yp;
        z = zp;
}

void Vector3::setX(double i){ x = i; }
void Vector3::setY(double i){ y = i; }
void Vector3::setZ(double i){ z = i; }
void Vector3::addX(double i){ x += i; }
void Vector3::addY(double i){ y += i; }
void Vector3::addZ(double i){ z += i; }
double Vector3::getX(){ return x; }
double Vector3::getY(){ return y; }
double Vector3::getZ(){ return z; }
Vector3 Vector3::getVector(){ return *this; }
Vector3 Vector3::operator +(Vector3 rhs){
        return Vector3(x+rhs.getX(), y+rhs.getY(), z+rhs.getZ());
}
Vector3 Vector3::operator -(Vector3 rhs){
        return Vector3(x-rhs.getX(), y-rhs.getY(), z-rhs.getZ());
}
Vector3 Vector3::operator *(double rhs){
        return Vector3(x*rhs, y*rhs, z*rhs);
}
Vector3 Vector3::operator *(int rhs){
        return Vector3(x*rhs, y*rhs, z*rhs);
}
Vector3 Vector3::operator *(Vector3 rhs){
        return Vector3(x*rhs.getX(), y*rhs.getY(), z*rhs.getZ());
}
Vector3 Vector3::operator /(double rhs){
        return Vector3(x/rhs, y/rhs, z/rhs);
}
Vector3 Vector3::operator /(int rhs){
        return Vector3(x/rhs, y/rhs, z/rhs);
}
bool Vector3::operator ==(Vector3 rhs){
        if(x==rhs.getX() && y==rhs.getY() && z==rhs.getZ())
                return true;
        return false;
}
bool Vector3::operator!=(Vector3 rhs){
	if(x != rhs.getX() || y != rhs.getY() || z != rhs.getZ())
		return true;
	return false;
}
void Vector3::normalize(){
        double l = length();
		x = x/l;
		y = y/l;
		z = z/l;
}
Vector3 Vector3::normalized(){
	double l = length();
	return Vector3(x/l, y/l, z/l);
}

Vector3 Vector3::unitFrom(Vector3 v){
        Vector3 vec(x-v.getX(), y-v.getY(), z-v.getZ());
        return vec.normalized();
}
double Vector3::dot(Vector3 i){ return x*i.getX() + y*i.getY() + z*i.getZ(); }

Vector3 Vector3::cross(Vector3 i)
{
        Vector3 normal;
        normal.setX(y * i.getZ() - z * i.getY());
        normal.setY(z * i.getX() - x * i.getZ());
        normal.setZ(x * i.getY() - y * i.getX());

        return normal;
}

double Vector3::length(){
        return sqrt(x*x + y*y + z*z);
}
double Vector3::distanceFrom(Vector3 v){
	return sqrt( pow( v.getX() - x , 2 ) + pow( v.getY() - y, 2 ) + pow( v.getZ() - z , 2 ) );
}
