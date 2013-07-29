#include "avoid.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../client/client.h"
#include "../shape/shape.h"
#include "../seek/seek.h"

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
	mAvoidee = NULL;

	mVectorToClosestAvoideeLength = 0.0f;
	mVectorToClosestAvoideeLengthLast = 0.0f;

	mAvoidDot = 0.0f;
	mAvoidDotLast = 0.0f;

	mVectorToClosestAvoidee = new Vector3D();
	mAvoidVelocity = new Vector3D();
	mAvoidVelocityLast = new Vector3D();

	mCurrentPosition = new Vector3D();
	mAvoideePosition = new Vector3D();

	mPanicDistance = 20.0f;

	mRandomAvoidDegrees = 0.0f;

	//evade
	mEvadeWithXPositive = false;
	mEvadeWithZPositive = false;
	mEvadeWithXNegative = false;
	mEvadeWithZNegative = false;

 	//avoid states
	mStateMachine =  new StateMachine<Avoid>(this);
	mStateMachine->setCurrentState      (NORMAL_AVOID::Instance());
	mStateMachine->setPreviousState     (NORMAL_AVOID::Instance());
	mStateMachine->setGlobalState       (GLOBAL_AVOID::Instance());

	//get a random old mAvoidVelocity
	float randomX = rand() % 500; 
	float randomZ = rand() % 500; 
	randomX = randomX - 250;
	randomZ = randomZ - 250;

        Vector3D* randomVector3D = new Vector3D(randomX,0,randomZ);
        int randomDegree = rand() % 360;

        mAvoidVelocity = randomVector3D->getVectorOffset(randomDegree,true);
        mAvoidVelocityLast->copyValuesFrom(mAvoidVelocity);
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

void  Avoid::calculateClosestAvoidees()
{
	mClosestAvoidees.clear();	

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

		if (length < mPanicDistance)
		{
			mClosestAvoidees.push_back(avoidee);	
		}

		if (length < closestDistanceSoFar)
		{
			closestShapeSoFar = avoidee;
			closestDistanceSoFar = length;
		}
	}
	mAvoidee = closestShapeSoFar;
	if (mAvoidee)
	{
        	mAvoideePosition->convertFromVector3(mAvoidee->mSceneNode->getPosition());

                //mVectorToClosestAvoidee and length(this is actually to hit the avoidee)
                mVectorToClosestAvoidee->subtract(mAvoideePosition,mCurrentPosition);
                mVectorToClosestAvoideeLengthLast  = mVectorToClosestAvoideeLength;
                mVectorToClosestAvoideeLength     = mVectorToClosestAvoidee->length();
                mVectorToClosestAvoidee->normalise();
	}
}

