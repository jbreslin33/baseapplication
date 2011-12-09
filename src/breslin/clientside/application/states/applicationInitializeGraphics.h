#ifndef APPLICATIONINITIALIZEGRAPHICS_H
#define APPLICATIONINITIALIZEGRAPHICS_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ApplicationInitializeGraphics : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationInitializeGraphics(ApplicationBreslin* applicationBreslin);
~ApplicationInitializeGraphics();

void enter  ();
void execute();
void exit   ();

};

#endif
