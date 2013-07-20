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
		else //dot lines up, take evasive action.. by changing to X_N_Z_N 
		{
			//get the sine and cosine of 90degrees
			double cs = cos( 90.0f * 3.14f / 180.0f);	
			double sn = sin( 90.0f * 3.14f / 180.0f);	
		
			Vector3D* newVelocity = new Vector3D();

			newVelocity->x = avoid->mAvoidVelocity->x * cs - avoid->mAvoidVelocity->z * sn;	
			newVelocity->z = avoid->mAvoidVelocity->x * sn + avoid->mAvoidVelocity->z * cs;	

       			avoid->mShape->mMove->mVelocity->copyValuesFrom(newVelocity);
       			avoid->mShape->mMove->mVelocity->normalise();
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

