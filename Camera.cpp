#include "Camera.h"
Camera::Camera(void){
	_position = Vector3();
	_orientation = Vector3();
	_up = Vector3();
}
Camera::Camera(Vector3 pos, Vector3 fwd, Vector3 upVector) : Entity(pos){
	_orientation = fwd;
	_up = upVector;
}
Camera::~Camera(){
}

// accessors
Vector3 Camera::getOrientation()	{	return _orientation;	}
Vector3 Camera::getUp()				{	return _up;				}