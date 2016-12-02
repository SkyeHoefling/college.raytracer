#include "Light.h"


Light::Light(void)
{
	_position = Vector3();
	_color = RayColor();
}
Light::Light(Vector3 position, RayColor color) : Entity(position){
	_color = color;
}

Light::~Light(void)
{
}

// accessors
RayColor Light::getColor()		{	return _color;		}
