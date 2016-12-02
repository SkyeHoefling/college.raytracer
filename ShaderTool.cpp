#include "ShaderTool.h"
#include "Vector3.h"
#include <stdio.h>
#include <iostream>

#define RED RayColor( 1.0f, 0.0f, 0.0f )
#define YELLOW RayColor( 1.0f, 1.0f, 0.0f )
//#define PI 3.1456 redifined
#define MAX_DEPTH 5
typedef unsigned char BYTE;

RayColor ShaderTool::applyPhongShader(AmbientLight* ambLight,
									  Light** lightSources,
									  int numberOfLights,
									  Vector3 surfaceNormal,
									  Vector3 intersectionPoint,
									  Shape* colorfulShape,
									  Camera* camera)
{
	// solve for L(v) by adding up 3 steps
	// 1. Ka x La (according to slides)
	// 2. Kd * Sigma(Li(Si [dot] N))
	// 3. Ks * Sigma(Li(Ri [dot] V) ^ Ke)
	// *note* Li(----) == Function Li
	// THIS IS IMPORTANT
	// ONLY APPLY STEP 1 IF YOU CAN'T SEE THE LIGHT SOURCE

	// To calculate R:
	// R = S + 2a
	// R = S - 2 * {(S [dot] N)/(|N|^2)} * N

	// To calculate V:
	// Viewing direction = camera position - point of intersection

	// To Calculate S:
	// Direction of Incoming Light =
	// light position - point of intersection
	
	// useful variables
	// Ambient - background light -> Ka
	// Diffuse - Lambertian reflection -> Kd
	// Specular - mirror-like reflection - > Ks
	// Exponent - controls size of specular highlight -> Ke
	// Light Source - Our current light source at element i -> Si
	// Ambient Light - Our ambient light of the room -> La
	// Normal Vector - Our surface normal vector -> N
	// Reflection of Source, and normal -> Ri
	// Viewing Direction -> V
	Vector4 ambientSolution = Vector4();
	Vector4 diffuseSolution = Vector4();
	Vector4 specularSolution = Vector4();
	
	// Calculate part 1 the ambient solution
	// 1. Ka x La
	ambientSolution = Vector4(ambLight->getColor().asVector3() * colorfulShape->getAmbientColor().asVector3());
	if(numberOfLights > 0){
		// To Calculate S:
		// Direction of Incoming Light =
		// light position - point of intersection
		Vector3 dirIncomingLight;

		// Calculate part 2 the diffuse solution
		// 2. Kd * Sigma(Li(Si [dot] N))
		double sigma = 0;
		for(int i = 0; i < numberOfLights; i ++){
			dirIncomingLight = intersectionPoint -
							   lightSources[i]->getPosition();
			dirIncomingLight.normalize();
			sigma = sigma + dirIncomingLight.dot(surfaceNormal);
		}
		diffuseSolution = Vector4(colorfulShape->getDiffuseColor().asVector3() * sigma);

		// Calculate part 3 the specular solution
		// 3. Ks * Sigma(Li(Ri [dot] V) ^ Ke)

		// To calculate R:
		// perfect mirror reflection
		// R = S + 2a
		// R = S - 2 * {(S [dot] N)/(|N|^2)} * N
		Vector3 mirrorReflection; // used for R

		
		// aAsDoub = 2 * S [dot] N
		//				 ----------
		//				   |N| ^ 2  <--- Remember |N| is the magnitutde of the vector
		double aAsDoub;
		// a == what a is above in the reflection calculation
		Vector3 a;

		// To calculate V:
		// Viewing direction = camera position - point of intersection
		Vector3 viewingDirection = 
			intersectionPoint - camera->getPosition();
		viewingDirection.normalize();

		// NOW: lets calculate the specular solution since we have all the pieces
		sigma = 0;
		for(int i = 0; i < numberOfLights; i ++){
			// get direction of incoming light (S)
			dirIncomingLight = intersectionPoint -
							   lightSources[i]->getPosition();
			dirIncomingLight.normalize();
			// calculate our mirror reflection
			aAsDoub = 2 * (dirIncomingLight.dot(surfaceNormal) / 
				(surfaceNormal.length() * surfaceNormal.length()));
			a = surfaceNormal * aAsDoub;
			mirrorReflection = dirIncomingLight - a;
			sigma = sigma + pow(mirrorReflection.dot(viewingDirection), 
				colorfulShape->getExponentColor());
		}
		specularSolution = Vector4(colorfulShape->getSpecularColor().asVector3() * sigma);
	}
	// this part is simple just add up the 3 solutions, and return
	RayColor pixelColor = RayColor(ambientSolution.getNormalized() +
								   diffuseSolution.getNormalized() +
								   specularSolution.getNormalized());
	return pixelColor.getNormalized();
}

