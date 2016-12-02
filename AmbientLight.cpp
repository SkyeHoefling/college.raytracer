#include "AmbientLight.h"


AmbientLight::AmbientLight(void) :Light(Vector3(), RayColor())
{
	_radius = 0;
}

AmbientLight::AmbientLight(Vector3 position, RayColor color, float radius): Light(position, color)
{
	_radius = radius;
}
AmbientLight::~AmbientLight(void)
{
}
float AmbientLight::getRadius()	{	return _radius;	}