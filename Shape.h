#pragma once
#include "Entity.h"
#include "RayColor.h"

#define PI 3.14159265
#define ToRad PI/180
#define SHAPE_PLANE 0
#define SHAPE_SPHERE 1
#define SHAPE_OTHER 2
typedef int ShapeType;

class Shape : public Entity
{
protected:
	double _boundingRadius;
	Vector3 _rotation;
	RayColor _color;
	double _reflection;
	double _transparent;
	double clampDouble(double value, double low, double high);
	RayColor _ambientColor;
	RayColor _specularColor;
	RayColor _diffuseColor;
	int _exponentColor;
	ShapeType _type;
	void init( void );
public:
	Shape(void);
	_declspec(deprecated("**(deprecated)Color has been broken up into multiple colors, this code was originally for ambient only**")) Shape(Vector3 position, double radius, RayColor color);
	_declspec(deprecated("**(deprecated)This is used for phong shading WHICH IS NOT RAY TRACING**"))Shape(Vector3 position, double radius, RayColor ambient, RayColor specular, RayColor diffuse, int exponent);
	Shape(Vector3 position, double radius, RayColor color, double reflection, double transparent);
	~Shape(void);

	double getBoundingRadius();
	Vector3 getRotation();
	void applyRotation(Vector3 rotation);

	RayColor getColor();
	double getReflection();
	double getTransparent();
	void setAmbientColor( RayColor new_color );
	RayColor getAmbientColor();
	RayColor getSpecularColor();
	RayColor getDiffuseColor();
	int getExponentColor();
	ShapeType getType();

	
};

