//header
#include "abilityMoveStates.h"

//state machine
#include "abilityMoveStateMachine.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shapeDynamic.h"

//ability
#include "abilityMove.h"

//utility
#include <math.h>


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
	abilityMove->mShapeDynamic->moveGhostShape();
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
	//abilityMove->mShapeDynamic->appendToTitle("M:Normal");

	// if distance exceeds threshold && server velocity is zero
	if(abilityMove->mDeltaPosition > abilityMove->mPosInterpLimitHigh && !abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity->isZero())
	{
		abilityMove->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
    }
    else //server stopped or we are in sync so just use server vel as is..
    {
		Vector3D* serverDest = new Vector3D();
		serverDest->copyValuesFrom(abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity);
		serverDest->normalise();

        if(abilityMove->mShapeDynamic->mCommandToRunOnShape->mMilliseconds != 0)
        {
			abilityMove->mSpeed = abilityMove->calcuateSpeed(
			abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity,
			abilityMove->mShapeDynamic->mCommandToRunOnShape->mMilliseconds);
        }

		serverDest->multiply(abilityMove->mSpeed);
		abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->copyValuesFrom(serverDest);
	}
}
void Normal_ProcessTick_Move::exit(AbilityMove* abilityMove)
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
	//abilityMove->mShapeDynamic->appendToTitle("M:Catchup");

	//if we are back in sync
    if(abilityMove->mDeltaPosition <= abilityMove->mPosInterpLimitHigh || abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity->isZero())
    {
		abilityMove->mProcessTickStateMachine->changeState(Normal_ProcessTick_Move::Instance());
    }
    else
    {
		//this is what we will set mCommandToRunOnShape->mMoveVelocity to
		Vector3D* newVelocity = new Vector3D(); //vector to future server pos

		//first set newVelocity to most recent velocity from server.
 		newVelocity->copyValuesFrom(abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity);

		//normalise it now we know what direction to head in.
        newVelocity->normalise();

		//le'ts find out how fast
		//change in position times our interp factor
        float multiplier = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor;
		
		//multiply our normalized velocity by multiplier(change * interpfactor)
		newVelocity->multiply(multiplier);
		
		//add the latest server position to our newvelocity
		newVelocity->add(abilityMove->mShapeDynamic->mServerFrame->mPosition);

		//now subtract our current position from our new velocity
		newVelocity->subtract(abilityMove->mShapeDynamic->getPosition());

        //dist from client pos to future server pos
        float predictDist = pow(newVelocity->x, 2) + pow(newVelocity->y, 2) + pow(newVelocity->z, 2);
        predictDist = sqrt(predictDist);

        //server velocity
		if(abilityMove->mShapeDynamic->mCommandToRunOnShape->mMilliseconds != 0)
        {
			abilityMove->mSpeed = abilityMove->calcuateSpeed(
			abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity,
			abilityMove->mShapeDynamic->mCommandToRunOnShape->mMilliseconds);
		   
			abilityMove->mShapeDynamic->mSpeed = abilityMove->mSpeed;
		}

		if(abilityMove->mSpeed != 0.0)
		{
           //time needed to get to future server pos
           float time = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor/abilityMove->mSpeed;

           newVelocity->normalise();  //?????what the hell why i am normalizing this after all that work above?

           //client vel needed to get to future server pos in time
		   float distTime = predictDist/time;
		   newVelocity->multiply(distTime);

		   abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->copyValuesFrom(newVelocity);

		}
		else
		{
			//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
			abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->zero();

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

	//copy values from mMoveVelocity so we don't make changes to original
  	transVector->copyValuesFrom(abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity);

	//get the mulitplier
	float multipliedRenderTime = abilityMove->mShapeDynamic->mGame->getRenderTime() * 1000;

	//multiply our vector using render values
	transVector->multiply(multipliedRenderTime); 

	//add our velocity to current position
	transVector->add(abilityMove->mShapeDynamic->getPosition());

	//set new position
	abilityMove->mShapeDynamic->setPosition(transVector);
}
void Normal_InterpolateTick_Move::exit(AbilityMove* abilityMove)
{
}


