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
	game->processMoveControls();
}
void PLAY_GAME::exit(Game* game)
{
}
bool PLAY_GAME::onLetter(Game* game, Letter* letter)
{
        return true;
}

