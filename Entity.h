#pragma once
#include "Vector3.h"
class Entity
{
protected:
	Vector3 _position;
public:
	Entity(void);
	Entity(Vector3 position);
	~Entity(void);

	// Accessor
	Vector3 getPosition();
};

