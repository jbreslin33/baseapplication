#ifndef USERNAMESCREEN_H
#define USERNAMESCREEN_H

//Ogre headers
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

//username labels
OgreBites::Label* mLabelUsername;
OgreBites::Label* mLabelUsernameEdit;

//actual usnerame string
std::string mUsername;

void enter  ();
void execute();
void exit   ();

void createScreen();
void showScreen();
void hideScreen();

};

#endif
