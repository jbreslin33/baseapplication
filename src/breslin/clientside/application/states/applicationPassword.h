#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ApplicationPassword : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationPassword(ApplicationBreslin* applicationBreslin);
~ApplicationPassword();

void enter  ();
void execute();
void exit   ();

};

#endif
