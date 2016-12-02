#include "ShaderTool.h"
#include "Vector3.h"
#include <stdio.h>
#include <math.h>
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
			dirIncomingLight = collisionPoint->getPosition1() -
							   worldRef->getLightSources()[i].getPosition();
			dirIncomingLight.normalize();
			sigma = sigma + dirIncomingLight.dot(collisionPoint->getSurfaceNormalP1());
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
			collisionPoint->getPosition1() - worldRef->getCamera()->getPosition();
		viewingDirection.normalize();

		// NOW: lets calculate the specular solution since we have all the pieces
		sigma = 0;
		for(int i = 0; i < worldRef->getTotalLightSources(); i ++){
			// get direction of incoming light (S)
			dirIncomingLight = collisionPoint->getPosition1() -
							   worldRef->getLightSources()[i].getPosition();
			dirIncomingLight.normalize();
			// calculate our mirror reflection
			aAsDoub = 2 * (dirIncomingLight.dot(collisionPoint->getSurfaceNormalP1()) / 
				(collisionPoint->getSurfaceNormalP1().length() * collisionPoint->getSurfaceNormalP1().length()));
			a = collisionPoint->getSurfaceNormalP1() * aAsDoub;
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
			double colY = collisionPoint.getPosition1().getY() + Y_OFFSET;
			double colZ = collisionPoint.getPosition1().getZ() + Z_OFFSET;

			double shapeY = collisionPoint.getShape()->getPosition().getY();
			double shapeZ = collisionPoint.getShape()->getPosition().getZ();

			double dist_W = 250;
			double dist_H = 400;

			if( abs( colY - shapeY) < dist_W && abs( colZ-shapeZ ) < dist_H ){
				collisionPoint.setColor(
					ShaderTool::gridProceduralShade(collisionPoint.getShape(), 
												collisionPoint.getPosition1() ));
			}else{
				collisionPoint.setColor( _worldRef->getAmbientLight()->getColor() );
			}
			return collisionPoint.getColor();
		}
		else collisionPoint.setColor();
      
		// BASIC local illumination, returns the objects color???
		resultColor = ShaderTool::applyPhongShader(_worldRef, &collisionPoint);		
		Ray* shadow = spawnShadowRay(&collisionPoint.getPosition1());
      
		//resultColor = resultColor + illuminate(shadow, _maxDepth - 1);
		if(depth < _maxDepth){						
			if(collisionPoint.getShape()->getReflection() > 0){
				Ray * reflection = spawnReflectionRay(&collisionPoint, ray);
				resultColor = resultColor +
					(illuminate(reflection, depth+1) * collisionPoint.getShape()->getReflection());
			}
			if(collisionPoint.getShape()->getTransparent() > 0){
				Ray* refraction = spawnRefractionRay(&collisionPoint, ray);
				resultColor = resultColor + 
					(illuminate(refraction, depth+1) * collisionPoint.getShape()->getTransparent());
			}						
		}
	}
	return resultColor;
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
	Vector3 a = collisionPoint->getSurfaceNormalP1() * 
		(currentRay->asVector3().normalized().dot(collisionPoint->getSurfaceNormalP1()) / 
		collisionPoint->getSurfaceNormalP1().length() * collisionPoint->getSurfaceNormalP1().length());
	Vector3 reflectionVector = currentRay->asVector3().normalized() - (a.normalized() * 2);
	Ray* reflection = new Ray(collisionPoint->getPosition1());
	reflection->setTarget(collisionPoint->getPosition1() + (reflectionVector.normalized() *5000));
	//reflection->setEta(INDEX_OF_REFRACTION_AIR);
	return reflection;
}

Ray* ShaderTool::spawnRefractionRay(PointCollision* collisionPoint, Ray* currentRay){
	// refraction ray math:
	// *First lets demonstrate some simple formulas*
	// (eta)i = sin(theta)t
	// ------   -----------
	// (eta)t   sin(theta)i
	//
	//                   eta(i)
	// (alpha) = (eta)it = ------
	//                   eta(t)
	//
	// cos(theta)i = -D [dot] N
	//
	// ** Lets get into the formula now **
	// T = (alpha)D + (beta)N
	// T = (eta)it(-D [dot] N - sqrt(1 - (eta)it((-D [dot] N)^2 -1))N
	// T = (alpha)(-D [dot] N - sqrt(1 - (alpha)( (-D [dot] N)^2 - 1)) N
	double alpha;
	double costheta;
	double betasqrt;
	double beta;
	Vector3 normal = collisionPoint->getSurfaceNormalP1();
	Vector3 endPoint = Vector3();
	
	double eta = currentRay->getEta();
	double ior = collisionPoint->getShape()->getIndexOfRefraction();
	if(eta == ior){
		// we are inside!! bamf
		normal = normal * -1;
		collisionPoint->getShape()->setIndexOfRefraction(INDEX_OF_REFRACTION_AIR);
	}
		
	eta = INDEX_OF_REFRACTION_AIR;
	alpha = eta / ior;
	costheta = currentRay->asVector3().dot(normal);
	betasqrt = 1 - alpha*alpha * (costheta*costheta -1);
	//if(betasqrt < 0) return spawnReflectionRay(collisionPoint, currentRay);
	beta = alpha * costheta - sqrt(betasqrt);

	endPoint = currentRay->asVector3() * alpha + normal * beta;

	Ray* transmission = new Ray(collisionPoint->getPosition1());
	transmission->setTarget(endPoint.normalized() * 5000);
	transmission->setEta(collisionPoint->getShape()->getIndexOfRefraction());	
	endPoint = currentRay->getTarget();
	currentRay = new Ray(collisionPoint->getPosition1());
	currentRay->setTarget(endPoint.normalized());
	//Ray* nRay = new Ray(getPointOnOtherSideOfTheSphere(currentRay, collisionPoint));
	//nRay->setTarget(endPoint);
	transmission = new Ray(getPointOnOtherSideOfTheSphere(currentRay, collisionPoint));
	transmission->setTarget(endPoint);
	return transmission;
}

Vector3 ShaderTool::getPointOnOtherSideOfTheSphere( Ray * T , PointCollision* origin ){
	Ray radiusRay = Ray( origin->getPosition1() );
	radiusRay.setTarget( origin->getShape()->getPosition() );

	double radius = origin->getShape()->getBoundingRadius();
	double inside =  T->asVector3().dot( radiusRay.asVector3() ) / radius;
	double toRad = (3.14/180);
	double tempTheta = cos(inside *  toRad);
	double centerTheta = 90 - tempTheta;

	double centerDist = radius * sin( centerTheta );
	T->setTarget( T->getTarget() * ( centerDist * 2 ) );

	return T->getTarget();
}