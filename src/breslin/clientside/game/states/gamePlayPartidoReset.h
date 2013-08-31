#ifndef GAMEPLAYPARTIDORESET_H
#define GAMEPLAYPARTIDORESET_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class GamePartido;

class GamePlayPartidoReset : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

GamePartido* mGamePartido;
bool mFirstTimeExecute;

GamePlayPartidoReset(GamePartido* gamePartido);
~GamePlayPartidoReset();

void enter  ();
void execute();
void exit   ();

};

#endif
