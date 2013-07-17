#include "avoid.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../client/client.h"
#include "../shape/shape.h"

#include "../../math/vector3D.h"


#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//avoid states
#include "states/avoidStates.h"

Avoid::Avoid(Shape* shape) : BaseEntity(BaseEntity::getNextValidID())
{
	mShape = shape;

	mAvoidShape = NULL;
	mAvoidPoint = NULL;

 	//avoid states
	mStateMachine =  new StateMachine<Avoid>(this);
	mStateMachine->setCurrentState      (Normal_Avoid::Instance());
	mStateMachine->setPreviousState     (Normal_Avoid::Instance());
	mStateMachine->setGlobalState       (GlobalAvoid::Instance());
}

Avoid::~Avoid()
{
}
void Avoid::update()
{
	mStateMachine->update();
	
	if (mAvoidShape)
	{
		updateAvoidPoint();
	}
}

bool Avoid::handleLetter(Letter* letter)
{
        return mStateMachine->handleLetter(letter);
}

void Avoid::updateAvoidPoint()
{
	//update avoid point if avoid shape
 	if (mAvoidShape)
        {
                //set avoid point as that is what we will really use...
                mAvoidPoint = new Vector3D();
                mAvoidPoint->x = mAvoidShape->mSceneNode->getPosition().x;             
                mAvoidPoint->y = mAvoidShape->mSceneNode->getPosition().y;             
                mAvoidPoint->z = mAvoidShape->mSceneNode->getPosition().z;             
        }
}

void Avoid::setAvoidPoint(Vector3D* avoidPoint)
{
	if (avoidPoint)
	{
		mAvoidPoint = new Vector3D();
		mAvoidPoint->copyValuesFrom(avoidPoint); 
	}
	else
	{
		mAvoidPoint = NULL;
		mAvoidShape = NULL;
	}
}

void Avoid::setAvoidShape(Shape* avoidShape)
{
	if (avoidShape)
	{
		//set shape
		mAvoidShape = avoidShape;

		updateAvoidPoint();
	}
	else
	{
		mAvoidShape = NULL;
		mAvoidPoint = NULL;
	}
}
