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

class ApplicationMain : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationMain(ApplicationBreslin* applicationBreslin);
~ApplicationMain();

void enter  ();
void execute();
void exit   ();

};

#endif
