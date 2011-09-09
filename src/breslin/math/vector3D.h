#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{

public:
Vector3D();
~Vector3D();

double length();

float x;
float y;
float z;

bool isZero();
void zero();

void normalise();

Vector3D operator*(float num) const;

//getDegreesToSomething
double Vec3_Module(const double * v);
double Vec3_Dot(const double * a, const double * b);
double Vec3_Angle(const double * a, const double * b);
};
#endif
