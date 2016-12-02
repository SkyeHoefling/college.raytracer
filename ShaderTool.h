#pragma once
#include "RayColor.h"
#include "Ray.h"
#include "CollisionTool.h"
#include "PointCollision.h"
#include "World.h"

//#define INDEX_OF_REFRACTION_AIR 1.0
//#define INDEX_OF_REFRACTION_GLASS 0.95
static double INDEX_OF_REFRACTION_AIR = 1.0;
static double INDEX_OF_REFRACTION_GLASS =0.95;
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
	Ray* spawnRefractionRay(PointCollision* collisionPoint, Ray* currentRay);
	Vector3 getPointOnOtherSideOfTheSphere(Ray* T, PointCollision* origin);
};


