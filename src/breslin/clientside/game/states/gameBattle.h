#ifndef GAMEBATTLE_H
#define GAMEBATTLE_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class Game;

class GameBattle : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

Game* mGame;

GameBattle(Game* game);
~GameBattle();

void enter  ();
void execute();
void exit   ();

};

#endif
