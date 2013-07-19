//parent
#include "avoidStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//avoid
#include "../avoid.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//vector3D
#include "../../../math/vector3D.h"

//move
#include "../../move/move.h"

//seek
#include "../../seek/seek.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalAvoid* GlobalAvoid::Instance()
{
  static GlobalAvoid instance;
  return &instance;
}
void GlobalAvoid::enter(Avoid* avoid)
{
}
void GlobalAvoid::execute(Avoid* avoid)
{

}
void GlobalAvoid::exit(Avoid* avoid)
{
}
bool GlobalAvoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}


/*****************************************
	Normal_Avoid
****************************************/
Normal_Avoid* Normal_Avoid::Instance()
{
  static Normal_Avoid instance;
  return &instance;
}
void Normal_Avoid::enter(Avoid* avoid)
{
	//LogString("Normal");
}
void Normal_Avoid::execute(Avoid* avoid)
{
	if (avoid->mAvoidVector.size() == 0)	
	{
		avoid->mStateMachine->changeState(No_Avoid::Instance());
	}

	Shape* avoidee = avoid->findClosestAvoidee();

	if (avoidee)
	{
          	//current position
                Vector3D* currentPosition = new Vector3D();
                currentPosition->convertFromVector3(avoid->mShape->mSceneNode->getPosition());

		//avoidee position
                Vector3D* avoideePosition = new Vector3D();
                avoideePosition->convertFromVector3(avoidee->mSceneNode->getPosition());

                //avoid velocity and length(this is actually to hit the avoidee)
                avoid->mAvoidVelocity->subtract(avoideePosition,currentPosition);
                avoid->mAvoidLengthLast = avoid->mAvoidLength;
                avoid->mAvoidLength     = avoid->mAvoidVelocity->length();
                avoid->mAvoidVelocity->normalise();
	
		//the dot between seekVelocity and avoidVelocity
		avoid->mAvoidDotLast = avoid->mAvoidDot;
		avoid->mAvoidDot = avoid->mAvoidVelocity->dot(avoid->mShape->mSeek->mSeekVelocity);

		if (avoid->mAvoidDot < .50) 
		{
			//just seek
		} 
		else //dot lines up, take evasive action..
		{
			//avoid->mShape->mMove->mVelocity->zero();

			//let's turn one of the coordinates to it's inverse
			Vector3D* evasiveVelocity = new Vector3D();	
			evasiveVelocity->copyValuesFrom(avoid->mShape->mSeek->mSeekVelocity);
		
			//let's just start moving x and z until we evade??
			evasiveVelocity->z += .10f; 
			evasiveVelocity->normalise();
	
			/*
			evasiveVelocity->crossProduct(avoid->mShape->mSeek->mSeekVelocity);		
			evasiveVelocity->x = -1 * evasiveVelocity->x;	
			evasiveVelocity->normalise();	
			evasiveVelocity->x = evasiveVelocity->z * -1.0f;	
			evasiveVelocity->z = evasiveVelocity->x;	
			*/		

			avoid->mShape->mMove->mVelocity->copyValuesFrom(evasiveVelocity);
			avoid->mShape->mMove->mVelocity->normalise();

			//avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mShape->mSeek->mSeekVelocity);
		}

	}
}
void Normal_Avoid::exit(Avoid* avoid)
{
}
bool Normal_Avoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

/*****************************************
	No_Avoid
****************************************/
No_Avoid* No_Avoid::Instance()
{
	static No_Avoid instance;
	return &instance;
}
void No_Avoid::enter(Avoid* avoid)
{
	//LogString("No");
}
void No_Avoid::execute(Avoid* avoid)
{
	if (avoid->mAvoidVector.size() > 0)	
	{
		avoid->mStateMachine->changeState(Normal_Avoid::Instance());
	}
}
void No_Avoid::exit(Avoid* avoid)
{
}
bool No_Avoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

