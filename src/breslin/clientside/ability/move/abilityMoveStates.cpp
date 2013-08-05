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
        //abilityMove->mShape->appendToTitle("M:Normal");

        // if distance exceeds threshold && server velocity is zero
        if(abilityMove->mDeltaPosition > abilityMove->mPosInterpLimitHigh && !abilityMove->mShape->mServerCommandCurrent->mVelocity->isZero())
        {
                abilityMove->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
	}                

	Vector3D serverVelocity;
       	serverVelocity.copyValuesFrom(abilityMove->mShape->mServerCommandCurrent->mVelocity);
        serverVelocity.normalise();

        if(abilityMove->mShape->mCommandToRunOnShape->mFrameTime != 0)
        {
        	abilityMove->mShape->mSpeed = abilityMove->calculateSpeed(
                abilityMove->mShape->mServerCommandCurrent->mVelocity,
                abilityMove->mShape->mCommandToRunOnShape->mFrameTime);
        }

       	serverVelocity.multiply(abilityMove->mShape->mSpeed);
	abilityMove->regulate(&serverVelocity);
        abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(&serverVelocity);
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

	//abilityMove->mShape->appendToTitle("M:Catchup");

        //if we are back in sync
    	if(abilityMove->mDeltaPosition <= abilityMove->mPosInterpLimitHigh || abilityMove->mShape->mServerCommandCurrent->mVelocity->isZero())
    	{
                abilityMove->mProcessTickStateMachine->changeState(Normal_ProcessTick_Move::Instance());
    	}
      	
	//this is what we will set mCommandToRunOnShape->mVelocity to
        Vector3D velocity; //vector to future server pos

        //first set velocity to most recent velocity from server.
        velocity.copyValuesFrom(abilityMove->mShape->mServerCommandCurrent->mVelocity);

        //normalise it now we know what direction to head in.
        velocity.normalise();

        //le'ts find out how fast
        //change in position times our interp factor
        float multiplier = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor;
                
        //multiply our normalized velocity by multiplier(change * interpfactor)
        velocity.multiply(multiplier);
                
        //add the latest server position to our velocity
        velocity.add(abilityMove->mShape->mServerCommandCurrent->mPosition);

        //now subtract our current position from our velocity
        velocity.subtract(abilityMove->mShape->getPosition());

        //dist from client pos to future server pos
        float predictDist = pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2);
        predictDist = sqrt(predictDist);

        //server velocity
        if(abilityMove->mShape->mCommandToRunOnShape->mFrameTime != 0)
        {
        	abilityMove->mShape->mSpeed = abilityMove->calculateSpeed(
abilityMove->mShape->mServerCommandCurrent->mVelocity,
               abilityMove->mShape->mCommandToRunOnShape->mFrameTime);
        }

        if(abilityMove->mShape->mSpeed != 0.0)
        {
        	//time needed to get to future server pos
                float time = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor/abilityMove->mShape->mSpeed;

                velocity.normalise();  //?????what the hell why i am normalizing this after all that work above?

                //client vel needed to get to future server pos in time
                float distTime = predictDist/time;
                velocity.multiply(distTime);

                //set velocity to mCommandToRunOnShape->mVelocity which is what interpolateTick uses
		abilityMove->regulate(&velocity);
                abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(&velocity);
	}
        else
        {
               	//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
                abilityMove->mShape->mCommandToRunOnShape->mVelocity->zero();
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
        Vector3D transVector;

        //copy values from mVelocity so we don't make changes to original
        transVector.copyValuesFrom(abilityMove->mShape->mCommandToRunOnShape->mVelocity);
        
	//get the mulitplier
        float multipliedRenderTime = abilityMove->mShape->mApplication->getRenderTime() * 1000;

        //multiply our vector using render values
        transVector.multiply(multipliedRenderTime); 

        //add our velocity to current position
        transVector.add(abilityMove->mShape->getPosition());
        
	//set position
	if (transVector.x < 250.0f && transVector.x > -250.0f && transVector.z < 250.0f && transVector.z > -250.0f)
	{
		abilityMove->mShape->setPosition(transVector);
	}

	if (abilityMove->mShape->mLocal == 1)
	{
		abilityMove->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(transVector.x,transVector.y + 100,transVector.z + 150));

		abilityMove->mShape->mApplication->getCamera()->lookAt(Ogre::Vector3(transVector.x,transVector.y,transVector.z - 30.0f));
	
	}
}
void Normal_InterpolateTick_Move::exit(AbilityMove* abilityMove)
{
}

	//abliityMove->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(0,20,20));
 	// Position it at 500 in Z direction
 	//   mCamera->setPosition(Ogre::Vector3(0,20,20));
    	// Look back along -Z
  	//  mCamera->lookAt(Ogre::Vector3(0,0,0));
