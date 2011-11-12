#ifndef GRAPHICSOGRE_H
#define GRAPHICSOGRE_H

/***************************************
*   		INCLUDES
***************************************/
//standard library

//parents
#include "../game/BaseApplication.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

//game
class ApplicationOgre;

class GraphicsOgre : public BaseApplication
{
public:
	
	GraphicsOgre(ApplicationOgre* applicationOgre);
	~GraphicsOgre();

/***************************************
*   		MEMBER VARIABLES
***************************************/

//initialize
bool mInitializeGui;
bool mJoinGame;
bool mPlayingGame;

//game
ApplicationOgre* mApplicationOgre;

//time
float mRenderTime;

//gui
OgreBites::Button* mJoinButton;

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;
	

/***************************************
*			          METHODS
***************************************/

//graphics
Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }
virtual void        createScene          ();
virtual bool        frameRenderingQueued (const Ogre::FrameEvent& evt);
bool                runGraphics          ();

//gui	
void hideGui();
void loadJoinScreen();
void hideJoinScreen();
void unloadOtherScreens();
void initializeGui();

	//input
void buttonHit             (OgreBites::Button *button);
bool mouseMoved            ( const OIS::MouseEvent &arg );
void processInput();
};

#endif
