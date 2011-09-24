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

//multiply this vector by a scalar
void Vector3D::multiply(float num)
{
	/*
	Vector3D* vec = new Vector3D();
	vec->x = x * num;
	vec->y = y * num;
	vec->z = z * num;

	return vec;
	*/
	x = x * num;
	y = y * num;
	z = z * num;
}

//add another vector to this one
void Vector3D::add(Vector3D* vectorToAddtoThisOne)
{
	x = x + vectorToAddtoThisOne->x;
	y = y + vectorToAddtoThisOne->y;
	z = z + vectorToAddtoThisOne->z;
}

//subtract another vector from this one
void Vector3D::subtract(Vector3D* vectorToAddtoThisOne)
{
	x = x - vectorToAddtoThisOne->x;
	y = y - vectorToAddtoThisOne->y;
	z = z - vectorToAddtoThisOne->z;
}

//copy values
void Vector3D::copyValuesFrom(Vector3D* copyFrom)
{
	x = copyFrom->x;
	y = copyFrom->y;
	z = copyFrom->z;
	//return copyTo;
}

