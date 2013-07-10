#ifndef MOVE_H
#define MOVE_H

//parent
#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"

template <class entity_type> class State;

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Shape;
class Vector3D;

class Move : public BaseEntity 
{

public:

Move(Shape* shape);
~Move();

//update
virtual void update();

//handle message
virtual bool  handleMessage(const Telegram& msg);

Shape* mShape;

//position
Vector3D* mPositionLast;
Vector3D* mPositionBeforeCollision;

StateMachine<Move>* mStateMachine;

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
