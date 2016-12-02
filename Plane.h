#pragma once
#include "Shape.h"
class Plane : public Shape
{
private:
	double _width;
	double _height;
	Vector3 _normal;
public:
	Plane(void);
	Plane(Vector3 position, Vector3 normal, double width, double height, RayColor color);
	~Plane(void);

	double getWidth();
	double getHeight();
	Vector3 getSurfaceNormal();
};

