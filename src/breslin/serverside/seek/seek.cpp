#include "seek.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../client/client.h"
#include "../../shape/shape.h"

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
	
	if (mSeekShape)
	{
		updateSeekPoint();
	}
}

void Seek::updateSeekPoint()
{
	//update seek point if seek shape
 	if (mSeekShape)
        {
                //set seek point as that is what we will really use...
                mSeekPoint = new Vector3D();
                mSeekPoint->x = mSeekShape->mSceneNode->getPosition().x;             
                mSeekPoint->y = mSeekShape->mSceneNode->getPosition().y;             
                mSeekPoint->z = mSeekShape->mSceneNode->getPosition().z;             
        }
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
		mSeekShape = NULL;
	}
}

void Seek::setSeekShape(Shape* seekShape)
{
	if (seekShape)
	{
		//set shape
		mSeekShape = seekShape;

		updateSeekPoint();
	}
	else
	{
		mSeekShape = NULL;
		mSeekPoint = NULL;
	}
}
