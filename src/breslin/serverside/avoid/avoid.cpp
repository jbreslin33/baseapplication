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

	mAvoidLength = 0.0f;
	mAvoidVelocity = new Vector3D();

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
}

bool Avoid::handleLetter(Letter* letter)
{
        return mStateMachine->handleLetter(letter);
}

void Avoid::addAvoidShape(Shape* avoidShape)
{
	mAvoidVector.push_back(avoidShape);
}

bool Avoid::removeAvoidShape(Shape* avoidShape)
{
	for (int i = 0; i < mAvoidVector.size(); i++)
	{
		if (mAvoidVector.at(i) == avoidShape)
		{
			mAvoidVector.erase(mAvoidVector.begin()+i);
			return true;
		}	
	}
	return false;
}

Shape*  Avoid::findClosestAvoidee()
{
	Shape* closestShapeSoFar = NULL;
	float closestDistanceSoFar = 3000.0f;

	for (int i = 0; i < mAvoidVector.size(); i++)
	{
		Shape* avoidee = mAvoidVector.at(i);

 		Vector3D* newKeyDirection         = new Vector3D();

                Vector3D* currentPosition         = new Vector3D();
                Vector3D* currentAvoideePosition  = new Vector3D();
                Vector3D* differenceVector        = new Vector3D();

                currentPosition->x = mShape->mSceneNode->getPosition().x;
                currentPosition->y = mShape->mSceneNode->getPosition().y;
                currentPosition->z = mShape->mSceneNode->getPosition().z;

                currentAvoideePosition->x = avoidee->mSceneNode->getPosition().x;
                currentAvoideePosition->y = avoidee->mSceneNode->getPosition().y;
                currentAvoideePosition->z = avoidee->mSceneNode->getPosition().z;

		differenceVector->subtract(currentPosition,currentAvoideePosition);

		float length = differenceVector->length();

		if (length < closestDistanceSoFar)
		{
			closestShapeSoFar = avoidee;
			closestDistanceSoFar = length;
		}
	}
	return closestShapeSoFar;
}

