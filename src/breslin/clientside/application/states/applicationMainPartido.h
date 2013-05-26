#ifndef MAINSCREENPARTIDO_H
#define MAINSCREENPARTIDO_H

/***************************************
*   		INCLUDES
***************************************/
#include "applicationMain.h"


/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationPartido;

class ApplicationMainPartido : public ApplicationMain 
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationPartido* mApplicationPartido;

ApplicationMainPartido(ApplicationPartido* applicationPartido);
~ApplicationMainPartido();

virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
