//header
#include "gamePlay.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../../application/applicationBreslin.h"

//game
#include "../game.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
GamePlay::GamePlay(Game* game)
{
	mGame = game;
}

GamePlay::~GamePlay()
{

}

void GamePlay::enter()
{
	
}
void GamePlay::execute()
{
 	//process input
 	mGame->mKeyCurrent = 0;

        if (mGame->mApplication->getKeyboard()->isKeyDown(OIS::KC_W)) // Forward
        {
        	mGame->mApplication->mKeyArray[119] = true;
                mGame->mKeyCurrent |= mGame->mKeyUp;
        }
       	else
        {
        	mGame->mApplication->mKeyArray[119] = false;
        }


        if (mGame->mApplication->getKeyboard()->isKeyDown(OIS::KC_S)) // down 
        {
        	mGame->mApplication->mKeyArray[115] = true;
                mGame->mKeyCurrent |= mGame->mKeyDown;
        }
       	else
        {
        	mGame->mApplication->mKeyArray[115] = false;
        }

        if (mGame->mApplication->getKeyboard()->isKeyDown(OIS::KC_A)) // left 
        {
        	mGame->mApplication->mKeyArray[97] = true;
                mGame->mKeyCurrent |= mGame->mKeyLeft;
        }
       	else
        {
        	mGame->mApplication->mKeyArray[97] = false;
        }


        if (mGame->mApplication->getKeyboard()->isKeyDown(OIS::KC_D)) // right 
        {
        	mGame->mApplication->mKeyArray[100] = true;
                mGame->mKeyCurrent |= mGame->mKeyRight;
        }
       	else
        {
        	mGame->mApplication->mKeyArray[100] = false;
        }

	//network outgoing
	mGame->sendByteBuffer();

/*
 	mGame->mKeyCurrent = 0;
  	if (mGame->mApplication->mKeyArray[119]) //forward
        {
        //	mGame->mApplication->mKeyArray[119] = false;
                mGame->mKeyCurrent |= mGame->mKeyUp;
        }
  	if (mGame->mApplication->mKeyArray[119] == false) //forward
        {
		LogString("false");
        	//mGame->mApplication->mKeyArray[119] = false;
               // mGame->mKeyCurrent |= mGame->mKeyUp;
        }
*/

/*
 mKeyCurrent = 0;

        if (mApplication->getKeyboard()->isKeyDown(OIS::KC_I)) // Forward
        {
                mKeyCurrent |= mKeyUp;
        }

        if (mApplication->getKeyboard()->isKeyDown(OIS::KC_K)) // Backward
        {
                mKeyCurrent |= mKeyDown;
        }

        if (mApplication->getKeyboard()->isKeyDown(OIS::KC_J)) // Left
        {
                mKeyCurrent |= mKeyLeft;
        }

        if (mApplication->getKeyboard()->isKeyDown(OIS::KC_L)) // Right
        {
                mKeyCurrent |= mKeyRight;
        }

        if (mApplication->getKeyboard()->isKeyDown(OIS::KC_Z)) // Rotate -Yaw(counter-clockwise)
        {
                mKeyCurrent |= mKeyCounterClockwise;
        }

        if (mApplication->getKeyboard()->isKeyDown(OIS::KC_X)) // Right + Yaw(clockwise)
        {
                mKeyCurrent |= mKeyClockwise;
        }

*/	
	
}

void GamePlay::exit()
{
	
}
