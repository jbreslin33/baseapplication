#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class Game;

class GamePlay : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

Game* mGame;

GamePlay(Game* game);
~GamePlay();

void enter  ();
void execute();
void exit   ();

};

#endif