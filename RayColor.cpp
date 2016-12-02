#include "RayColor.h"

RayColor::RayColor(){
	_r = 0.0;
	_g = 0.0;
	_b = 0.0;
	_alpha = 1.0;
}

RayColor::RayColor( float r, float g, float b, float alpha)
{
	setColor( r, g, b, alpha );
}

RayColor::RayColor( float r, float g, float b)
{
	setColor( r, g, b );
}

RayColor::RayColor(Vector3 color, float alpha)
{
	setColor(color.getX(), color.getY(), color.getZ(), alpha);
}
RayColor::RayColor(Vector3 color)
{
	setColor( color.getX(), color.getY(), color.getZ() );
}
RayColor::RayColor(Vector4 color)
{
	setColor( color.getX(), color.getY(), color.getZ(), color.getW() );
}
RayColor::~RayColor(void)
{
}

float RayColor::getR()
{
	return _r;
}
float RayColor::getG()
{
	return _g;
}
float RayColor::getB()
{
	return _b;
}
float RayColor::getAlpha()
{
	return _alpha;
}

Vector4 RayColor::getColor()
{
	return Vector4( _r, _g, _b, _alpha );
}

RayColor RayColor::cross( RayColor rc )
{
	float AbBa = _b * rc.getAlpha();
	float ArBg = _r * rc.getG();
	float AaBr = _alpha * rc.getR();
	float AgBb = _g * rc.getB();

	float newR = (      AgBb      ) - (        AbBa        ) - ( _alpha * rc.getG() );
	float newG = ( _r * rc.getB() ) - (        AbBa        ) - (         AaBr       );
	float newB = (      ArBg      ) - ( _g * rc.getAlpha() ) - (         AaBr       );
	float newA = (      ArBg      ) - (        AgBb        ) - ( _b * rc.getR()     );

	return RayColor( newR, newG, newB, newA );
}

float RayColor::dot( RayColor rc )
{
	return _r * rc.getR() + _g * rc.getG() + _b * rc.getB() + _alpha * rc.getAlpha();
}

RayColor RayColor::getNormalized(){
	// get the length
	double magnitude = sqrt(_r*_r + _g*_g + _b*_b + _alpha*_alpha);
	return RayColor(_r/magnitude,
					_g/magnitude,
					_b/magnitude,
					_alpha/magnitude);

}

RayColor RayColor::operator+(RayColor rightHandSide){
	return RayColor(_r + rightHandSide.getR(),
				    _g + rightHandSide.getG(),
				    _b + rightHandSide.getB(),
				    _alpha + rightHandSide.getAlpha());
}

RayColor RayColor::operator-(RayColor rightHandSide){
	return RayColor(_r - rightHandSide.getR(),
					_g + rightHandSide.getG(),
					_b + rightHandSide.getB(),
					_alpha + rightHandSide.getAlpha());
}

RayColor RayColor::operator*(double multiplyer){
	return RayColor(_r * multiplyer,
					_g * multiplyer,
					_b * multiplyer,
					_alpha * multiplyer);
}

void RayColor::setColor( float r, float g, float b )
{
	_r = r;
	_g = g;
	_b = b;
	_alpha = 1.0;
}
void RayColor::setColor( float r, float g, float b, float alpha )
{
	_r = r;
	_g = g;
	_b = b;
	_alpha = alpha;
}

Vector4 RayColor::asVector4(){
	return Vector4(_r,_g,_b,_alpha);
}
Vector3 RayColor::asVector3(){
	return Vector3(_r,_g,_b);
}
