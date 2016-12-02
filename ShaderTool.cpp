#include "ShaderTool.h"
#include "Vector3.h"
#include <stdio.h>
#include <iostream>

#define RED RayColor( 1.0f, 0.0f, 0.0f )
#define YELLOW RayColor( 1.0f, 1.0f, 0.0f )
#define WHITE RayColor( 1.0f, 1.0f, 1.0f )
//#define PI 3.1456 redifined
#define MAX_DEPTH 5
typedef unsigned char BYTE;

/*RayColor ShaderTool::applyPhongShader(AmbientLight* ambLight,
									  Light* lightSources,
									  int numberOfLights,
									  Vector3 surfaceNormal,
									  Vector3 intersectionPoint,
									  Shape* colorfulShape,
									  Camera* camera)*/
RayColor ShaderTool::applyPhongShader(World* worldRef, PointCollision* collisionPoint)
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
	ambientSolution = Vector4(worldRef->getAmbientLight()->getColor().asVector3() * collisionPoint->getShape()->getAmbientColor().asVector3());
	if(worldRef->getTotalLightSources() > 0){
		// To Calculate S:
		// Direction of Incoming Light =
		// light position - point of intersection
		Vector3 dirIncomingLight;

		// Calculate part 2 the diffuse solution
		// 2. Kd * Sigma(Li(Si [dot] N))
		double sigma = 0;
		for(int i = 0; i < worldRef->getTotalLightSources(); i ++){
			dirIncomingLight = collisionPoint->getPosition() -
							   worldRef->getLightSources()[i].getPosition();
			dirIncomingLight.normalize();
			sigma = sigma + dirIncomingLight.dot(collisionPoint->getSurfaceNormal());
		}
		diffuseSolution = Vector4(collisionPoint->getShape()->getDiffuseColor().asVector3() * sigma);

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
			collisionPoint->getPosition() - worldRef->getCamera()->getPosition();
		viewingDirection.normalize();

		// NOW: lets calculate the specular solution since we have all the pieces
		sigma = 0;
		for(int i = 0; i < worldRef->getTotalLightSources(); i ++){
			// get direction of incoming light (S)
			dirIncomingLight = collisionPoint->getPosition() -
							   worldRef->getLightSources()[i].getPosition();
			dirIncomingLight.normalize();
			// calculate our mirror reflection
			aAsDoub = 2 * (dirIncomingLight.dot(collisionPoint->getSurfaceNormal()) / 
				(collisionPoint->getSurfaceNormal().length() * collisionPoint->getSurfaceNormal().length()));
			a = collisionPoint->getSurfaceNormal() * aAsDoub;
			mirrorReflection = dirIncomingLight - a;
			sigma = sigma + pow(mirrorReflection.dot(viewingDirection), 
				collisionPoint->getShape()->getExponentColor());
		}
		specularSolution = Vector4(collisionPoint->getShape()->getSpecularColor().asVector3() * sigma);
	}
	// this part is simple just add up the 3 solutions, and return
	RayColor pixelColor = RayColor(ambientSolution.getNormalized() +
								   diffuseSolution.getNormalized() +
								   specularSolution.getNormalized());
	return pixelColor.getNormalized();
}

