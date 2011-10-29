#ifndef ROTATION_H
#define ROTATION_H


//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Command;
class RotationStateMachine;
class Shape;

class Rotation
{

public:

Rotation(Shape* shape);
~Rotation();

Shape* mShape;

float mRotationSpeed;

//acceleration
float mRotationDecel;
float mRotationAccel;

//movement
void processTick    ();

RotationStateMachine* mRotationStateMachine;


};

#endif

