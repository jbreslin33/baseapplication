#include "ai.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../client/client.h"

#define MAX_RUN_SPEED 1.66           // character running speed in units per second

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//ai states
#include "aiStateMachine.h"
#include "aiStates.h"

AI::AI(Shape* shape) : Ability(shape)
{
	mShape = shape;

 	//ai states
	mAIStateMachine = new AIStateMachine(this);    //setup the state machine
	mAIStateMachine->setCurrentState      (Random_AI::Instance());
	mAIStateMachine->setPreviousState     (Random_AI::Instance());
	mAIStateMachine->setGlobalState       (NULL);
}

AI::~AI()
{
}
void AI::processTick()
{
	mAIStateMachine->update();
}


