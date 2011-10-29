#ifndef ROTATION_H
#define ROTATION_H

//parent
#include "../ability.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Command;
class RotationStateMachine;
class Shape;

class Rotation : public Ability
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

