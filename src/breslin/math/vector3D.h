#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{

public:
Vector3D();
~Vector3D();

float length();

float x;
float y;
float z;

bool isZero();
void zero();

void normalise();

void multiply(float num);
void add     (Vector3D* vectorToAddtoThisOne);
void subtract(Vector3D* vectorToAddtoThisOne);
void copyValuesFrom(Vector3D* copyFrom);

};
#endif
