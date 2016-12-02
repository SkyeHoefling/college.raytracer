#pragma once
#include "RayColor.h"
#include "Entity.h"
class Light : public Entity
{
protected:
	RayColor _color;
public:
	Light(void);
	Light(Vector3 position, RayColor color);
	~Light(void);

	RayColor getColor();
};

