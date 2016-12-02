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
	_declspec(deprecated("(deprecated) **Ray Tracing does not use the phong shading model **"))
		static RayColor applyPhongShader(AmbientLight* ambLight, 
										 Light** lightSources, 
										 int numberOfLights,
										 Vector3 surfaceNormal, 
										 Vector3 intersectionPoint,
										 Shape* colorfulShape,
										 Camera* camera);
	static RayColor GridProceduralShade( Shape * plane, Vector3 intersectionPoint );
	static RayColor SinProceduralShade( Shape * plane, Vector3 intersectionPoint );
	static RayColor ImageProceduralShade( Shape * plane, Vector3 intersectionPoint );	
	RayColor illuminate(Ray* r, int depth);
	ShaderTool(World * worldref, int maxDepth);
private:
	World * _worldRef;

	int _maxDepth;
};


