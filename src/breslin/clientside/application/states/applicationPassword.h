#ifndef PASSWORDSCREEN_H
#define PASSWORDSCREEN_H

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

class ApplicationPassword : public State
{
public:

/***************************************
*   		MEMBER VARIABLES
***************************************/

ApplicationBreslin* mApplicationBreslin;

ApplicationPassword(ApplicationBreslin* applicationBreslin);
~ApplicationPassword();

//username labels
OgreBites::Label* mLabelPassword;
OgreBites::Label* mLabelPasswordEdit;

//actual usnerame string
std::string mPassword;

void enter  ();
void execute();
void exit   ();

void createScreen();
void showScreen();
void hideScreen();

};

#endif
