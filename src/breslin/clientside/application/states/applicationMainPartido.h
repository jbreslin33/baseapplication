#ifndef MAINSCREENPARTIDO_H
#define MAINSCREENPARTIDO_H

/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationPartido;

class ApplicationMainPartido : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationPartido* mApplication;

ApplicationMainPartido(ApplicationPartido* application);
~ApplicationMainPartido();

void enter  ();
void execute();
void exit   ();

};

#endif
