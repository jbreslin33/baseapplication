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


Quaternion* Vector3D::getRotationTo(Vector3D* to)
{
	
	Quaternion* quaternion = new Quaternion();

	Vector3D* fallbackAxis = new Vector3D(0.0f,0.0f,0.0f);

	Vector3D* v0 = new Vector3D();
	Vector3D* v1 = new Vector3D();
	v0->copyValuesFrom(this);
	v1->copyValuesFrom(to);

	v0->normalise();	
	v1->normalise();

	float d = v0->dot(v1);

    // If dot == 1, vectors are the same
    if (d >= 1.0f)
    {
		//LogString("VECTORS ARE THE SAME!!!!!!!!!!!!!!!!");
		Quaternion* quaternionIdentity = new Quaternion(1.0,0.0,0.0,0.0);
		return quaternionIdentity;
    }
			
	if (d < (1e-6f - 1.0f))
	{
		// rotate 180 degrees about the fallback axis
		Vector3 fb;
		fb.x = fallbackAxis->x;
		fb.y = fallbackAxis->y;
		fb.z = fallbackAxis->z;
		//quaternion->FromAngleAxis(Radian(Math::PI), fb);
		
		// rotate 180 degrees about the fallback axis
		quaternion->FromAngleAxis(Radian(Math::PI), fb);
	}
	else
	{
		Real s = Math::Sqrt( (1+d)*2 );
        Real invs = 1 / s;

		Vector3D* c = v0->crossProduct(v1);

   	    quaternion->x = c->x * invs;
       	quaternion->y = c->y * invs;
        quaternion->z = c->z * invs;
        quaternion->w = s * 0.5f;
		quaternion->normalise();
	}
return quaternion;
}


//calculate how far off we are from some vector
float Vector3D::getDegreesToSomething(Vector3D* to)
{
	Quaternion* toSomething = this->getRotationTo(to);
	
    // convert to degrees
    Real degreesToSomething = toSomething->getYaw().valueDegrees();
	return degreesToSomething;
}

Vector3 Vector3D::getVector3()
{
	Vector3 vector3;
	vector3.x = x;
	vector3.y = y;
	vector3.z = z;
	return vector3;
}

void Vector3D::convertFromVector3(Vector3 vector3)
{
	x = vector3.x;
	y = vector3.y;
	z = vector3.z;

}