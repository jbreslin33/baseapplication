#ifndef GAMEPLAYPARTIDO_H
#define GAMEPLAYPARTIDO_H

#include "gamePlay.h"

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class GamePartido;

class GamePlayPartido : public GamePlay 
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

GamePartido* mGamePartido;

GamePlayPartido(GamePartido* gamePartido);
~GamePlayPartido();

virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
