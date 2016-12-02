#pragma once
#include "PointCollision.h"
#include "Sphere.h"
#include "Plane.h"
#include "World.h"
#include "Ray.h"
class CollisionTool
{
public:
	static bool getClosestIntersection(Shape* shapes, int numShapes, Ray* ray, PointCollision &closestCollision);
	static bool collidesWithShape(Shape* theShape, Ray* ray, PointCollision &collision);
	static bool collidesWithPlane(Shape* theShape, Ray* ray, PointCollision &collision);
	static bool collidesWithSphere(Shape* theShape, Ray* ray, PointCollision &collision);	
};

