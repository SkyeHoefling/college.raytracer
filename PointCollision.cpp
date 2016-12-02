#include "PointCollision.h"
PointCollision::PointCollision(void) {
	_position1 = Vector3();
	_position2 = Vector3();
	_surfaceNormalP1 = Vector3();
	_surfaceNormalP2 = Vector3();
}
PointCollision::PointCollision(Shape* theShape,Vector3 position1){
	_shape = theShape;
	_position1 = position1;
	_position2 = position1;
	_surfaceNormalP1 = Vector3();
}
PointCollision::PointCollision(Shape* theShape,Vector3 position1, Vector3 position2){
	_shape = theShape;
	_position1 = position1;
	_position2 = position2;
	_surfaceNormalP1 = Vector3();
	_surfaceNormalP2 = Vector3();
}
PointCollision::PointCollision(Vector3 position){}
PointCollision::~PointCollision(void){}

void PointCollision::setSurfaceNormalP1(Vector3 n) {
	_surfaceNormalP1 = n;
}
void PointCollision::setSurfaceNormalP2(Vector3 n) {
	_surfaceNormalP2 = n;
}

Vector3 PointCollision::getSurfaceNormalP1(){
	return _surfaceNormalP1;
}
Vector3 PointCollision::getSurfaceNormalP2(){
	return _surfaceNormalP2;
}
void PointCollision::calculateSurfaceNormals(Shape* object) {
	if(object->getBoundingRadius() == -1){
		// we are a plane
		_surfaceNormalP1 = Vector3(1,0,0);//((Plane *)object)->getSurfaceNormal();
		_surfaceNormalP2 = Vector3(1,0,0);
	}
	else{
		_surfaceNormalP1 = (_position1 - object->getPosition()).normalized();
		_surfaceNormalP2 = (_position2 - object->getPosition()).normalized();
	}
}

Shape* PointCollision::getShape(){
	return _shape;
}

void PointCollision::setColor( RayColor color )
{
	_color = color;
}
void PointCollision::setColor(){
	setColor(_shape->getColor());
}

RayColor PointCollision::getColor()
{
	return _color;
}

Vector3 PointCollision::getPosition1()	{ return _position1;	}
Vector3 PointCollision::getPosition2()	{ return _position2;	}