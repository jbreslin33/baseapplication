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
	avoid->calculateCurrentPosition();
	avoid->calculateDot();
	avoid->setEvasiveVelocityToSeek();
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
	avoid->mRandomAvoidDegrees = rand() % 180;

	avoid->mRandomAvoidDegrees = avoid->mRandomAvoidDegrees + 90;
}
void NORMAL_AVOID::execute(Avoid* avoid)
{
/*
	if (avoid->mAvoidee)
	{
		if (avoid->mAvoidVector.size() == 0)	
		{
			avoid->mStateMachine->changeState(NO_AVOID::Instance());	
		} 
		else  
		{
			if (avoid->mShape->mSeek->mSeekPoint || avoid->mShape->mSeek->mDestinationPoint)
			{ 
                		avoid->mStateMachine->changeState(SEEK_AVOID::Instance());
			}
			else
			{
				Vector3D* newVelocity = new Vector3D();
				newVelocity = avoid->mAvoidVelocity->getVectorOffset(avoid->mRandomAvoidDegrees,true);

       				avoid->mShape->mMove->mVelocity->copyValuesFrom(newVelocity);
       				avoid->mShape->mMove->mVelocity->normalise();
			}
		}
	}
// mAvoidDot     = mAvoidVelocity->dot(mShape->mSeek->mSeekVelocity);

*/
	if (avoid->mAvoidee)
	{
	if (avoid->mAvoidVector.size() == 0)	
	{
		avoid->mStateMachine->changeState(NO_AVOID::Instance());	
	} 
	else  
	{
		Vector3D* inverseToAvoidee = new Vector3D();
		inverseToAvoidee = avoid->mAvoidVelocity->getVectorOffset(180.0f,true);
		int d = 0;
		for (d = 1; d < 360; d++)
		{
			bool dotMatch = false;
			Vector3D* newVelocity = inverseToAvoidee->getVectorOffset(d,true);
			for (int i = 0; i < avoid->mClosestAvoidees.size(); i++)
			{
 				Vector3D* currentAvoideePosition = new Vector3D();
				currentAvoideePosition->convertFromVector3(avoid->mClosestAvoidees.at(i)->mSceneNode->getPosition());
				Vector3D* vectorToClosestAvoidee = new Vector3D();
				vectorToClosestAvoidee->subtract(currentAvoideePosition,avoid->mCurrentPosition);	
				float dotToAvoidee = newVelocity->dot(vectorToClosestAvoidee);
				if (dotToAvoidee > .50)
				{
					dotMatch = true;
					i = 2099;	
				}
				
			}
			if (dotMatch == false)
			{
       				avoid->mShape->mMove->mVelocity->copyValuesFrom(newVelocity);
       				avoid->mShape->mMove->mVelocity->normalise();
			}
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

