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

ApplicationPartido* mApplication;

ApplicationMainPartido(ApplicationPartido* application);
~ApplicationMainPartido();

void enter  ();
void execute();
void exit   ();

};

#endif
