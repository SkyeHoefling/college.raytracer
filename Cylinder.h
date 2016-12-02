#pragma once
#include "Shape.h"
#include "Triangle.h"
#include <vector>
#define MAXPOINTS 10000

class Cylinder :
	public Shape
{
private:
	int _slices, _stacks;
	double _radius;
	int _totalTriangles;
	int numTriangles;
	
public:
	//double triangles[MAXPOINTS][9];
	Triangle _triangles[];

	Cylinder( double radius, int slices, int stacks);
	~Cylinder(void);

	void translateCylinder();
	double getRadius( void );
	int getNumTriangles( void );
private:
	void makeCylinder ( double radius, int slices, int stacks );
	void addTriangle(	double x1, double x2, double x3,
						double y1, double y2, double y3, 
						double z1, double z2, double z3 );
};