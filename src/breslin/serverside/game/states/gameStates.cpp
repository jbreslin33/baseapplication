//parent
#include "gameStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../game.h"

//shape
#include "../../shape/shape.h"

//server
#include "../../server/server.h"

//client robust
#include "../../client/robust/clientRobust.h"

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
        game->mResetTime = 2000;

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
	LogString("NORMAL_GAME::enter");
	game->mGameTime = 0;
   	
	//set scores to zero.
        for (unsigned int i = 0; i < game->mServer->mClientVector.size(); i++)
        {
                game->mServer->mClientVector.at(i)->mScore = 0;
        }

	game->sendGameStart();
}
void NORMAL_GAME::execute(Game* game)
{
	//let's reset for a turn
        if (game->mGameTime > game->mGameTimeEnd)
        {
		game->mStateMachine->changeState(RESET_GAME::Instance());	
        }
	
	//this is where they want to move
        for (unsigned int i = 0; i < game->mShapeVector.size(); i++)
        {
                game->mShapeVector.at(i)->update();
                game->checkBounds(game->mShapeVector.at(i));
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
	LogString("RESET_GAME::enter");
	game->resetEnter();
}
void RESET_GAME::execute(Game* game)
{
	//send out standings here....

	LogString("RESET_GAME::execute");	

	//do this one every mResetTime
        if (game->mGameTime > game->mGameTimeEnd + game->mResetTime)
	{
		//go back in time for next one
		game->mGameTime = game->mGameTime - game->mResetTime;

		bool areWeDone = true;
        	for (unsigned int i = 0; i < game->mClientStandingsVector.size(); i++)
        	{
			if (game->mClientStandingsVector.at(i)->mStandingsSent == false)
			{		
				game->mClientStandingsVector.at(i)->mStandingsSent = true;
				areWeDone = false;
				LogString("id:%d",game->mClientStandingsVector.at(i));		
			}
		}
		if (areWeDone)
		{
			game->mStateMachine->changeState(NORMAL_GAME::Instance());	
		}
	}
}
void RESET_GAME::exit(Game* game)
{
	game->resetExit();
}
bool RESET_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
}

