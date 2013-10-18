//parent
#include "gameStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../game.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
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

/*****************************************
*******       INIT    ******************
****************************************/
INIT_GAME* INIT_GAME::Instance()
{
  static INIT_GAME instance;
  return &instance;
}
void INIT_GAME::enter(Game* game)
{
}
void INIT_GAME::execute(Game* game)
{
	game->mGameTime = 0;
        game->mGameTimeEnd = 50000;
        game->mGameTimeReset = 0;
        game->mGameTimeResetEnd = 0;

	game->mStateMachine->changeState(NORMAL_GAME::Instance());

}
void INIT_GAME::exit(Game* game)
{
}
bool INIT_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
}

/*****************************************
*******       NORMAL    ******************
****************************************/
NORMAL_GAME* NORMAL_GAME::Instance()
{
  static NORMAL_GAME instance;
  return &instance;
}
void NORMAL_GAME::enter(Game* game)
{
	game->mGameTime = 0;
}
void NORMAL_GAME::execute(Game* game)
{
	//let's reset for a turn
        if (game->checkForEndOfGame())
        {
		game->mStateMachine->changeState(RESET_GAME::Instance());	
        }
}
void NORMAL_GAME::exit(Game* game)
{
}
bool NORMAL_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
}

/*****************************************
*******       RESET    ******************
****************************************/
RESET_GAME* RESET_GAME::Instance()
{
  static RESET_GAME instance;
  return &instance;
}
void RESET_GAME::enter(Game* game)
{
	game->reset();
}
void RESET_GAME::execute(Game* game)
{
	game->mStateMachine->changeState(NORMAL_GAME::Instance());	
}
void RESET_GAME::exit(Game* game)
{
	game->sendGameStart();
}
bool RESET_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
}

