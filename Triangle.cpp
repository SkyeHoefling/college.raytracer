#include "Triangle.h"


Triangle::Triangle(void)
{
}

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3, RayColor color)
	: Shape(Vector3((p1.getX() + p2.getX() + p3.getX())/3,
					(p1.getY() + p2.getY() + p3.getY())/3,
					(p1.getZ() + p2.getZ() + p3.getZ()/3)), -2, color)
{
	_point1 = p1;
	_point2 = p2;
	_point3 = p3;
	calculateSurfaceNormal();
}

Triangle::~Triangle(void)
{
}

Vector3 Triangle::getNormal()	{	return _normal;		}
Vector3 Triangle::getPoint1()	{	return _point1;		}
Vector3 Triangle::getPoint2()	{	return _point2;		}
Vector3 Triangle::getPoint3()	{	return _point3;		}

void Triangle::calculateSurfaceNormal(){
	_normal = Vector3();
	Vector3 u = _point2 - _point1;
	Vector3 v = _point3 - _point1;
	_normal.setX( (u.getY() * v.getZ()) - (u.getZ() - v.getY()) );
	_normal.setY( (u.getZ() * v.getX()) - (u.getX() - v.getZ()) );
	_normal.setZ( (u.getX() * v.getY()) - (u.getY() - v.getX()) );
}
