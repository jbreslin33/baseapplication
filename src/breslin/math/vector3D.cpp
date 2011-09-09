#include "vector3D.h"
#include <math.h>

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::~Vector3D()
{
}

double Vector3D::length()
{
	return sqrt(x*x + y*y + z*z);
}

bool Vector3D::isZero()
{
	if (x == 0.0 && y == 0.0 && z == 0.0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Vector3D::zero()
{
	x = 0;
	y = 0;
	z = 0;
}

void Vector3D::normalise()
{
	double len = length();
	if (len == 0)
		return;
	x /= len;
	y /= len;
	z /= len;
}

//multiply this vector by a scalar
Vector3D Vector3D::operator*(float num) const
{
	Vector3D vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;

	vec.x = x * num;
	vec.y = y * num;
	vec.z = z * num;
	return vec;
}

// Given 3D vector 'v', returns its module (i.e. length)
double Vector3D::Vec3_Module(const double * v)
{
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

// Given two 3D vectors, returns the dot product between them
double Vector3D::Vec3_Dot(const double * a, const double * b)
{
    return (a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
}

// Given a pair of 3D vectors, returns the angle between them.
// Angle is expressed in radians, in range [0, PI]
double Vector3D::Vec3_Angle(const double * a, const double * b)
{
    //
    // From dot product definition:
    //
    // a . b = |a| |b| cos(theta)
    //
    //  ==>  cos(theta) = a . b / (|a| |b|)
    //
    //  ==>  theta = acos( a . b / (|a| |b|) )
    //

    return acos( Vec3_Dot(a, b) / (Vec3_Module(a) * Vec3_Module(b)) );
}


