#include "Entity.h"


Entity::Entity(void){
	_position = Vector3();
}
Entity::Entity(Vector3 position)
{
	_position = position;
}
Entity::~Entity(void)
{
}

// accessors
Vector3 Entity::getPosition()		{	return _position;	}