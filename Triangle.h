#pragma once
#include "Shape.h"
class Triangle : public Shape
{
private:
	Vector3 _point1;
	Vector3 _point2;
	Vector3 _point3;
	Vector3 _normal;
public:
	Triangle(void);
	Triangle(Vector3 p1, Vector3 p2, Vector3 p3, RayColor color);
	~Triangle(void);

	Vector3 getPoint1();
	Vector3 getPoint2();
	Vector3 getPoint3();
	Vector3 getNormal();
	void calculateSurfaceNormal();
};

