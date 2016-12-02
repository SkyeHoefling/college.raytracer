#include "Shape.h"


Shape::Shape(void)
{
	init();
}

Shape::Shape(Vector3 position, double radius, RayColor color) : Entity(position){
	init();
	_boundingRadius = radius;
	_color = color;
	_ambientColor = _color;
	_specularColor = RayColor(.8f,.6f,.9f);
	_diffuseColor = RayColor(color);
	_exponentColor = 20;
}

Shape::Shape( Vector3 position, double radius, RayColor color, RayColor ambient, RayColor specular, RayColor diffuse, int exponent, double reflection, double transparent ):Entity(position)
{
	init();
	_boundingRadius = radius;
	_color = color;
	_ambientColor = ambient;
	_specularColor = specular;
	_diffuseColor = diffuse;
	_exponentColor = exponent;
	_reflection = clampDouble(reflection, 0, 1);
	_transparent = clampDouble(transparent, 0, 1);
}

Shape::~Shape(void)
{
}

void Shape::init( void )
{
	_boundingRadius = 0;
	_rotation = Vector3();
	_color = RayColor( 0, 0, 0 );
	_ambientColor = RayColor( 0, 0, 0 );
	_specularColor = RayColor( 0, 0, 0 );
	_diffuseColor = RayColor( 0, 0, 0 );
	_type = SHAPE_OTHER;
}

// accessors
double Shape::getBoundingRadius()	{	return _boundingRadius;		}
Vector3 Shape::getRotation(){	return _rotation;	}

// functions
void Shape::applyRotation(Vector3 rotation){
	_rotation = _rotation + rotation;
}

RayColor Shape::getColor(){
	return _color;
}

RayColor Shape::getAmbientColor()
{
	return _ambientColor;
}
void Shape::setAmbientColor( RayColor new_color )
{
	_ambientColor = new_color;
}
RayColor Shape::getSpecularColor()
{
	return _specularColor;
}
RayColor Shape::getDiffuseColor()
{
	return _diffuseColor;
}
int Shape::getExponentColor()
{
	return _exponentColor;
}
ShapeType Shape::getType()
{
	return _type;
}
double Shape::getReflection(){
	return _reflection;
}
double Shape::getTransparent(){
	return _transparent;
}
double Shape::clampDouble(double value, double low, double high){
	if(value > high) value = high;
	else if(value < low) value = low;
	return value;
}
double Shape::getIndexOfRefraction()	{	return _indexOfRefraction;	}
void Shape::setIndexOfRefraction(double i)	{	_indexOfRefraction = i;	}