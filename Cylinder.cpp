#include "Cylinder.h"


Cylinder::Cylinder( double radius, int slices, int stacks)
{
	numTriangles = 0;
	 _radius = radius;
	 _slices = slices;
	 _stacks = stacks;
	 _totalTriangles = ( _slices * 2 ) + ( _slices * _stacks * 2 );
	 _triangles[ _totalTriangles ];
	 makeCylinder( _radius, _slices, _stacks );
}


Cylinder::~Cylinder(void)
{
	numTriangles = 0;
	delete _triangles;

}

double Cylinder::getRadius()
{
	return _radius;
}

int Cylinder::getNumTriangles()
{
	return _totalTriangles;
}

void Cylinder::translateCylinder()
{

}

void Cylinder::makeCylinder (double radius, int slices, int stacks)
{
	double cylindarHeight = 1;

	double angle = 360 / (double) slices;
	double height = 1  / (double) stacks;
	double radians = (double)ToRad;


	for( int i = 0; i < slices; i++ ){
		double currentAngle = angle * i;
		double nextAngle = currentAngle + angle;

		//Create top circle slice
		double x1, y1, z1, x2, y2, z2, x3, y3, z3;

		x1 = 0;
		y1 = .5;
		z1 = 0;

		x2 = radius * cos( currentAngle * radians );
		y2 = .5;
		z2 = radius * sin( currentAngle * radians );

		x3 =  radius * cos( nextAngle * radians );
		y3 =  .5;
		z3 =  radius * sin( nextAngle * radians );

		addTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3  );

		//Rectangles
		for( int i = 0; i < stacks; i++ ){
			addTriangle( x2, y2-(i*height), z2, 
						 x2, y2-((i+1)*height), z2,
						 x3, y3-((i+1)*height), z3 );

			addTriangle( x3, y3-((i+1)*height), z3, 
						 x3, y2-((i)*height), z3,
						 x2, y2-((i)*height), z2 );
		}

		//Bottom Circle
		y1 *= -1;
		y2 *= -1;
		y3 *= -1;
		addTriangle(x1, y1, z1, x3, y3, z3, x2, y2, z2  );
	}
}


void Cylinder::addTriangle (double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
	/*triangles[numTriangles][0] = x1;
	triangles[numTriangles][1] = y1;
	triangles[numTriangles][2] = z1;
	
	triangles[numTriangles][3] = x2;
	triangles[numTriangles][4] = y2;
	triangles[numTriangles][5] = z2;
	
	triangles[numTriangles][6] = x3;
	triangles[numTriangles][7] = y3;
	triangles[numTriangles][8] = z3;*/

	_triangles[numTriangles] = Triangle(
		Vector3( x1, y1, z1 ),
		Vector3( x2, y2, z2 ),
		Vector3( x3, y3, z3 ), 
		RayColor( 1.0, 1.0, 1.0 ));
	
	//printf ("Adding triangle: (%f, %f, %f) / (%f, %f, %f) / (%f, %f, %f)\n", x1, y1, z1, x2, y2, z2, x3, y3, z3);
	
	numTriangles++;
}