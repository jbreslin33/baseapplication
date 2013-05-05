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

class ApplicationLogin : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplication;

ApplicationLogin(ApplicationBreslin* application);
~ApplicationLogin();

void enter  ();
void execute();
void exit   ();

};

#endif
