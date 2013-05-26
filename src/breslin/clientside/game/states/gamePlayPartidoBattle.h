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

GamePartido* mGamePartido;

GamePlayPartidoBattle(GamePartido* gamePartido);
~GamePlayPartidoBattle();

void enter  ();
void execute();
void exit   ();

};

#endif