RayColor ShaderTool::gridProceduralShade( Shape * plane, Vector3 intersectionPoint )
{
	RayColor red = RED, yellow = YELLOW, white = WHITE;
	RayColor returnColor = YELLOW;

	double TILE_W = 20, TILE_H = 20;
	double Iy = intersectionPoint.getY();
	double Iz = intersectionPoint.getZ();

	int y_tiles =  (int)( Iy / TILE_W );
	int z_tiles =  (int)( Iz / TILE_H );

	int row = ( y_tiles % 2 == 0 ) ? 0 : 1;
	int col = ( z_tiles % 2 == 0 ) ? 0 : 1;

	//Allow me to explain this hack
	//the basis of it is the ternary logic of (( col ^ row ) ? RED : YELLOW. Basically determing the
	// XOR of what the color should be, either red or yellow. This creates the checker pattern. However,
	//by itself it will line up w/ other quadrents making a double wide section along the y and z axis.
	//to correct this we encase the ternary logic within another one, which checks against the sign of
	//our current posisiton, effectively creating an XOR of the pattern or XORs. However the one line only
	//accounts for 3 quadrants, we still need to alternate one more time. The simpleest way to do that is
	//to check to see if we are in that quadrent and if we are, revert the colors that it originally thought
	//it was going to render.
	returnColor =(Iz > 0 || Iy > 0 ) ? (( col ^ row ) ? YELLOW : RED) :  (( col ^ row ) ? RED : YELLOW);
	if( Iz > 0 && Iy > 0 ){
		if( returnColor == red ){
			returnColor = yellow;
		}else{
			returnColor = red;
		}
	}

	return returnColor;
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

ShaderTool::ShaderTool(World * worldRef, int maxDepth){
	_worldRef = worldRef;
	_maxDepth = maxDepth;
}
RayColor ShaderTool::illuminate(Ray * ray, int depth){
	// LETS ILLUMINATE
	// okay
	PointCollision collisionPoint;
	RayColor resultColor;
	bool intersection = CollisionTool::getClosestIntersection(_worldRef->getShapes(),
															  _worldRef->getTotalShapes(), 
															  ray, 
															  collisionPoint);
	if(!intersection) {
		resultColor = _worldRef->getAmbientLight()->getColor();
	} else {
		if(collisionPoint.getShape()->getType() == SHAPE_PLANE){
			double Y_OFFSET = -150;
			double Z_OFFSET = -200;
			double colY = collisionPoint.getPosition().getY() + Y_OFFSET;
			double colZ = collisionPoint.getPosition().getZ() + Z_OFFSET;

			double shapeY = collisionPoint.getShape()->getPosition().getY();
			double shapeZ = collisionPoint.getShape()->getPosition().getZ();

			double dist_W = 250;
			double dist_H = 400;

			if( abs( colY - shapeY) < dist_W && abs( colZ-shapeZ ) < dist_H ){
				collisionPoint.setColor(
					ShaderTool::gridProceduralShade(collisionPoint.getShape(), 
												collisionPoint.getPosition() ));
			}else{
				collisionPoint.setColor( _worldRef->getAmbientLight()->getColor() );
			}
			return collisionPoint.getColor();
		}
		else collisionPoint.setColor();
      
		// BASIC local illumination, returns the objects color???
		resultColor = ShaderTool::applyPhongShader(_worldRef, &collisionPoint);		
		Ray* shadow = spawnShadowRay(&collisionPoint.getPosition());
      
		//resultColor = resultColor + illuminate(shadow, _maxDepth - 1);
		if(depth < _maxDepth){			
			if(collisionPoint.getShape()->getReflection() > 0){
         //Create cone from Distance from collision Point
         //for loop pick X number of random points within a circly
         // each reflection ray, illuminate( ray, curDepth++ )
				Ray * reflection = spawnReflectionRay(&collisionPoint, ray);
				//resultColor = resultColor + (illuminate(reflection, depth+1) * collisionPoint.getShape()->getReflection());
				RayColor brdsColor = getBRDSColorFromCone( &collisionPoint, reflection, depth + 1 );
				resultColor = resultColor + brdsColor;
			}
			if(collisionPoint.getShape()->getTransparent() > 0){

			}			
		}
	}
	return resultColor;
}

RayColor ShaderTool::getBRDSColorFromCone( PointCollision * ptCol, Ray * reflectRay, int depth ){
	RayColor newColor = WHITE;
	double averageR = 0, averageG = 0, averageB = 0;
	int CONE_DIST = 400;
	int CONE_RADIUS = 15;
	const int total_rays = 20;
	Ray brdsRays[ total_rays ];
	Ray baseRay = Ray( Vector3( reflectRay->asVector3().getX(), reflectRay->asVector3().getY(), reflectRay->asVector3().getZ() ) ); 
	Vector3 baseVector = baseRay.asVector3();
	baseVector.normalize();
	baseVector = baseVector * CONE_DIST;
	double MAX_THETA = asin( CONE_RADIUS / baseVector.length() );


	for( int i = 0 ; i < total_rays ; i++ ){
		brdsRays[i] = Ray( Vector3( baseVector.getX() + CONE_RADIUS / cos( MAX_THETA * rand() ),
									baseVector.getX() + CONE_RADIUS / sin( MAX_THETA * rand() ), 
									baseVector.getX() + CONE_RADIUS / cos( MAX_THETA * rand() ) 
									));
	}
	//brdsRays = brdsRays - sizeof( Ray ) * total_rays;
	//loop through and get illumination per reflect array
	for( int i = 0; i <	total_rays; i++ ){
		Ray ray = brdsRays[i];
		RayColor curRay = illuminate( &ray , depth + 1);
		averageR += curRay.getR();
		averageG += curRay.getG();
		averageB += curRay.getB();
	}
	//average colors
	averageR /= total_rays;
	averageG /= total_rays;
	averageB /= total_rays;
	//return average
	newColor.setColor( averageR, averageG, averageB );
	return newColor;
}

Ray* ShaderTool::spawnShadowRay(Vector3* origin, int currentLight){
	Ray* shadow = new Ray(*origin);
	shadow->setTarget(_worldRef->getLightSources()[currentLight].getPosition());
	return shadow;
}
Ray* ShaderTool::spawnShadowRay(Vector3* origin){
	return spawnShadowRay(origin, 0);
}
Ray* ShaderTool::spawnReflectionRay(PointCollision* collisionPoint, Ray* currentRay){
	// reflection ray formula
	//			  S [dot] N
	// R = S - 2  ---------- N
	//				  |N|^2
	// remember variables:
	// S: incoming ray or currentRay
	// N: normal at collisionPoint
	//
	// Equation breakdown:
	// R = S - 2a
	//		S [dot] N
	// a = ----------- N
	//		  |N|^2
	Vector3 a = collisionPoint->getSurfaceNormal() * 
		(currentRay->asVector3().normalized().dot(collisionPoint->getSurfaceNormal()) / 
		collisionPoint->getSurfaceNormal().length() * collisionPoint->getSurfaceNormal().length());
	Vector3 reflectionVector = currentRay->asVector3().normalized() - (a.normalized() * 2);
	Ray* reflection = new Ray(collisionPoint->getPosition());
	reflection->setTarget(collisionPoint->getPosition() + (reflectionVector.normalized() *5000));
	return reflection;

}
