#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

//ogre
#include "Ogre.h"
using namespace Ogre;

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>



/***************************************
*   		INCLUDES
***************************************/

#include "../../../statemachine/state.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class ApplicationBreslin;

class ApplicationUsername : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationUsername(ApplicationBreslin* applicationBreslin);
~ApplicationUsername();

OgreBites::SdkTrayManager* mTrayMgr;

//login
OgreBites::Label* mLabelUsername;
OgreBites::Label* mLabelUsernameEdit;


void enter  ();
void execute();
void exit   ();

};

#endif
