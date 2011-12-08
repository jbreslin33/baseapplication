#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ScreenPlay : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ScreenPlay(ApplicationBreslin* applicationBreslin);
~ScreenPlay();

void enter  ();
void execute();
void exit   ();

};

#endif