#include "PointCollision.h"
PointCollision::PointCollision(void) : Entity(Vector3()){
	_surfaceNormal = Vector3();
}
PointCollision::PointCollision(Shape* theShape,Vector3 position) : Entity(position) {
	_shape = theShape;
	_surfaceNormal = Vector3();
}
PointCollision::PointCollision(Vector3 position) : Entity(position) {}
PointCollision::~PointCollision(void){}

Vector3 PointCollision::getSurfaceNormal() {
	return _surfaceNormal;
}

void PointCollision::calculateSurfaceNormal(Shape* object) {
	if(object->getBoundingRadius() == -1)
		// we are a plane
		_surfaceNormal = Vector3(1,0,0);//((Plane *)object)->getSurfaceNormal();
	else
		_surfaceNormal = (_position - object->getPosition()).normalized();
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