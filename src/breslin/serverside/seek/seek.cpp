#include "seek.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../client/client.h"
#include "../shape/shape.h"

#include "../../math/vector3D.h"


#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//seek states
#include "states/seekStates.h"

Seek::Seek(Shape* shape) : BaseEntity(BaseEntity::getNextValidID())
{
	mShape = shape;

	mSeekShape = NULL;
	mSeekPoint = NULL;

 	//seek states
	mStateMachine =  new StateMachine<Seek>(this);
	mStateMachine->setCurrentState      (Normal_Seek::Instance());
	mStateMachine->setPreviousState     (Normal_Seek::Instance());
	mStateMachine->setGlobalState       (GlobalSeek::Instance());
}

Seek::~Seek()
{
}
void Seek::update()
{
	mStateMachine->update();
	
	if (mSeekShape)
	{
		updateSeekPoint();
	}
}

bool Seek::handleMessage(const Telegram& msg)
{
        return mStateMachine->handleMessage(msg);
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