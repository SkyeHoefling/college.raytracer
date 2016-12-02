#pragma once
class Vector2
{ 
protected:
	double x, y;
public:
	Vector2(void);
	Vector2(double x, double y);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);

	double dot( Vector2 v2 );
	~Vector2(void);
};

