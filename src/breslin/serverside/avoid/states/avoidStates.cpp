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

//client
#include "../../client/robust/clientRobust.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_AVOID* GLOBAL_AVOID::Instance()
{
  static GLOBAL_AVOID instance;
  return &instance;
}
void GLOBAL_AVOID::enter(Avoid* avoid)
{
}
void GLOBAL_AVOID::execute(Avoid* avoid)
{
        if (avoid->mAvoidVector.size() == 0)
        {
		if (avoid->mStateMachine->currentState() != NO_AVOID::Instance())
		{	
                	avoid->mStateMachine->changeState(NO_AVOID::Instance());
		}
        }
	avoid->calculateClosestAvoidees();
 	avoid->mCurrentPosition->convertFromVector3(avoid->mShape->mSceneNode->getPosition());
	
	//the dot between seekVelocity and avoidVelocity
        avoid->mAvoidDotLast = avoid->mAvoidDot;
        avoid->mAvoidDot     = avoid->mAvoidVelocity->dot(avoid->mShape->mSeek->mSeekVelocity);
}
void GLOBAL_AVOID::exit(Avoid* avoid)
{
}
bool GLOBAL_AVOID::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}


/*****************************************
	NORMAL_AVOID
****************************************/
NORMAL_AVOID* NORMAL_AVOID::Instance()
{
  static NORMAL_AVOID instance;
  return &instance;
}

void NORMAL_AVOID::enter(Avoid* avoid)
{
	LogString("NORMAL_AVOID:%d",avoid->mShape->mClient->db_id);
}

void NORMAL_AVOID::execute(Avoid* avoid)
{
	if (avoid->mAvoidee)
	{
		if (avoid->mAvoidVector.size() == 0)	
		{
			avoid->mStateMachine->changeState(NO_AVOID::Instance());	
		} 
		
		if (avoid->mShape->mSeek->mSeekPoint || avoid->mShape->mSeek->mDestinationPoint)
		{ 
                	avoid->mStateMachine->changeState(SEEK_AVOID::Instance());
		}

		//first let's take the inverse velocity of the closest avoidee	
		Vector3D* inverseToAvoidee = new Vector3D();
		inverseToAvoidee = avoid->mAvoidVelocity->getVectorOffset(180.0f,true);

		Vector3D* vectorToClosestAvoidee = new Vector3D();

		//get the size to be used later.....	
		int closestAvoideeSize = avoid->mClosestAvoidees.size();

		//next we will start at 1 degree and then offset from this until we find an open velocity
		int d = 0;
		
		//let's increment by 10 degrees for speed
		for (d = 1; d < 360; d = d + 10)
		{
			bool inTheWay = false;
			//proposedVelocity is 1 degree further than the original inverseToAvoidee then we increase by 1 deg
			Vector3D* proposedVelocity = inverseToAvoidee->getVectorOffset(d,true);
			
			int i = 0;
			while (i < avoid->mClosestAvoidees.size() && inTheWay == false)
			{
				vectorToClosestAvoidee->subtract(avoid->mAvoideePosition,avoid->mCurrentPosition);	
				if (proposedVelocity->dot(vectorToClosestAvoidee) > .50)
				{
					inTheWay = true;
				}
				i++;
			}
			if (inTheWay == false)
			{
       				avoid->mShape->mMove->mVelocity->copyValuesFrom(proposedVelocity);
       				avoid->mShape->mMove->mVelocity->normalise();
			}
			else //no way out right now atleast avoid the closest
			{
       				avoid->mShape->mMove->mVelocity->copyValuesFrom(inverseToAvoidee);
       				avoid->mShape->mMove->mVelocity->normalise();
			}
		}
	}
}

void NORMAL_AVOID::exit(Avoid* avoid)
{
}
bool NORMAL_AVOID::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

/*****************************************
        SEEK_AVOID
****************************************/
SEEK_AVOID* SEEK_AVOID::Instance()
{
  static SEEK_AVOID instance;
  return &instance;
}
void SEEK_AVOID::enter(Avoid* avoid)
{
        LogString("SEEK_AVOID:%d",avoid->mShape->mClient->db_id);
}
void SEEK_AVOID::execute(Avoid* avoid)
{
        if (avoid->mAvoidee)
        {
		if (avoid->mAvoidVector.size() == 0)	
		{
                        avoid->mStateMachine->changeState(NO_AVOID::Instance());
                }
                else //dot lines up, take evasive action..
                {
                        Vector3D* newVelocity = new Vector3D();

                        if (avoid->mShape->mSeek->mSeekPoint || avoid->mShape->mSeek->mDestinationPoint)
                        {
				if (avoid->mAvoidDot >= .50)
				{
                                	newVelocity = avoid->mAvoidVelocity->getVectorOffset(45.0f,true);
                        		avoid->mShape->mMove->mVelocity->copyValuesFrom(newVelocity);
                        		avoid->mShape->mMove->mVelocity->normalise();
				}
                        }
                        else
                        {
                		avoid->mStateMachine->changeState(NORMAL_AVOID::Instance());
                        }
                }
        }
}
void SEEK_AVOID::exit(Avoid* avoid)
{
}
bool SEEK_AVOID::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}


/*****************************************
	NO_AVOID
****************************************/
NO_AVOID* NO_AVOID::Instance()
{
	static NO_AVOID instance;
	return &instance;
}
void NO_AVOID::enter(Avoid* avoid)
{
	LogString("NO_AVOID:%d",avoid->mShape->mClient->db_id);
}
void NO_AVOID::execute(Avoid* avoid)
{
	if (avoid->mAvoidVector.size() > 0)	
	{
		avoid->mStateMachine->changeState(NORMAL_AVOID::Instance());
	}
}
void NO_AVOID::exit(Avoid* avoid)
{
}
bool NO_AVOID::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

