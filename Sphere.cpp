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

Sphere::Sphere(Vector3 position, double radius, RayColor color,
	double reflection, double transparent) : Shape(position, radius, color, reflection, transparent){
		_radius = radius;
		_type = SHAPE_SPHERE;
}

Sphere::~Sphere(void)
{
}

double Sphere::getRadius()	{	return _radius;		}