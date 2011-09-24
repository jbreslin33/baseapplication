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
		Vector3D* serverDest = new Vector3D(); //vector to future server pos
        Vector3D* myDest     = new Vector3D(); //vector from clienr pos to future server pos

 		serverDest->copyValuesFrom(abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity);
        serverDest->normalise();

        float multiplier = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor;
		serverDest->multiply(multiplier);
        serverDest->x = abilityMove->mShapeDynamic->mServerFrame->mPosition->x + serverDest->x;
        serverDest->y = abilityMove->mShapeDynamic->mServerFrame->mPosition->y + serverDest->y;
        serverDest->z = abilityMove->mShapeDynamic->mServerFrame->mPosition->z + serverDest->z;
		          
        myDest->x = serverDest->x - abilityMove->mShapeDynamic->getPosition().x;
        myDest->y = serverDest->y - abilityMove->mShapeDynamic->getPosition().y;
        myDest->z = serverDest->z - abilityMove->mShapeDynamic->getPosition().z;

        //dist from clienr pos to future server pos
        float predictDist = pow(myDest->x, 2) + pow(myDest->y, 2) + pow(myDest->z, 2);
        predictDist = sqrt(predictDist);

        //server velocity
		if(abilityMove->mShapeDynamic->mCommandToRunOnShape->mMilliseconds != 0)
        {
           abilityMove->mSpeed = sqrt(pow(abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity->x, 2) + 
           pow(abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity->y, 2) + pow(abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity->z, 2))/abilityMove->mShapeDynamic->mCommandToRunOnShape->mMilliseconds;
		   abilityMove->mShapeDynamic->mSpeed = abilityMove->mSpeed;
		}

		if(abilityMove->mSpeed != 0.0)
		{
           //time needed to get to future server pos
           float time = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor/abilityMove->mSpeed;

           myDest->normalise();

           //client vel needed to get to future server pos in time
		   float distTime = predictDist/time;
		   myDest->multiply(distTime);

		   abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->copyValuesFrom(myDest);

		}
		else
		{
			//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
           //abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->x = 0.0;
           //abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->y = 0.0;
           //abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->z = 0.0;
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
	Vector3D transVector;

    transVector.x = abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->x;
    transVector.y = abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->y;
    transVector.z = abilityMove->mShapeDynamic->mCommandToRunOnShape->mMoveVelocity->z;

	transVector = transVector * abilityMove->mShapeDynamic->mGame->getRenderTime() * 1000;
	Vector3D newPosition;
	newPosition.x = transVector.x + abilityMove->mShapeDynamic->getPosition().x;
	newPosition.y = transVector.y + abilityMove->mShapeDynamic->getPosition().y;
	newPosition.z = transVector.z + abilityMove->mShapeDynamic->getPosition().z;
	
	abilityMove->mShapeDynamic->setPosition(newPosition);

	//does this just prevent you from going below 0 up and down?
    if(abilityMove->mShapeDynamic->getPosition().y < 0.0)
	{	
		abilityMove->mShapeDynamic->setPosition(abilityMove->mShapeDynamic->getPosition().x, 0.0 ,abilityMove->mShapeDynamic->getPosition().z);
	}
}
void Normal_InterpolateTick_Move::exit(AbilityMove* abilityMove)
{
}


