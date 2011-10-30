#include "vector3D.h"


#include <math.h>

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

Vector3D::~Vector3D()
{
}

float Vector3D::length()
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
	float len = length();
	if (len == 0)
		return;
	x /= len;
	y /= len;
	z /= len;
}

//multiply this vector by a scalar
void Vector3D::multiply(float num)
{
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
}

float Vector3D::dot(Vector3D* v2)
{
	float d = x * v2->x + y * v2->y + z * v2->z;
	return d;
}

Vector3D* Vector3D::crossProduct(Vector3D* b)
{
	Vector3D* a = new Vector3D();
	a->copyValuesFrom(this);

	Vector3D* c = new Vector3D();
	c->x = a->y * b->z - a->z * b->x;
	c->y = a->z * b->x - a->x * b->z;
	c->z = a->x * b->y - a->y * b->x;

	return c;
}

Vector3 Vector3D::convertToVector3()
{
	Vector3 vector3;
	vector3.x = x;
	vector3.y = y;
	vector3.z = z;

	return vector3;
}