#ifndef APPLICATIONOGRE_H
#define APPLICATIONOGRE_H

/***************************************
*   		INCLUDES
***************************************/
//standard library

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//parents
#include "application.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
//game
class GameOgre;

//graphics
class GraphicsOgre;

//ByteBuffer
class ByteBuffer;

class ApplicationOgre : public Application
{
public:
	
	ApplicationOgre(const char* serverIP, int serverPort);
	~ApplicationOgre();

/***************************************
*   		MEMBER VARIABLES
***************************************/
//game
GameOgre* mGameOgre;

//gui
OgreBites::Button* mJoinButton;

/***************************************
*			          METHODS
***************************************/

//time
virtual float getRenderTime();

//graphics
virtual bool runGraphics();

virtual void initializeGui();

virtual void processInput();


//graphics
Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }
virtual void        createScene          ();
virtual bool        frameRenderingQueued (const Ogre::FrameEvent& evt);


//gui	
void hideGui();
void loadJoinScreen();
void hideJoinScreen();
void unloadOtherScreens();


	//input
void buttonHit             (OgreBites::Button *button);
bool mouseMoved            ( const OIS::MouseEvent &arg );

};

#endif
