#pragma once
#include "Vector3.h"

class Vector4
{
public:
        Vector4(void);
        Vector4(double xp, double yp, double zp, double wp);
		Vector4(Vector3 vec);
		Vector4(Vector3 vec, double wp);
        ~Vector4(void);
        double getW();double getX();double getY();double getZ();
        void setW(double i);void setX(double i);void setY(double i);void setZ(double i);
        double dot(Vector4 i);
		Vector4 getNormalized();
		void normalize();
        Vector4 operator+(Vector4 rhs);
        Vector4 operator-(Vector4 rhs);
        bool operator==(Vector4 rhs);
		Vector4 operator=(Vector3 rhs);
		Vector4 operator*(double num);
		Vector4 operator*(Vector4 rightHandSide);
protected:
        double _x, _y, _z, _w;
};

