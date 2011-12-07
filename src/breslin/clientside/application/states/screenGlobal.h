#ifndef SCREENGLOBAL_H
#define SCREENGLOBAL_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ScreenGlobal : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ScreenGlobal(ApplicationBreslin* applicationBreslin);
~ScreenGlobal();

void enter  ();
void execute();
void exit   ();

};

#endif
