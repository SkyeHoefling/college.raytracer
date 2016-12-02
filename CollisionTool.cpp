#include "CollisionTool.h"

bool CollisionTool::getClosestIntersection(Shape* shapes, int numShapes, Ray* ray, PointCollision &closestCollision){
	bool intersection = false;
	bool currentIntersection = false;
	PointCollision currentCollisionPoint;
	for(int i = 0; i < numShapes; i ++){
		// lets check if the current shape is too close to the ray origin
		if(ray->getOrigin().distanceFrom(shapes[i].getPosition()) < shapes[i].getBoundingRadius() + 5)
			continue;
		currentIntersection = CollisionTool::collidesWithShape(&shapes[i],
															   ray,
															   currentCollisionPoint);
		if(currentIntersection){
			if(!intersection){
				closestCollision = currentCollisionPoint;
			} else {
				double newDistance = 
					currentCollisionPoint.getPosition().distanceFrom(ray->getOrigin());
				double oldDistance =
					closestCollision.getPosition().distanceFrom(ray->getOrigin());
				if(newDistance < oldDistance) 
					closestCollision = currentCollisionPoint;
			}
		}
		if(currentIntersection || intersection)
			intersection = true;
	}
	return intersection;
}
bool CollisionTool::collidesWithShape(Shape* theShape, Ray* ray, PointCollision &collision){
	if(theShape->getType() == SHAPE_PLANE){
		return collidesWithPlane(theShape, ray, collision);
	}else{
		return collidesWithSphere(theShape, ray, collision);
	}
	return false;
}

bool CollisionTool::collidesWithSphere(Shape* theShape, Ray* r, PointCollision &collision){
	Vector3 shapePosition = theShape->getPosition();
	Vector3 endPoint = r->getTarget();
	Vector3 origin = r->getOrigin();
	Vector3 ray = Vector3(endPoint.getX() - origin.getX(),
						  endPoint.getY() - origin.getY(),
						  endPoint.getZ() - origin.getZ());

	double a = ray.getX() * ray.getX() + ray.getY() * ray.getY() + ray.getZ() * ray.getZ();
	double b = 2 * ((ray.getX()) * (origin.getX() - shapePosition.getX()) +
					(ray.getY()) * (origin.getY() - shapePosition.getY()) +
					(ray.getZ()) * (origin.getZ() - shapePosition.getZ()));
	double c = 
		(shapePosition.getX() * shapePosition.getX()) +
		(shapePosition.getY() * shapePosition.getY()) +
		(shapePosition.getZ() * shapePosition.getZ()) +
		(origin.getX() * origin.getX()) +
		(origin.getY() * origin.getY()) +
		(origin.getZ() * origin.getZ()) -
		2 * (
			(shapePosition.getX() * origin.getX()) +
			(shapePosition.getY() * origin.getY()) +
			(shapePosition.getZ() * origin.getZ())
			) -
		(theShape->getBoundingRadius() * theShape->getBoundingRadius());
	double answer = b * b - 4 * a * c;
	if(answer > 0){
		double t = (- b - sqrt( answer)) / (2*a);
		collision = PointCollision(theShape, Vector3(
			origin.getX() + (t * ray.getX()),
			origin.getY() + (t * ray.getY()),
			origin.getZ() + (t * ray.getZ())));
		collision.calculateSurfaceNormal(theShape);
		return true;
	}
	else return false;
}

bool CollisionTool::collidesWithPlane(Shape* theShape, Ray* ray, PointCollision &collision){
	Vector3 normal = Vector3(-1,0,0);
	Vector3 endPoint = ray->getTarget();
	Vector3 origin = ray->getOrigin();
	Vector3 ab = endPoint - origin;
	double d = normal.dot(theShape->getPosition());

	double u = normal.dot(theShape->getPosition() - origin) /
		normal.dot(origin - endPoint);
	//double u = d - normal.dot(origin) / normal.dot(ab);
	if(u > 0 && u < 1){
		collision =  PointCollision(theShape, ab * u + origin);		
		collision.calculateSurfaceNormal(theShape);
		return true;
	}
	else return false;
}