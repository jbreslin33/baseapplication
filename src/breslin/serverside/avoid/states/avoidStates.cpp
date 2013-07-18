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

/*
    		Vector3D* currentPosition = new Vector3D();

                currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());

                seek->mSeekVelocity->subtract(seek->mSeekPoint,currentPosition);
                seek->mSeekLength = seek->mSeekVelocity->length();

                seek->mShape->mMove->mVelocity->copyValuesFrom(seek->mSeekVelocity);

                seek->mShape->mMove->mVelocity->normalise();
*/
/*

          	//current position
                Vector3D* currentPosition = new Vector3D();
                currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());

                //seek velocity and length
                seek->mSeekVelocity->subtract(seek->mSeekPoint,currentPosition);
                seek->mSeekLength = seek->mSeekVelocity->length();
                seek->mSeekVelocity->normalise();

                //set to shape velocity
                seek->mShape->mMove->mVelocity->copyValuesFrom(seek->mSeekVelocity);

*/

	if (avoidee)
	{
          	//current position
                Vector3D* currentPosition = new Vector3D();
                currentPosition->convertFromVector3(avoid->mShape->mSceneNode->getPosition());

		//avoidee position
                Vector3D* avoideePosition = new Vector3D();
                avoideePosition->convertFromVector3(avoidee->mSceneNode->getPosition());

                //avoid velocity and length
                avoid->mAvoidVelocity->subtract(avoideePosition,currentPosition);
                avoid->mAvoidLength = avoid->mAvoidVelocity->length();
                avoid->mAvoidVelocity->normalise();

		float d = avoid->mAvoidVelocity->dot(avoid->mShape->mSeek->mSeekVelocity);
		LogString("dot:%f",d);

	}
/*
	if (avoidee)
	{

			

		//get current proposed velocity from seek and others basically...
		Vector3D* currentProposedVelocity = new Vector3D();
		currentProposedVelocity->copyValuesFrom(avoid->mShape->mMove->mVelocity);		
		//get current position of avoidee
		Vector3D* avoideePosition = new Vector3D();	
		avoideePosition->convertFromVector3(avoidee->mSceneNode->getPosition());

		//let's get a direction vector to the shape to be avoided
 		Vector3D* velocityToAvoidAvoidee     = new Vector3D();
                Vector3D* currentPosition = new Vector3D();
                currentPosition->convertFromVector3(avoid->mShape->mSceneNode->getPosition());
                velocityToAvoidAvoidee->subtract(currentPosition,avoideePosition);
		velocityToAvoidAvoidee->normalise();

		//betweeen	
//		avoid->mShape->mMove->mVelocity = velocityToAvoidAvoidee;


		Vector3D* compromiseVelocity = new Vector3D();
		compromiseVelocity->add(currentProposedVelocity,velocityToAvoidAvoidee); 
		compromiseVelocity->multiply(.5);
		compromiseVelocity->normalise();
		avoid->mShape->mMove->mVelocity = compromiseVelocity;
	}
*/

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

