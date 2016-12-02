#pragma once
#include "PointCollision.h"
#include "Sphere.h"
#include "Plane.h"
class CollisionTool
{
public:
	static bool collidesWithShape(Shape* theShape, Vector3 endPoint, Vector3 origin, PointCollision &collision);
	static bool collidesWithPlane(Shape* theShape, Vector3 endPoint, Vector3 origin, PointCollision &collision);
	static bool collidesWithSphere(Shape* theShape, Vector3 endPoint, Vector3 origin, PointCollision &collision);	
};

