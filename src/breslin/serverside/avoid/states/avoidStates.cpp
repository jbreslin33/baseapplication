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
        if (avoid->mAvoidVector.size() == 0)
        {
		if (avoid->mStateMachine->currentState() != No_Avoid::Instance())
		{	
                	avoid->mStateMachine->changeState(No_Avoid::Instance());
		}
        }
	avoid->calculateClosestAvoidee();
	avoid->calculateCurrentPosition();
	avoid->calculateDot();
	avoid->setEvasiveVelocityToSeek();
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
	LogString("Normal_Avoid");
}
void Normal_Avoid::execute(Avoid* avoid)
{
	if (avoid->mAvoidee)
	{
		if (avoid->mAvoidDot < .50) 
		{
			//just seek
			avoid->mStateMachine->changeState(No_Avoid::Instance());	
		} 
		else //dot lines up, take evasive action.. 
		{
			Vector3D* newVelocity = new Vector3D();

			if (avoid->mShape->mSeek->mSeekPoint || avoid->mShape->mSeek->mSeekPoint)
			{ 
                		avoid->mStateMachine->changeState(Seek_Avoid::Instance());
			}
			else
			{
				newVelocity = avoid->mAvoidVelocity->getVectorOffset(90.0f,true);
			}

       			avoid->mShape->mMove->mVelocity->copyValuesFrom(newVelocity);
       			avoid->mShape->mMove->mVelocity->normalise();
			delete newVelocity;
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
        Seek_Avoid
****************************************/
Seek_Avoid* Seek_Avoid::Instance()
{
  static Seek_Avoid instance;
  return &instance;
}
void Seek_Avoid::enter(Avoid* avoid)
{
        LogString("Seek_Avoid");
}
void Seek_Avoid::execute(Avoid* avoid)
{
        if (avoid->mAvoidee)
        {
                if (avoid->mAvoidDot < .50)
                {
                        //just seek
                        avoid->mStateMachine->changeState(No_Avoid::Instance());
                }
                else //dot lines up, take evasive action..
                {
                        Vector3D* newVelocity = new Vector3D();

                        if (avoid->mShape->mSeek->mSeekPoint || avoid->mShape->mSeek->mSeekPoint)
                        {
                                newVelocity = avoid->mAvoidVelocity->getVectorOffset(45.0f,true);
                        }
                        else
                        {
                		avoid->mStateMachine->changeState(Normal_Avoid::Instance());
                        }

                        avoid->mShape->mMove->mVelocity->copyValuesFrom(newVelocity);
                        avoid->mShape->mMove->mVelocity->normalise();
			delete newVelocity;
                }
        }
}
void Seek_Avoid::exit(Avoid* avoid)
{
}
bool Seek_Avoid::onLetter(Avoid* avoid, Letter* letter)
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
	LogString("No_Avoid");
}
void No_Avoid::execute(Avoid* avoid)
{
	if (avoid->mAvoidVector.size() > 0)	
	{
		if (avoid->mAvoidDot >= .50)
		{
			avoid->mStateMachine->changeState(Normal_Avoid::Instance());
		}
	}
}
void No_Avoid::exit(Avoid* avoid)
{
}
bool No_Avoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

