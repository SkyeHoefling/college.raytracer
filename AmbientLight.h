#pragma once
#include "Light.h"
#include "RayColor.h"
class AmbientLight : public Light
{
private:
	float _radius;
public:
	AmbientLight(void);
	AmbientLight(Vector3 position, RayColor color, float radius);
	~AmbientLight(void);
	float getRadius();
};

