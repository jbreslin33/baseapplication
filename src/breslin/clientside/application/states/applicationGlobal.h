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

class ApplicationGlobal : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplication;

ApplicationGlobal(ApplicationBreslin* application);
~ApplicationGlobal();

void enter  ();
void execute();
void exit   ();

};

#endif
