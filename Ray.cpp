#include "Ray.h"

Ray::Ray( Vector3 loc)
{
	_origin = Vector3( loc.getX(), loc.getY(), loc.getZ() );
	//_color = RayColor( );
}


Ray::~Ray(void)
{
}

/*void Ray::setWorldLightingReference( Light* lightSources, int numberOfLights, AmbientLight* ambient )
{
	_lightSources = new Light[numberOfLights];
	for(int i = 0; i < numberOfLights; i ++){
		_lightSources[i] = lightSources[i];
	}
	_numberOfLights = numberOfLights;
	_ambient = ambient;
}

void Ray::setCameraReference(Camera* camera)
{
	_camera = camera;
}*/

void Ray::setTarget(Vector3 p){
	_target = p;
}
Vector3 Ray::getTarget(){
	return _target;
}
Vector3 Ray::getOrigin(){
	return _origin;
}
Vector3 Ray::asVector3(){
	return _target-_origin;
}


/*RayColor Ray::getColor(){
	return collidesWith();
}

void Ray::calculateAngles(){
	double dist = _origin.distanceFrom( _target );

	Vector2 start = Vector2( _origin.getX(), _origin.getY() );
	Vector2 end = Vector2( _target.getX(), _target.getY() );

	_theta = acos( start.dot( end ) * ToRad );

	start = Vector2( _origin.getX(), _origin.getZ() );
	end = Vector2( _target.getX(), _target.getZ() );

	_phi = acos( start.dot( end ) * ToRad);

}

void Ray::checkThese( Shape * shapes, int total_shapes )
{
	_numShapes = total_shapes;
	_collisionShapes = shapes;
}*/

//RayColor Ray::getAppropriateColor(){
//	Vector3 surfaceNormal;
//	for( int i = 0; i < _numShapes; i++ ){
//		/*shape * curShape = _collisionShapes + i*sizeof(shape);*/
//		surfaceNormal = collidesWith( &_collisionShapes[i]);
//		if(surfaceNormal != Vector3()){
//
//			//Add the Phong shader color here
//			//return ShaderTool.applyPhongShader();
//			
//			
//			//this will go in get the point once lighting and shaders are implemented
//			//for the time being (checkpoint 2) we are just going to grab the color of
//			//the shape.s
//			/*return (*curShape).getColor();*/
//			//return (&_collisionShapes[i])->getColor(surfaceNormal);
//		}
//		//if( collidesWith( (*(_collisionShapes))[ i *sizeof( entity ) ]
//
//	}
//	//if not found, return black
//	return RayColor();
//}

//RayColor Ray::collidesWith(){	
//	// if seeLight does not collide (the surface should = Vector3())
//	// then we can see the light source (important for phong shading)
//	PointCollision seeLight = PointCollision();
//	Light* visibleLights = new Light[_numberOfLights];
//	int visibleLightsCount = 0;
//	RayColor r;
//	PointCollision collision;
//	PointCollision shadowCollision;
//	Shape* otherShapes = new Shape[2];
//	int otherShapesCounter = 0;
//	bool drawShadow = false;
//	for(int i = 0; i < _numShapes; i ++){
//		if(CollisionTool::collidesWithShape(&_collisionShapes[i], _target, _origin, collision)){
//			
//			//First we check to see if its a plane, if it is we need to proceduraly shade it
//			if( _collisionShapes[i].getType() == SHAPE_PLANE ){
//
//				int PLANE_WIDTH = 15;
//				double PLANE_HEIGHT = 231;
//				double xPos = collision.getPosition().getX();
//				double yPos = collision.getPosition().getY();
//				double zPos = collision.getPosition().getZ();
//
//				//We want to get one of the spheres, yet make sure we dont get a indexOutOfBounds issue
//				int j = ( i+1 < _numShapes ) ? i+1 : i-1;
//				
//				if( abs( otherShapes[1].getPosition().getY() - yPos ) > PLANE_WIDTH ){
//					return _ambient->getColor();
//				}
//				double abs_ = abs( otherShapes[1].getPosition().getZ() - zPos ); 
//
//				if(  abs_ < PLANE_HEIGHT ){
//					return _ambient->getColor();	
//				}else{
//					int cat = 5;
//				}
//				//Attempt to make bounds for our plane
//				/*double distanceFrom = collision.getPosition().distanceFrom( _collisionShapes[i].getPosition() );
//				if( distanceFrom> 265 ){
//					return _ambient->getColor();
//				}*/
//
//
//				RayColor calcColor = ShaderTool::GridProceduralShade( &_collisionShapes[i], collision.getPosition() );
//				_collisionShapes[i].setAmbientColor( calcColor );
//				return _collisionShapes[i].getAmbientColor();
//			//otherwise shade normal
//			}else{
//
//				// lets get all the other shapes excluding us
//				otherShapes = new Shape[_numShapes - 1];
//				otherShapesCounter = 0;
//				for(int t = 0; t < _numShapes; t ++){
//					if(&_collisionShapes[t] != &_collisionShapes[i]){					
//						otherShapes[otherShapesCounter] = _collisionShapes[t];					
//						otherShapesCounter++;
//					}
//				}
//				// lets shoot a ray at the light source, if we collide with
//				// an object -> then we can't see any lights return ambient light
//				for(int l = 0; l < _numberOfLights; l ++){ // we need to check each light source
//					for(int s = 0; s < _numShapes - 1; s ++){ // other shapes could obstruct our light
//						drawShadow = CollisionTool::collidesWithShape(&_collisionShapes[s],
//								 									 _lightSources[l].getPosition(), 
//																	 _target,
//																	 shadowCollision);				
//					}
//					if(!drawShadow){ // THIS MEANS WE CAN SEE THE LIGHT
//						visibleLights[visibleLightsCount] = _lightSources[l];
//						visibleLightsCount++;
//					}
//				}
//				r = ShaderTool::applyPhongShader(_ambient, &visibleLights, visibleLightsCount,
//					collision.getSurfaceNormal(), collision.getPosition(), &_collisionShapes[i], 
//					_camera);
//				return r;//_collisionShapes[i].getColor();
//			}
//		}
//	}
//	return _ambient->getColor();
//}