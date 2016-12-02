#pragma once
#include "Shape.h"
class Sphere : public Shape
{
protected:
	double _radius;
public:
	Sphere(void);
	_declspec(deprecated("(deprecated) ** This is designed for basic ray tracing/phong shading, which isn't good ray tracing **"))
		Sphere(Vector3 position, double radius, RayColor color);
	Sphere(Vector3 position, double radius, RayColor color, RayColor ambient, RayColor specular, 
		RayColor diffuse, int exponent, double reflection, double transparent);
	~Sphere(void);

	double getRadius();
};

