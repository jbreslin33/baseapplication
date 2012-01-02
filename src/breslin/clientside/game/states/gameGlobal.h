#ifndef GAMEGLOBAL_H
#define GAMEGLOBAL_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class Game;

class GameGlobal : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

Game* mGame;

GameGlobal(Game* game);
~GameGlobal();

void enter  ();
void execute();
void exit   ();

};

#endif
