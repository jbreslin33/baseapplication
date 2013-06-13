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
}

void GamePlay::exit()
{
	
}
