#pragma once
#include "Sphere.h"
#include "Plane.h"
#include "Vector3.h"
class PointCollision
{
private:
	Vector3 _surfaceNormalP1;
	Vector3 _surfaceNormalP2;
	Vector3 _position1;
	Vector3 _position2;
	Shape * _shape;
	RayColor _color;
public:
	PointCollision(void);
	PointCollision(Shape* theShape, Vector3 position1);
	PointCollision(Shape* theShape, Vector3 position1, Vector3 position2);
	PointCollision(Vector3 position);
	~PointCollision(void);
	Vector3 getSurfaceNormalP1();
	Vector3 getSurfaceNormalP2();
	void calculateSurfaceNormals(Shape* object);
	void setSurfaceNormalP1(Vector3 normal);
	void setSurfaceNormalP2(Vector3 normal);
	Vector3 getPosition1();
	Vector3 getPosition2();
	Shape * getShape();

	void setColor( RayColor color );
	void setColor();
	RayColor getColor( );

};

