//header
#include "abilityMoveStates.h"

//state machine
#include "abilityMoveStateMachine.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../../application/applicationBreslin.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//ability
#include "abilityMove.h"

//utility
#include <math.h>

//command
#include "../../command/command.h"


/******************** Global_ProcessTick_Move *****************/

Global_ProcessTick_Move* Global_ProcessTick_Move::Instance()
{
  static Global_ProcessTick_Move instance;
  return &instance;
}
void Global_ProcessTick_Move::enter(AbilityMove* abilityMove)
{

}
void Global_ProcessTick_Move::execute(AbilityMove* abilityMove)
{
	abilityMove->mShape->moveGhostShape();
	abilityMove->calculateDeltaPosition();
 	

}
void Global_ProcessTick_Move::exit(AbilityMove* abilityMove)
{
}


/******************** Normal_ProcessTick_Move *****************/

Normal_ProcessTick_Move* Normal_ProcessTick_Move::Instance()
{
  static Normal_ProcessTick_Move instance;
  return &instance;
}
void Normal_ProcessTick_Move::enter(AbilityMove* abilityMove)
{

}
void Normal_ProcessTick_Move::execute(AbilityMove* abilityMove)
{
        abilityMove->mShape->appendToTitle("M:Normal");

        Vector3D* positionDiff = new Vector3D();
        positionDiff->subtract(abilityMove->mShape->mServerCommandCurrent->mPosition, abilityMove->mShape->mServerCommandLast->mPosition);  
       
	if (positionDiff->isZero())
	{
                abilityMove->mProcessTickStateMachine->changeState(Stop_ProcessTick_Move::Instance());
	}
	else
	{
/*        	if(abilityMove->mDeltaPosition > abilityMove->mPosInterpLimitHigh)
		{
                	abilityMove->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
		}
		else
		{ */
                	Vector3D* positionDiff = new Vector3D();

                	positionDiff->subtract(abilityMove->mShape->mServerCommandCurrent->mPosition, abilityMove->mShape->mServerCommandLast->mPosition);
                
                       	abilityMove->mShape->mSpeed = abilityMove->calcuateSpeed(
                       	positionDiff,
                       	abilityMove->mShape->mServerCommandCurrent->mFrameTime);
               	
		 	positionDiff->normalise();
                	positionDiff->multiply(abilityMove->mShape->mSpeed);
                
               		//keep player from teleporting
                	abilityMove->regulate(positionDiff);
                
                	abilityMove->mShape->mVelocity->copyValuesFrom(positionDiff);
		//}	
	}
}

void Normal_ProcessTick_Move::exit(AbilityMove* abilityMove)
{
}


/******************** STOP_ProcessTick_Move *****************/

Stop_ProcessTick_Move* Stop_ProcessTick_Move::Instance()
{
  static Stop_ProcessTick_Move instance;
  return &instance;
}
void Stop_ProcessTick_Move::enter(AbilityMove* abilityMove)
{
	abilityMove->mShape->mVelocity->zero();	
}
void Stop_ProcessTick_Move::execute(AbilityMove* abilityMove)
{
	abilityMove->mShape->appendToTitle("M:Stop");
		
	Vector3D* positionDiff = new Vector3D();
        positionDiff->subtract(abilityMove->mShape->mServerCommandCurrent->mPosition, abilityMove->mShape->mServerCommandLast->mPosition);  

	if (!positionDiff->isZero())	
	{
		// if distance exceeds threshold && server has a non-zero velocity
	
		if(abilityMove->mDeltaPosition < abilityMove->mPosInterpLimitHigh)
		{
			abilityMove->mProcessTickStateMachine->changeState(Normal_ProcessTick_Move::Instance());
    		}
    	/*	else
		{
			abilityMove->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
		} */	
	}
}

void Stop_ProcessTick_Move::exit(AbilityMove* abilityMove)
{

}

/******************** Catchup_ProcessTick_Move *****************/

