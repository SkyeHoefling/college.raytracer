#include "World.h"


World::World(void)
{
	_totalShapes = 0;
}

World::World(Shape* shapes, int totalShapes, Light lightSources[], int lightSourceCount,
		AmbientLight* ambient, Camera* camera){
	_shapes = shapes;
	_totalShapes = totalShapes;
	//_lightSources = lightSources;
	// create light source array
	_lightSources = new Light[lightSourceCount];
	for(int i = 0; i < lightSourceCount; i ++){
		_lightSources[i] = lightSources[i];
	}
	_totalLightSources = lightSourceCount;
	_ambientLight = ambient;
	_camera = camera;
}

World::~World(void)
{
	delete _shapes;
}

Shape* World::getShapes()	{	return _shapes;			}
int World::getTotalShapes()	{	return _totalShapes;	}

Light* World::getLightSources()		{	return _lightSources;		}
int World::getTotalLightSources()	{	return _totalLightSources;	}

AmbientLight* World::getAmbientLight()	{	return _ambientLight;	}
Camera*	World::getCamera()				{	return _camera;			}