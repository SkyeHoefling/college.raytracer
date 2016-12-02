#pragma once

#include "Vector3.h"

class Ray
{
private:
	//the origin of the ray ( aka the location of the RayCannon )
	Vector3 _origin;
	//the target point "on the viewscreen"
	Vector3 _target;

	double _eta;
	bool _inside;

// ---------------- this is all deprecated ---------------------- \\
//	Shape*  _collisionShapes;
//	int _numShapes;

	//theta is the angle made with the x-axis and the y axis
//	double _theta;
	//phi is the angle made with the x-axis and the z-axis
//	double _phi;

	//the color of the ray ( well at least the one it finds )
//	RayColor _color;
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))Light* _lightSources;
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))int _numberOfLights;
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))AmbientLight* _ambient;
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))Camera* _camera;	

public:
	Ray(Vector3 loc);
	Ray(Vector3 loc, bool inside);
	~Ray(void);
	void setTarget( Vector3 point );
	Vector3 getOrigin();
	Vector3 getTarget();
	Vector3 asVector3();
	double getEta();
	void setEta( double new_eta );
	bool getInside();
	// the origin is the origin of our shadow ray, not a previous ray

	// ---------------- this is all deprecated ---------------------- \\
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))void setWorldLightingReference( Light* lightSources, int numberOfLights, AmbientLight* ambient );
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))void setCameraReference(Camera* camera);
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))void checkThese( Shape * shapes, int totalShapes );
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))RayColor getColor();
private:
	// ---------------- this is all deprecated ---------------------- \\
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))void calculateAngles( void );
	//_declspec(deprecated("**This logic is no longer needed, and has been refactored into the collides with function**"))RayColor getAppropriateColor();	
	//_declspec(deprecated("**This has been outdated and no longer takes in parameters due to refactoring of getAppropriateColor**"))Vector3 collidesWith( Shape * theShape );
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))RayColor collidesWith();
	//_declspec(deprecated("**Collision detection has been moved to a static collision tool"))PointCollision collidesWithSphere(Shape* theShape);
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))Vector3 collidesWithPlain(Shape* theShape);
	//_declspec(deprecated("(deprecated) ** No longer needed Ray Calculations, and Collisions handled elsewhere **"))Vector3 collidesWithTriangle(Triangle * theShape);
};

