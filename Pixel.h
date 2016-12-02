#pragma once
#include "Vector2.h"
#include "Vector3.h"
#define lmax 1000

class Pixel
{
private:
	Vector2 _position;
	Vector3 _color;
	double _luminance;
public:
	static const int maxLuminance = lmax;

	Pixel(void);
	Pixel(Vector2 position);
	Pixel(Vector2 position, Vector3 color);
	Pixel(Vector2 position, Vector3 color, double luminance);
	~Pixel(void);

	Vector3* getColor();
	void setColor(Vector3* color);
	double getColorR();
	double getColorG();
	double getColorB();
	void setColorR(double r);
	void setColorG(double g);
	void setColorB(double b);

	void setLuminance(double l);
	double getLuminance();
};

