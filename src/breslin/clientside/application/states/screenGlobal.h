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

class ScreenMain : public State
{
public:

ScreenMain() {}

void enter  ();
void execute();
void exit   ();

};

#endif