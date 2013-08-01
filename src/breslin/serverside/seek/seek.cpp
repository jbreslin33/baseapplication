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
	mDestinationShape = NULL;

	mSeekPoint = NULL;
	mDestinationPoint = NULL;

	mSeekVelocity = new Vector3D();
	mDestinationVelocity = new Vector3D();

	mSeekLength = 0.0f;
	mDestinationLength = 0.0f;

 	//seek states
	mStateMachine =  new StateMachine<Seek>(this);
	mStateMachine->setCurrentState      (NO_SEEK::Instance());
	mStateMachine->setPreviousState     (NO_SEEK::Instance());
	mStateMachine->setGlobalState       (GLOBAL_SEEK::Instance());
}

Seek::~Seek()
{
	LogString("Seek::~Seek");
	delete mSeekVelocity;
	delete mDestinationVelocity;
}
void Seek::update()
{
	mStateMachine->update();
	
	if (mSeekShape)
	{
		updateSeekPoint();
	}
	if (mDestinationShape)
	{
		updateDestinationPoint();
	}
}

bool Seek::handleLetter(Letter* letter)
{
        return mStateMachine->handleLetter(letter);
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

void Seek::updateDestinationPoint()
{
	//update destination point if seek shape
 	if (mDestinationShape)
        {
                //set destination point as that is what we will really use...
                mDestinationPoint = new Vector3D();
                mDestinationPoint->x = mDestinationShape->mSceneNode->getPosition().x;             
                mDestinationPoint->y = mDestinationShape->mSceneNode->getPosition().y;             
                mDestinationPoint->z = mDestinationShape->mSceneNode->getPosition().z;             
        }
}

void Seek::setSeekPoint(Vector3D* seekPoint)
{
	if (seekPoint)
	{
		//make destination vars null
		mDestinationShape = NULL;		
		mDestinationPoint = NULL;		
	
		//set seek vars
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
		//make destination vars null
		mDestinationShape = NULL;		
		mDestinationPoint = NULL;		

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

void Seek::setDestinationPoint(Vector3D* destinationPoint)
{
        if (destinationPoint)
        {
                //make seek vars null
                mSeekShape = NULL;
                mSeekPoint = NULL;

                //set destination vars
                mDestinationPoint = new Vector3D();
                mDestinationPoint->copyValuesFrom(destinationPoint);
        }
        else
        {
                mDestinationPoint = NULL;
                mDestinationShape = NULL;
        }
}

void Seek::setDestinationShape(Shape* destinationShape)
{
        if (destinationShape)
        {
                //make seek vars null
                mSeekShape = NULL;
                mSeekPoint = NULL;

                //set shape
                mDestinationShape = destinationShape;

                updateDestinationPoint();
        }
        else
        {
                mDestinationShape = NULL;
                mDestinationPoint = NULL;
        }
}


