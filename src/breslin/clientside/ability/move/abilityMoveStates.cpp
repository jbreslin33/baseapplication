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

	Vector3D* serverVelocity = new Vector3D();
       	serverVelocity->copyValuesFrom(abilityMove->mShape->mServerCommandCurrent->mVelocity);
        serverVelocity->normalise();

        if(abilityMove->mShape->mCommandToRunOnShape->mFrameTime != 0)
        {
        	abilityMove->mShape->mSpeed = abilityMove->calculateSpeed(
                abilityMove->mShape->mServerCommandCurrent->mVelocity,
                abilityMove->mShape->mCommandToRunOnShape->mFrameTime);
        }

       	serverVelocity->multiply(abilityMove->mShape->mSpeed);
        abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(serverVelocity);
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
        Vector3D* newVelocity = new Vector3D(); //vector to future server pos

        //first set newVelocity to most recent velocity from server.
        newVelocity->copyValuesFrom(abilityMove->mShape->mServerCommandCurrent->mVelocity);

        //normalise it now we know what direction to head in.
        newVelocity->normalise();

        //le'ts find out how fast
        //change in position times our interp factor
        float multiplier = abilityMove->mDeltaPosition * abilityMove->mPosInterpFactor;
                
        //multiply our normalized velocity by multiplier(change * interpfactor)
        newVelocity->multiply(multiplier);
                
        //add the latest server position to our newvelocity
        newVelocity->add(abilityMove->mShape->mServerCommandCurrent->mPosition);

        //now subtract our current position from our new velocity
        newVelocity->subtract(abilityMove->mShape->getPosition());

        //dist from client pos to future server pos
        float predictDist = pow(newVelocity->x, 2) + pow(newVelocity->y, 2) + pow(newVelocity->z, 2);
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

                newVelocity->normalise();  //?????what the hell why i am normalizing this after all that work above?

                //client vel needed to get to future server pos in time
                float distTime = predictDist/time;
                newVelocity->multiply(distTime);

                //set newVelocity to mCommandToRunOnShape->mVelocity which is what interpolateTick uses
				//abilityMove->regulate(newVelocity);
                abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(newVelocity);
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
        Vector3D* transVector = new Vector3D();

        //copy values from mVelocity so we don't make changes to original
        transVector->copyValuesFrom(abilityMove->mShape->mCommandToRunOnShape->mVelocity);
        
	//get the mulitplier
        float multipliedRenderTime = abilityMove->mShape->mApplication->getRenderTime() * 1000;

        //multiply our vector using render values
        transVector->multiply(multipliedRenderTime); 

        //add our velocity to current position
        transVector->add(abilityMove->mShape->getPosition());
        
	//set new position
	abilityMove->mShape->setPosition(transVector);
	//abliityMove->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(0,20,20));
 	// Position it at 500 in Z direction
 	//   mCamera->setPosition(Ogre::Vector3(0,20,20));
    	// Look back along -Z
  	//  mCamera->lookAt(Ogre::Vector3(0,0,0));

	if (abilityMove->mShape->mLocal == 1)
	{
		abilityMove->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(transVector->x,transVector->y + 320,transVector->z + 20));

		abilityMove->mShape->mApplication->getCamera()->lookAt(Ogre::Vector3(transVector->x,transVector->y,transVector->z));
	
	}
}
void Normal_InterpolateTick_Move::exit(AbilityMove* abilityMove)
{
}

