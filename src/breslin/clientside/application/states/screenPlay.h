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

class ScreenPlay : public State
{
public:

ScreenPlay() {}

void enter  ();
void execute();
void exit   ();

};

#endif