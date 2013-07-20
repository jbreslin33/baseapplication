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
                avoid->mStateMachine->changeState(No_Avoid::Instance());
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
	//LogString("Normal");
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
			avoid->mStateMachine->changeState(X_N_Z_N::Instance());
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
       X_N_Z_N 
****************************************/
X_N_Z_N* X_N_Z_N::Instance()
{
        static X_N_Z_N instance;
        return &instance;
}
void X_N_Z_N::enter(Avoid* avoid)
{
       	avoid->mEvasiveVelocity->x -= .10f;
       	avoid->mEvasiveVelocity->z -= .10f;
        avoid->mEvasiveVelocity->normalise();
        avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
        avoid->mShape->mMove->mVelocity->normalise();
}
void X_N_Z_N::execute(Avoid* avoid)
{
	if (avoid->mAvoidDot > avoid->mAvoidDotLast)
	{
		avoid->mStateMachine->changeState(X_N_Z_P::Instance());
	}
	else
	{
        	avoid->mEvasiveVelocity->x -= .10f;
        	avoid->mEvasiveVelocity->z -= .10f;
        	avoid->mEvasiveVelocity->normalise();
       		avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
        	avoid->mShape->mMove->mVelocity->normalise();
	}
}
void X_N_Z_N::exit(Avoid* avoid)
{
}
bool X_N_Z_N::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

/*****************************************
       X_N_Z_P
****************************************/
X_N_Z_P* X_N_Z_P::Instance()
{
        static X_N_Z_P instance;
        return &instance;
}
void X_N_Z_P::enter(Avoid* avoid)
{
        avoid->mEvasiveVelocity->x -= .10f;
        avoid->mEvasiveVelocity->z += .10f;
        avoid->mEvasiveVelocity->normalise();
        avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
        avoid->mShape->mMove->mVelocity->normalise();
}
void X_N_Z_P::execute(Avoid* avoid)
{
        if (avoid->mAvoidDot > avoid->mAvoidDotLast)
        {
                avoid->mStateMachine->changeState(X_N_Z_P::Instance());
        }
        else
        {
                avoid->mEvasiveVelocity->x -= .10f;
                avoid->mEvasiveVelocity->z += .10f;
                avoid->mEvasiveVelocity->normalise();
                avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
                avoid->mShape->mMove->mVelocity->normalise();
        }
}
void X_N_Z_P::exit(Avoid* avoid)
{
}
bool X_N_Z_P::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}


/*****************************************
       X_P_Z_P
****************************************/
X_P_Z_P* X_P_Z_P::Instance()
{
        static X_P_Z_P instance;
        return &instance;
}
void X_P_Z_P::enter(Avoid* avoid)
{
        avoid->mEvasiveVelocity->x += .10f;
        avoid->mEvasiveVelocity->z += .10f;
        avoid->mEvasiveVelocity->normalise();
        avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
        avoid->mShape->mMove->mVelocity->normalise();
}
void X_P_Z_P::execute(Avoid* avoid)
{
        if (avoid->mAvoidDot > avoid->mAvoidDotLast)
        {
                avoid->mStateMachine->changeState(X_N_Z_P::Instance());
        }
        else
        {
                avoid->mEvasiveVelocity->x += .10f;
                avoid->mEvasiveVelocity->z += .10f;
                avoid->mEvasiveVelocity->normalise();
                avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
                avoid->mShape->mMove->mVelocity->normalise();
        }
}
void X_P_Z_P::exit(Avoid* avoid)
{
}
bool X_P_Z_P::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

/*****************************************
       X_P_Z_N
****************************************/
X_P_Z_N* X_P_Z_N::Instance()
{
        static X_P_Z_N instance;
        return &instance;
}
void X_P_Z_N::enter(Avoid* avoid)
{
        avoid->mEvasiveVelocity->x += .10f;
        avoid->mEvasiveVelocity->z -= .10f;
        avoid->mEvasiveVelocity->normalise();
        avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
        avoid->mShape->mMove->mVelocity->normalise();
}
void X_P_Z_N::execute(Avoid* avoid)
{
        if (avoid->mAvoidDot > avoid->mAvoidDotLast)
        {
                avoid->mStateMachine->changeState(X_N_Z_P::Instance());
        }
        else
        {
                avoid->mEvasiveVelocity->x += .10f;
                avoid->mEvasiveVelocity->z -= .10f;
                avoid->mEvasiveVelocity->normalise();
                avoid->mShape->mMove->mVelocity->copyValuesFrom(avoid->mEvasiveVelocity);
                avoid->mShape->mMove->mVelocity->normalise();
        }
}
void X_P_Z_N::exit(Avoid* avoid)
{
}
bool X_P_Z_N::onLetter(Avoid* avoid, Letter* letter)
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
		if (avoid->mAvoidDot >= .50)
		{
			avoid->mStateMachine->changeState(X_N_Z_N::Instance());
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

