#include "abilityMoveStates.h"
#include "abilityMoveStateMachine.h"

#include "../../tdreamsock/dreamSockLog.h"

#include "../../shape/shapeDynamic.h"

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
	abilityMove->mShapeDynamic->appendToTitle(abilityMove->mShapeDynamic->mIndex);
	
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
	if(abilityMove->mDeltaPosition > abilityMove->mPosInterpLimitHigh && !abilityMove->mShapeDynamic->mServerFrame.mVelocity.isZero())
	{
		abilityMove->mMoveProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
    }
    else //server stopped or we are in sync so just use server vel as is, this is meat of normal state...
    {
		Vector3D serverDest;
       // Ogre::Vector3 myDest      = Ogre::Vector3::ZERO;

		serverDest.x = abilityMove->mShapeDynamic->mServerFrame.mVelocity.x;
	    serverDest.y = abilityMove->mShapeDynamic->mServerFrame.mVelocity.y;
        serverDest.z = abilityMove->mShapeDynamic->mServerFrame.mVelocity.z;
        serverDest.normalise();

       // abilityMove->mShapeDynamic->mRunSpeed = 0.0;

        if(abilityMove->mShapeDynamic->mCommandToRunOnShape.mMilliseconds != 0)
        {
			
			abilityMove->mRunSpeed =
			sqrt(
			pow(abilityMove->mShapeDynamic->mServerFrame.mVelocity.x, 2) + 
            pow(abilityMove->mShapeDynamic->mServerFrame.mVelocity.y, 2) +
			pow(abilityMove->mShapeDynamic->mServerFrame.mVelocity.z, 2)) /
			abilityMove->mShapeDynamic->mCommandToRunOnShape.mMilliseconds;
        }

        serverDest = serverDest * abilityMove->mRunSpeed;

		abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.x = serverDest.x;
        abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.y = serverDest.y;
        abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.z = serverDest.z;
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
    if(abilityMove->mDeltaPosition <= abilityMove->mPosInterpLimitHigh || abilityMove->mShapeDynamic->mServerFrame.mVelocity.isZero())
    {
		abilityMove->mMoveProcessTickStateMachine->changeState(Normal_ProcessTick_Move::Instance());
    }
    else
    {
		Vector3D serverDest; //vector to future server pos
        Vector3D myDest; //vector from clienr pos to future server pos

        serverDest.x = abilityMove->mShapeDynamic->mServerFrame.mVelocity.x;
        serverDest.y = abilityMove->mShapeDynamic->mServerFrame.mVelocity.y;
        serverDest.z = abilityMove->mShapeDynamic->mServerFrame.mVelocity.z;
        serverDest.normalise();

        float multiplier = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor;
        serverDest = serverDest * multiplier;
        serverDest.x = abilityMove->mShapeDynamic->mServerFrame.mOrigin.x + serverDest.x;
        serverDest.y = abilityMove->mShapeDynamic->mServerFrame.mOrigin.y + serverDest.y;
        serverDest.z = abilityMove->mShapeDynamic->mServerFrame.mOrigin.z + serverDest.z;
                //LogString("mOrigin.y %f", abilityMove->mShapeDynamic->mClient->mServerFrame.mOrigin.y);

        myDest.x = serverDest.x - abilityMove->mShapeDynamic->getPosition().x;
        myDest.y = serverDest.y - abilityMove->mShapeDynamic->getPosition().y;
        myDest.z = serverDest.z - abilityMove->mShapeDynamic->getPosition().z;


        //dist from clienr pos to future server pos
        float predictDist = pow(myDest.x, 2) + pow(myDest.y, 2) + pow(myDest.z, 2);
        predictDist = sqrt(predictDist);

        //server velocity
		if(abilityMove->mShapeDynamic->mCommandToRunOnShape.mMilliseconds != 0)
        {
           abilityMove->mRunSpeed = sqrt(pow(abilityMove->mShapeDynamic->mServerFrame.mVelocity.x, 2) + 
           pow(abilityMove->mShapeDynamic->mServerFrame.mVelocity.y, 2) + pow(abilityMove->mShapeDynamic->mServerFrame.mVelocity.z, 2))/abilityMove->mShapeDynamic->mCommandToRunOnShape.mMilliseconds;
		}

		if(abilityMove->mRunSpeed != 0.0)
		{
           //time needed to get to future server pos
           float time = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor/abilityMove->mRunSpeed;

           myDest.normalise();

           //client vel needed to get to future server pos in time
		   float distTime = predictDist/time;
           myDest = myDest * distTime;

           abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.x = myDest.x;
           abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.y = myDest.y;
           abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.z = myDest.z;

		}
		else
		{
			//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
           abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.x = 0.0;
           abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.y = 0.0;
           abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.z = 0.0;

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

    transVector.x = abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.x;
    transVector.y = abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.y;
    transVector.z = abilityMove->mShapeDynamic->mCommandToRunOnShape.mVelocity.z;
        
    abilityMove->mShapeDynamic->translate(transVector * abilityMove->mShapeDynamic->mRenderTime * 1000, 1);

	//does this just prevent you from going below 0 up and down?
    if(abilityMove->mShapeDynamic->getPosition().y < 0.0)
	{	
		abilityMove->mShapeDynamic->setPosition(abilityMove->mShapeDynamic->getPosition().x, 0.0 ,abilityMove->mShapeDynamic->getPosition().z);
	}
}
void Normal_InterpolateTick_Move::exit(AbilityMove* abilityMove)
{
}


