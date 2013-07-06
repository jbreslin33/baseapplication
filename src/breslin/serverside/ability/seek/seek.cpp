#include "seek.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../client/client.h"

#include "../../../math/vector3D.h"

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

void Seek::setSeekPoint(Vector3D* seekPoint)
{
	if (seekPoint)
	{
		mSeekPoint = new Vector3D();
		mSeekPoint->copyValuesFrom(seekPoint); 
	}
	else
	{
		mSeekPoint = NULL;
	}
}

void Seek::setSeekShape(Shape* seekShape)
{
	if (seekShape)
	{
		mSeekShape = seekShape;
	}
	else
	{
		mSeekShape = NULL;
	}

}
