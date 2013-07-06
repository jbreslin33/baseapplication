#include "seek.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../client/client.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//seek states
#include "seekStateMachine.h"
#include "seekStates.h"

Seek::Seek(Shape* shape) : Ability(shape)
{
	mShape = shape;

	mSeekShape = NULL;
	mSeekPoint = NULL;

 	//seek states
	mSeekStateMachine = new SeekStateMachine(this);    //setup the state machine
	mSeekStateMachine->setCurrentState      (Normal_Seek::Instance());
	mSeekStateMachine->setPreviousState     (Normal_Seek::Instance());
	mSeekStateMachine->setGlobalState       (NULL);
}

Seek::~Seek()
{
}
void Seek::processTick()
{
	mSeekStateMachine->update();
}


