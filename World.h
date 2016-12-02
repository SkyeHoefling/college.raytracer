#pragma once
#include "Shape.h"
#include "Light.h"
#include "AmbientLight.h"
#include "Camera.h"

class World
{
private:
	Shape* _shapes;
	int _totalShapes;
	Light* _lightSources;
	int _totalLightSources;
	AmbientLight* _ambientLight;
	Camera* _camera;
public:
	World(void);
	World(Shape* shapes, int totalShapes, Light lightSources[], int lightSourceCount,
		AmbientLight* ambient, Camera* camera);
	~World(void);

	// accessors
	Shape* getShapes();
	int getTotalShapes();

	Light* getLightSources();
	int getTotalLightSources();

	AmbientLight* getAmbientLight();
	Camera* getCamera();
};

