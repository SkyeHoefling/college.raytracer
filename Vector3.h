#pragma once
#include <math.h>
class Vector3
{
public:
        Vector3(void);
        Vector3(double x, double y, double z);
        ~Vector3(void);
        double getX(); 
        double getY();
        double getZ();
        void setX(double i);
        void setY(double i);
        void setZ(double i);
        void addX(double i);
        void addY(double i);
        void addZ(double i);
        Vector3 operator+(Vector3 rhs);
        Vector3 operator-(Vector3 rhs);
        Vector3 operator*(double rhs);
        Vector3 operator*(int rhs);
        Vector3 operator*(Vector3 rhs);
        Vector3 operator/(double rhs);
        Vector3 operator/(int rhs);
        bool operator==(Vector3 rhs);
		bool operator!=(Vector3 rhs);
        Vector3 getVector();
        void normalize();
		Vector3 normalized();
        Vector3 unitFrom(Vector3 v);
        double dot(Vector3 i);
        Vector3 cross(Vector3 i);
        double length();
        double distanceFrom(Vector3 v);
        
protected:
        double x, y, z;
};
