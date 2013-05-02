#ifndef GAMEBATTLE_H
#define GAMEBATTLE_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class GamePartido;

class GameBattle : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

GamePartido* mGame;

GameBattle(GamePartido* game);
~GameBattle();

void enter  ();
void execute();
void exit   ();

};

#endif
