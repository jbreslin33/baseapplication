#ifndef GAMEINITIALIZE_H
#define GAMEINITIALIZE_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class Game;

class GameInitialize : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

Game* mGame;

GameInitialize(Game* game);
~GameInitialize();

void enter  ();
void execute();
void exit   ();

};

#endif