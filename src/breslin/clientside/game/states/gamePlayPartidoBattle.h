#ifndef GAMEPLAYPARTIDOBATTLE_H
#define GAMEPLAYPARTIDOBATTLE_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class GamePartido;

class GamePlayPartidoBattle : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

GamePartido* mGame;

GamePlayPartidoBattle(GamePartido* game);
~GamePlayPartidoBattle();

void enter  ();
void execute();
void exit   ();

};

#endif
