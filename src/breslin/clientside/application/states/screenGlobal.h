#ifndef SCREENGLOBAL_H
#define SCREENGLOBAL_H

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

class ScreenGlobal : public State
{
public:

ScreenGlobal() {}

void enter  ();
void execute();
void exit   ();

};

#endif
