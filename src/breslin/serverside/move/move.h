#ifndef SERVERSIDEMOVE_H
#define SERVERSIDEMOVE_H

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Command;
class MoveStateMachine;
class Shape;

class Move 
{

public:

Move(Shape* shape);
~Move();

//ticks
void processTick    ();

Shape* mShape;

MoveStateMachine* mMoveStateMachine;

//run speed
float mRunSpeed;


//run acceleration
float mRunDecel;
float mRunAccel;

};

#endif

