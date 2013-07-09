#ifndef COMPUTER_H
#define COMPUTER_H

#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Shape;

class Computer : public BaseEntity 
{

public:

Computer(Shape* shape);
~Computer();

//update
virtual void update();

//handle message
virtual bool  handleMessage(const Telegram& msg);

Shape* mShape;

StateMachine<Computer>* mStateMachine;

int mCounter;
int mThreshold;

};

#endif

