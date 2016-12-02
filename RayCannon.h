#pragma once
#include "Shape.h"
#include "RayColor.h"
#include "Light.h"
#include "AmbientLight.h"
#include "Camera.h"
#include "World.h"
#include "ShaderTool.h"
#include <vector>

class RayCannon : public Entity
{
private:

	/* the world cordinates that describes the location of the cannon, which
	 * is effectively the camera as well.
	 */
	//Vector3 _location;

	// The normal vector, shouldn't change from ( 0,1,0)
	Vector3 _normal;

	///The shapes from the world, we will need the reference for the rays to
	// check their collision aginst them
	Shape * _shapes;
	int _numShapes;

	/* The view screen infromation needs to be passed in so it can calculate
	 * the necissary angles depending on the distance and location of the 
	 * cannon itself
	 */
	bool vScreenPassedIn; 

	Light* _lightSources;
	Light* _test;
	int _numLights;
	AmbientLight* _ambient;
	Camera*	_camera;
	ShaderTool* _shader;

	//World* _worldRef;

public:

	/*Constructors and Decontructors*/
	//The contructor will be passed in it's location default is (0,0,0)
	RayCannon( Vector3 vLoc, Shape* shapes, int totalShapes, Light* lightSources, int numberOfLights, AmbientLight* ambient, Camera* camera );
	RayCannon( Vector3 vLoc, World* worldRef);
	~RayCannon(void);

	/* Contains all necissary steps in order to determine the 
	 * particular point's color
	 */
	RayColor shootRayAt( Vector3 p);

};

