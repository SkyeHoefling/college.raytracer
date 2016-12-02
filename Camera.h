#pragma once
#include "Entity.h"
class Camera : public Entity
{
protected:
	Vector3 _orientation;
	Vector3 _up;
public:
		Camera(void);
        Camera(Vector3 position, Vector3 orientation, Vector3 upVector);
        ~Camera(); 

		// accessors
		Vector3 getOrientation();
		Vector3 getUp();
};

