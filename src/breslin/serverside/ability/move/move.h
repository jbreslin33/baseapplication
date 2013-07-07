#ifndef SERVERSIDEMOVE_H
#define SERVERSIDEMOVE_H

/***********************************************
		METHODS
***********************************************/

//parent
#include "../ability.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/***********************************************
		FORWARD DECLARATIONS
***********************************************/

class MoveStateMachine;
class Shape;
class Vector3D;

class Move : public Ability
{

public:

Move(Shape* shape);
~Move();

/***********************************************
		VARIABLES
***********************************************/

/***********************************************
		METHODS
***********************************************/

//ticks
void processTick    ();

Shape* mShape;

//position
Vector3D* mPositionLast;
Vector3D* mPositionBeforeCollision;

MoveStateMachine* mMoveStateMachine;

//keys
Vector3D* mHeading;

//run speed
float mRunSpeed;

float mSpeedMax;



//run acceleration
float mRunDecel;
float mRunAccel;



};

#endif

