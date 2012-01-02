#ifndef GAMEPAUSE_H
#define GAMEPAUSE_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class Game;

class GamePause : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

Game* mGame;

GamePause(Game* game);
~GamePause();

void enter  ();
void execute();
void exit   ();

};

#endif