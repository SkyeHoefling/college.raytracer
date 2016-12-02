#pragma once
#include "RayColor.h"
#include "Ray.h"
#include "CollisionTool.h"
#include "PointCollision.h"
#include "World.h"
#include <cmath>
class ShaderTool
{
public:
		/*static RayColor applyPhongShader(AmbientLight* ambLight, 
										 Light* lightSources, 
										 int numberOfLights,
										 Vector3 surfaceNormal, 
										 Vector3 intersectionPoint,
										 Shape* colorfulShape,
										 Camera* camera);*/
	RayColor getBRDSColorFromCone( PointCollision * ptCol, Ray * reflectRay, int depth );
	static RayColor applyPhongShader(World* worldRef, PointCollision* collisionPoint);
	static RayColor gridProceduralShade( Shape * plane, Vector3 intersectionPoint );
	static RayColor SinProceduralShade( Shape * plane, Vector3 intersectionPoint );
	static RayColor ImageProceduralShade( Shape * plane, Vector3 intersectionPoint );	
	RayColor illuminate(Ray* r, int depth);
	ShaderTool(World * worldref, int maxDepth);
private:
	World * _worldRef;
	int _maxDepth;
	Ray* spawnShadowRay(Vector3* origin, int currentLight);
	Ray* spawnShadowRay(Vector3* origin);
	Ray* spawnReflectionRay(PointCollision* collisionPoint, Ray* currentRay);
};


