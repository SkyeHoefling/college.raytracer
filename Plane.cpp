#include "Plane.h"


Plane::Plane(void)
{
}

Plane::Plane(Vector3 position, Vector3 normal, double width, double height, RayColor color) :
	Shape(position, -1, color)
{
	_width = width;
	_height = height;
	_normal = normal;
	_type = SHAPE_PLANE;
}


Plane::~Plane(void)
{
}

Vector3 Plane::getSurfaceNormal(){ return _normal; }

