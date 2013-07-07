#ifndef ROTATION_H
#define ROTATION_H

//parent
#include "../ability.h"

//vector3D
#include "../../../math/vector3D.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class RotationStateMachine;
class Shape;

class Rotation : public Ability
{

public:

Rotation(Shape* shape);
~Rotation();

Vector3D* mRotation;
Vector3D* mRotationLast;

Shape* mShape;

float mDegrees;
float mRotationSpeed;

//acceleration
float mRotationDecel;
float mRotationAccel;

//movement
void processTick    ();

RotationStateMachine* mRotationStateMachine;


};

#endif

