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

virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
