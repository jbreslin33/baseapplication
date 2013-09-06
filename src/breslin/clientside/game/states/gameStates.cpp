//header
#include "gameStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../../application/applicationBreslin.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//ability
#include "../game.h"

//utility
#include <math.h>

//command
#include "../../command/command.h"


/******************** GLOBAL_GAME *****************/

GLOBAL_GAME* GLOBAL_GAME::Instance()
{
  static GLOBAL_GAME instance;
  return &instance;
}
void GLOBAL_GAME::enter(Game* game)
{

}
void GLOBAL_GAME::execute(Game* game)
{
}
void GLOBAL_GAME::exit(Game* game)
{
}


/******************** PLAY_GAME *****************/

PLAY_GAME* PLAY_GAME::Instance()
{
  static PLAY_GAME instance;
  return &instance;
}
void PLAY_GAME::enter(Game* game)
{
}
void PLAY_GAME::execute(Game* game)
{
    	//process input
        game->mKeyCurrent = 0;

        //UP
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_W))
        {
                game->mApplication->mKeyArray[119] = true;
                game->mKeyCurrent |= game->mKeyUp;
        }
        else
        {
                game->mApplication->mKeyArray[119] = false;
        }

        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_UP))
        {
                game->mApplication->mKeyArray[119] = true;
                game->mKeyCurrent |= game->mKeyUp;
        }
        else
        {
                game->mApplication->mKeyArray[119] = false;
        }
        //DOWN
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_S))
        {
                game->mApplication->mKeyArray[115] = true;
                game->mKeyCurrent |= game->mKeyDown;
        }
        else
        {
                game->mApplication->mKeyArray[115] = false;
        }
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_DOWN))
        {
                game->mApplication->mKeyArray[115] = true;
                game->mKeyCurrent |= game->mKeyDown;
        }
        else
        {
                game->mApplication->mKeyArray[115] = false;
        }

	//LEFT
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_A))
        {
                game->mApplication->mKeyArray[97] = true;
                game->mKeyCurrent |= game->mKeyLeft;
        }
        else
        {
                game->mApplication->mKeyArray[97] = false;
        }
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_LEFT))
        {
                game->mApplication->mKeyArray[97] = true;
                game->mKeyCurrent |= game->mKeyLeft;
        }
        else
        {
                game->mApplication->mKeyArray[97] = false;
        }

        //RIGHT
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_D))
        {
                game->mApplication->mKeyArray[100] = true;
                game->mKeyCurrent |= game->mKeyRight;
        }
        else
        {
                game->mApplication->mKeyArray[100] = false;
        }
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_RIGHT))
        {
                game->mApplication->mKeyArray[100] = true;
                game->mKeyCurrent |= game->mKeyRight;
        }
        else
        {
                game->mApplication->mKeyArray[100] = false;
        }

	//COUNTERCLOCKWISE
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_Z))
        {
                game->mApplication->mKeyArray[122] = true;
                game->mKeyCurrent |= game->mKeyCounterClockwise;
        }
        else
        {
                game->mApplication->mKeyArray[122] = false;
        }

        //CLOCKWISE
        if (game->mApplication->getKeyboard()->isKeyDown(OIS::KC_X))
        {
                game->mApplication->mKeyArray[120] = true;
                game->mKeyCurrent |= game->mKeyClockwise;
        }
        else
        {
                game->mApplication->mKeyArray[120] = false;
        }

        //network outgoing
        game->sendByteBuffer();


}
void PLAY_GAME::exit(Game* game)
{
}

/******************** CATCHUP_PROCESSTICK_MOVE *****************/

