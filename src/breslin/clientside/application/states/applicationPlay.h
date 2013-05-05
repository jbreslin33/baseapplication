#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ApplicationPlay : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplication;

ApplicationPlay(ApplicationBreslin* application);
~ApplicationPlay();

void enter  ();
void execute();
void exit   ();

};

#endif
