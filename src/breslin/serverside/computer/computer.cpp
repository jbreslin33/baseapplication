#include "computer.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../client/client.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//computer states
#include "states/computerStates.h"

Computer::Computer(Shape* shape) : BaseEntity(BaseEntity::getNextValidID())
{
	mShape = shape;

 	//computer states
   	mStateMachine = new StateMachine<Computer>(this);
	mStateMachine->setCurrentState      (Random_Computer::Instance());
	mStateMachine->setPreviousState     (Random_Computer::Instance());
	mStateMachine->setGlobalState       (GlobalComputer::Instance());

	mCounter   = 0;
        mThreshold = 1000;
}

Computer::~Computer()
{
}

void Computer::update()
{
	mStateMachine->update();
}

bool Computer::handleMessage(const Telegram& msg)
{
        return mStateMachine->handleMessage(msg);
}


