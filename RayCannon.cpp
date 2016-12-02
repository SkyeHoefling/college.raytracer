#include "RayCannon.h"

//Constructors and deconstructors
RayCannon::RayCannon( Vector3 vLoc, Shape* shapes, int totalShapes,
	Light* lightSources, int numberOfLights, AmbientLight* ambient, Camera* camera) : Entity( vLoc)
{
	_shapes = shapes;
	_numShapes = totalShapes;
	_test = lightSources;
	_lightSources = lightSources;
	_numLights = numberOfLights;
	_ambient = ambient;
	_camera = camera;
}

RayCannon::RayCannon(Vector3 vLoc, World* worldRef): Entity (vLoc){
	_shader = new ShaderTool(worldRef, 4);

}

RayCannon::~RayCannon(void)
{
	//Do not delte shapes ( must be done in the world )
}

//Functions
RayColor RayCannon::shootRayAt( Vector3 p)
{
	Ray r = Ray( _position );
	r.setTarget( p );
	r.setEta(INDEX_OF_REFRACTION_AIR);
	return _shader->illuminate(&r, 0).getNormalized();
}