Catchup_ProcessTick_Move* Catchup_ProcessTick_Move::Instance()
{
	static Catchup_ProcessTick_Move instance;
	return &instance;
}
void Catchup_ProcessTick_Move::enter(AbilityMove* abilityMove)
{
}
void Catchup_ProcessTick_Move::execute(AbilityMove* abilityMove)
{
	abilityMove->mShape->appendToTitle("M:Catchup");

        Vector3D* positionDiff = new Vector3D();
        positionDiff->subtract(abilityMove->mShape->mServerCommandCurrent->mPosition, abilityMove->mShape->mServerCommandLast->mPosition);  
       
	if (positionDiff->isZero())
	{
                abilityMove->mProcessTickStateMachine->changeState(Stop_ProcessTick_Move::Instance());
	}
	else
	{
        	if(abilityMove->mDeltaPosition <= abilityMove->mPosInterpLimitHigh)
		{
                	abilityMove->mProcessTickStateMachine->changeState(Normal_ProcessTick_Move::Instance());
		}
		else
		{
 	
			//normalise it now we know what direction to head in.
        		positionDiff->normalise();

			//le'ts find out how fast
			//change in position times our interp factor
        		float multiplier = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor;
		
			//multiply our normalized velocity by multiplier(change * interpfactor)
			positionDiff->multiply(multiplier);
		
			//add the latest server position to our newvelocity
			positionDiff->add(abilityMove->mShape->mServerCommandCurrent->mPosition);

			//now subtract our current position from our new velocity
			positionDiff->subtract(abilityMove->mShape->getPosition());

        		//dist from client pos to future server pos
        		float predictDist = pow(positionDiff->x, 2) + pow(positionDiff->y, 2) + pow(positionDiff->z, 2);
        		predictDist = sqrt(predictDist);

			//this is what we will set mCommandToRunOnShape->mVelocity to
			Vector3D* positionDiff2 = new Vector3D(); //vector to future server pos

			//first set newVelocity to most recent velocity from server.
 			positionDiff2->subtract(abilityMove->mShape->mServerCommandCurrent->mPosition, abilityMove->mShape->mServerCommandLast->mPosition);

			abilityMove->mShape->mSpeed = abilityMove->calcuateSpeed(
			positionDiff2,
			abilityMove->mShape->mServerCommandCurrent->mFrameTime);
		   
			abilityMove->mShape->mSpeed = abilityMove->mShape->mSpeed;

			if(abilityMove->mShape->mSpeed != 0.0)
			{
				//time needed to get to future server pos
				float time = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor/abilityMove->mShape->mSpeed;

				positionDiff->normalise();  //?????what the hell why i am normalizing this after all that work above?

				//client vel needed to get to future server pos in time
				float distTime = predictDist/time;
				positionDiff->multiply(distTime);

				//keep player from "teleporting"
				abilityMove->regulate(positionDiff);
				abilityMove->mShape->mVelocity->copyValuesFrom(positionDiff);
				//abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(newVelocity);
			}
		}
	}
}
void Catchup_ProcessTick_Move::exit(AbilityMove* abilityMove)
{
}


/******************** Normal_InterpolateTick_Move *****************/

Normal_InterpolateTick_Move* Normal_InterpolateTick_Move::Instance()
{
  static Normal_InterpolateTick_Move instance;
  return &instance;
}
void Normal_InterpolateTick_Move::enter(AbilityMove* abilityMove)
{

}
void Normal_InterpolateTick_Move::execute(AbilityMove* abilityMove)
{
	//to be used to setPosition
	Vector3D* transVector = new Vector3D();

	//copy values from mVelocity so we don't make changes to original
  	transVector->copyValuesFrom(abilityMove->mShape->mVelocity);

	//get the mulitplier
	float multipliedRenderTime = abilityMove->mShape->mApplicationBreslin->getRenderTime() * 1000;

	//multiply our vector using render values
	transVector->multiply(multipliedRenderTime); 

	//add our velocity to current position
	transVector->add(abilityMove->mShape->getPosition());

	//set new position
	abilityMove->mShape->setPosition(transVector);
}
void Normal_InterpolateTick_Move::exit(AbilityMove* abilityMove)
{
}


