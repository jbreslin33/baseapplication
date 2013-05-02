#ifndef GAMEPARTIDOPLAY_H
#define GAMEPARTIDOPLAY_H

#include "gamePlay.h"

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class GamePartido;

class GamePartidoPlay : public GamePlay 
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

GamePartido* mGame;

GamePartidoPlay(GamePartido* game);
~GamePartidoPlay();

void enter  ();
void execute();
void exit   ();

};

#endif
