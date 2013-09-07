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
bool GLOBAL_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
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
bool PLAY_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
}

