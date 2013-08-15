#ifndef GAMEPLAYPARTIDOSHOWCORRECTANSWER_H
#define GAMEPLAYPARTIDOSHOWCORRECTANSWER_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class GamePartido;

class GamePlayPartidoShowCorrectAnswer : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

GamePartido* mGamePartido;
bool mFirstTimeExecute;

GamePlayPartidoShowCorrectAnswer(GamePartido* gamePartido);
~GamePlayPartidoShowCorrectAnswer();

void enter  ();
void execute();
void exit   ();

};

#endif
