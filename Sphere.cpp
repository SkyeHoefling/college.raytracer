#include "Sphere.h"


Sphere::Sphere(void) : Shape(Vector3(), 0, RayColor(0,0,0))
{
	_radius = 0;
	_type = SHAPE_SPHERE;
}

Sphere::Sphere(Vector3 position, double radius, RayColor color) : Shape(position, radius, color){
	_radius = radius;
	_type = SHAPE_SPHERE;
}

Sphere::Sphere(Vector3 position, double radius, RayColor color, RayColor ambient, RayColor specular,
	RayColor diffuse, int exponent, double reflection, double transparent) : 
	Shape(position, radius, color, ambient, specular, diffuse, exponent, reflection, transparent){
		_radius = radius;
		_type = SHAPE_SPHERE;
}

Sphere::~Sphere(void)
{
}

double Sphere::getRadius()	{	return _radius;		}