CATCHUP_PROCESSTICK_MOVE* CATCHUP_PROCESSTICK_MOVE::Instance()
{
        static CATCHUP_PROCESSTICK_MOVE instance;
        return &instance;
}
void CATCHUP_PROCESSTICK_MOVE::enter(Game* game)
{
}
void CATCHUP_PROCESSTICK_MOVE::execute(Game* game)
{

	//game->mShape->appendToTitle("M:Catchup");

        //if we are back in sync
    	if(game->mDeltaPosition <= game->mPosInterpLimitHigh || game->mShape->mServerCommandCurrent->mVelocity->isZero())
    	{
                game->mProcessTickStateMachine->changeState(PLAY_GAME::Instance());
    	}
      	
	//this is what we will set mCommandToRunOnShape->mVelocity to
        Vector3D velocity; //vector to future server pos

        //first set velocity to most recent velocity from server.
        velocity.copyValuesFrom(game->mShape->mServerCommandCurrent->mVelocity);

        //normalise it now we know what direction to head in.
        velocity.normalise();

        //le'ts find out how fast
        //change in position times our interp factor
        float multiplier = game->mDeltaPosition * game->mPosInterpFactor;
                
        //multiply our normalized velocity by multiplier(change * interpfactor)
        velocity.multiply(multiplier);
                
        //add the latest server position to our velocity
        velocity.add(game->mShape->mServerCommandCurrent->mPosition);

        //now subtract our current position from our velocity
        velocity.subtract(game->mShape->getPosition());

        //dist from client pos to future server pos
        float predictDist = pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2);
        predictDist = sqrt(predictDist);

        //server velocity
        if(game->mShape->mCommandToRunOnShape->mFrameTime != 0)
        {
        	game->mShape->mSpeed = game->calculateSpeed(
game->mShape->mServerCommandCurrent->mVelocity,
               game->mShape->mCommandToRunOnShape->mFrameTime);
        }

        if(game->mShape->mSpeed != 0.0)
        {
        	//time needed to get to future server pos
                float time = game->mDeltaPosition * game->mPosInterpFactor/game->mShape->mSpeed;

                velocity.normalise();  //?????what the hell why i am normalizing this after all that work above?

                //client vel needed to get to future server pos in time
                float distTime = predictDist/time;
                velocity.multiply(distTime);

                //set velocity to mCommandToRunOnShape->mVelocity which is what interpolateTick uses
		game->regulate(&velocity);
                game->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(&velocity);
	}
        else
        {
               	//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
                game->mShape->mCommandToRunOnShape->mVelocity->zero();
        }
}
void CATCHUP_PROCESSTICK_MOVE::exit(Game* game)
{
}


/******************** NORMAL_INTERPOLATETICK_MOVE *****************/

NORMAL_INTERPOLATETICK_MOVE* NORMAL_INTERPOLATETICK_MOVE::Instance()
{
  static NORMAL_INTERPOLATETICK_MOVE instance;
  return &instance;
}
void NORMAL_INTERPOLATETICK_MOVE::enter(Game* game)
{

}
void NORMAL_INTERPOLATETICK_MOVE::execute(Game* game)
{
        //to be used to setPosition
        Vector3D transVector;

        //copy values from mVelocity so we don't make changes to original
        transVector.copyValuesFrom(game->mShape->mCommandToRunOnShape->mVelocity);
        
	//get the mulitplier
        float multipliedRenderTime = game->mShape->mApplication->getRenderTime() * 1000;

        //multiply our vector using render values
        transVector.multiply(multipliedRenderTime); 

        //add our velocity to current position
        transVector.add(game->mShape->getPosition());
        
	//set position
	if (transVector.x < 250.0f && transVector.x > -250.0f && transVector.z < 250.0f && transVector.z > -250.0f)
	{
		game->mShape->setPosition(transVector);
	}

	if (game->mShape->mLocal == 1)
	{
		game->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(transVector.x,transVector.y + 100,transVector.z + 150));

		game->mShape->mApplication->getCamera()->lookAt(Ogre::Vector3(transVector.x,transVector.y,transVector.z - 30.0f));
	
	}
}
void NORMAL_INTERPOLATETICK_MOVE::exit(Game* game)
{
}

	//abliityGame->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(0,20,20));
 	// Position it at 500 in Z direction
 	//   mCamera->setPosition(Ogre::Vector3(0,20,20));
    	// Look back along -Z
  	//  mCamera->lookAt(Ogre::Vector3(0,0,0));
