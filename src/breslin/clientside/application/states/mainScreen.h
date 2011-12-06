#ifndef MAINSCREEN_H
#define MAINSCREEN_H

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

class MainScreen : public State
{
public:

MainScreen() {}

void enter  ();
void execute();
void exit   ();

};

#endif