RayColor ShaderTool::GridProceduralShade( Shape * plane, Vector3 intersectionPoint )
{
	double TILE_W = 5, TILE_H = .5;
	int x_tiles = (int) ( ( intersectionPoint.getX() - plane->getPosition().getX() ) / TILE_W );
	int y_tiles = (int) ( ( intersectionPoint.getY() - plane->getPosition().getY() ) / TILE_W );
	int z_tiles = (int) ( ( intersectionPoint.getZ() - plane->getPosition().getZ() ) / TILE_H );
	
	int row = ( y_tiles % 2 == 0 ) ? 0 : 1;
	int col = ( z_tiles % 2 == 0 ) ? 1 : 0;
	
	return ( row ^ col ) ? RED : YELLOW;
}

RayColor ShaderTool::SinProceduralShade( Shape * plane, Vector3 intersectionPoint )
{
	double RADIUS = 5;
	Vector3 p1 = intersectionPoint;
	Vector3 p2 = plane->getPosition();

	//Add some modifiers to flare it up
	p1 = Vector3( p1.getX() , p1.getY() * 2  , p1.getZ() * 3 );
	p2 = Vector3( p2.getX() , p2.getY() + 50 , p2.getZ() -50 );

	//get the distance between the two points
	double dist = p1.distanceFrom( p2 );
	return YELLOW.getNormalized()	* PI  *	.3 *cos( dist );
}

// Get the size of a file
long getFileSize(FILE *file)
{
	long lCurPos, lEndPos;
	lCurPos = ftell(file);
	fseek(file, 0, 2);
	lEndPos = ftell(file);
	fseek(file, lCurPos, 0);
	return lEndPos;
}

RayColor ShaderTool::ImageProceduralShade( Shape * plane, Vector3 intersectionPoint )
{
	const char *filePath = "C:\\Users\\IGMAdmin\\Desktop\\checkpoint3.p";
	BYTE * fileBuffer; FILE * file;

	if((file = fopen( filePath, "rb" )) == NULL )
		return RayColor( 1.0f, 1.0f, 1.0f );
	else{
		long fileSize = getFileSize( file );
		fread( fileBuffer, fileSize, 1, file );
	}
	
	double TILE_W = 5, TILE_H = .5;
	int x_tiles = (int) ( ( intersectionPoint.getX() - plane->getPosition().getX() ) / TILE_W );
	int y_tiles = (int) ( ( intersectionPoint.getY() - plane->getPosition().getY() ) / TILE_W );
	int z_tiles = (int) ( ( intersectionPoint.getZ() - plane->getPosition().getZ() ) / TILE_H );
	
	int row = ( y_tiles % 2 == 0 ) ? 0 : 1;
	int col = ( z_tiles % 2 == 0 ) ? 1 : 0;
	
	return ( row ^ col ) ? RED : YELLOW;
}
ShaderTool::ShaderTool(World * worldRef, int maxDepth){
	_worldRef = worldRef;
	_maxDepth = maxDepth;
}
RayColor ShaderTool::illuminate(Ray * ray, int depth){
	// LETS ILLUMINATE
	PointCollision collisionPoint;
	PointCollision currentCollisionPoint;
	bool intersection = false;
	for(int i = 0; i < _worldRef->getTotalShapes(); i ++){
		if(CollisionTool::collidesWithSphere(&_worldRef->getShapes()[i],
											 ray->getTarget(),
											 ray->getOrigin(),
											 currentCollisionPoint) || intersection)
			intersection = true;
		if(intersection){
			double newDistance = 
				currentCollisionPoint.getPosition().distanceFrom(_worldRef->getCamera()->getPosition());
			double oldDistance =
				collisionPoint.getPosition().distanceFrom(_worldRef->getCamera()->getPosition());
			if(newDistance < oldDistance) collisionPoint = currentCollisionPoint;
		}
	}
	if(!intersection) {
		return _worldRef->getAmbientLight()->getColor();
	} else {
		return collisionPoint.getShape()->getColor();
	}
}