#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ApplicationUsername : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationUsername(ApplicationBreslin* applicationBreslin);
~ApplicationUsername();

void enter  ();
void execute();
void exit   ();

};

#endif
