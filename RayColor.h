#pragma once
#include "Vector3.h"
#include "Vector4.h"
/**
 * Future implimentation of this class will add and sum 
 * multiple colors together to get the average color
 */
class RayColor
{
private:
	float _r, _g, _b;
	float _alpha;
public:
	RayColor();
	RayColor( float r, float g, float b);
	RayColor( float r, float g, float b, float alpha);
	RayColor( Vector3 color, float alpha);
	RayColor( Vector3 color );
	RayColor( Vector4 color );
	~RayColor(void);

	float getR();
	float getG();
	float getB();
	float getAlpha();

	Vector4 getColor();

	RayColor cross( RayColor rc );
	float dot( RayColor rc );
	RayColor getNormalized();

    RayColor operator+(RayColor rightHandSide);
	RayColor operator-(RayColor rightHandSide);
	RayColor operator*(double multiplyer);

	void setColor( float r, float g, float b );
	void setColor( float r, float g, float b, float alpha );

	Vector4 asVector4();
	Vector3 asVector3();
};

