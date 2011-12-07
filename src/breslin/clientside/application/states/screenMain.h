#ifndef MAINSCREEN_H
#define MAINSCREEN_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ScreenMain : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ScreenMain(ApplicationBreslin* applicationBreslin);
~ScreenMain();

void enter  ();
void execute();
void exit   ();

};

#endif
