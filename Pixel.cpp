#include "Pixel.h"


Pixel::Pixel(void)
{
	_position = Vector2();
	_color = Vector3();
	_luminance = 0;
}

Pixel::Pixel(Vector2 position){
	_position = position;
	_color = Vector3();
	_luminance = 0;
}

Pixel::Pixel(Vector2 position, Vector3 color){
	_position = position;
	_color = color;
	_luminance = 0;
}

Pixel::Pixel(Vector2 position, Vector3 color, double luminance){
	_position = position;
	_color = color;
	_luminance = luminance;
}

Pixel::~Pixel(void)
{
}

Vector3* Pixel::getColor()			{		return &_color;			}
double Pixel::getColorR()			{		return _color.getX();	}
double Pixel::getColorG()			{		return _color.getY();	}
double Pixel::getColorB()			{		return _color.getZ();	}
double Pixel::getLuminance()		{		return _luminance;		}

void Pixel::setColor(Vector3* color){		_color = *color;		}
void Pixel::setColorR(double r)		{		_color.setX(r);			}
void Pixel::setColorG(double g)		{		_color.setY(g);			}
void Pixel::setColorB(double b)		{		_color.setZ(b);			}
void Pixel::setLuminance(double l)	{		_luminance = l;			}