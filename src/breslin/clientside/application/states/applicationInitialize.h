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

ApplicationBreslin* mApplication;

ApplicationInitialize(ApplicationBreslin* application);
~ApplicationInitialize();

void enter  ();
void execute();
void exit   ();

};

#endif
