#ifndef APPLICATIONPLAY_H
#define APPLICATIONPLAY_H

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

ApplicationBreslin* mApplicationBreslin;

ApplicationPlay(ApplicationBreslin* applicationBreslin);
~ApplicationPlay();

virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
