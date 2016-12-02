#pragma once
#include "Sphere.h"
#include "Plane.h"
class PointCollision : public Entity
{
private:
	Vector3 _surfaceNormal;
	Shape * _shape;
public:
	PointCollision(void);
	PointCollision(Shape* theShape, Vector3 position);
	PointCollision(Vector3 position);
	~PointCollision(void);
	Vector3 getSurfaceNormal();
	void calculateSurfaceNormal(Shape* object);
	void setSurfaceNormal(Vector3 normal);
	Shape * getShape();
};

