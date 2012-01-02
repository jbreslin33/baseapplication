#ifndef APPLICATIONINITIALIZE_H
#define APPLICATIONINITIALIZE_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ApplicationInitialize : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationInitialize(ApplicationBreslin* applicationBreslin);
~ApplicationInitialize();

void enter  ();
void execute();
void exit   ();

};

#endif
