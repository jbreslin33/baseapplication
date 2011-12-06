#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "../../../statemachine/state.h"

/******************************************************
*				PROCESS TICK
*
*				   STATES
*
********************************************************/


/******************************************************
*				GLOBAL
********************************************************/

class PlayScreen : public State
{
public:

PlayScreen() {}

void enter  ();
void execute();
void exit   ();

};

#endif