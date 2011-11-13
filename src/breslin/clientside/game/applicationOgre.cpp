//header
#include "applicationOgre.h"

//standard library
#include <string>

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "gameOgre.h"

//graphics
#include "../graphics/graphicsOgre.h"

//shape
#include "../shape/shapeDynamicOgre.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"


/*********************************
*		CONSTRUCTORS
**********************************/
ApplicationOgre::ApplicationOgre(const char* serverIP, int serverPort) : Application(serverIP, serverPort) 

{
	LogString("ApplicationOgre!!!!!!!!!!!!!!!!");
	mGame = new GameOgre(this,serverIP,serverPort);
	//mGame = mGameOgre

	mGraphicsOgre = new GraphicsOgre(this);
}

ApplicationOgre::~ApplicationOgre()
{
}

/*********************************
*		TIME
***********************************/
float ApplicationOgre::getRenderTime()
{
	//LogString("r:%f",mGraphicsOgre->mRenderTime);
	return mGraphicsOgre->mRenderTime;
}

/*********************************
		INPUT
**********************************/

void ApplicationOgre::processInput()
{
	mGraphicsOgre->processInput();
}

/*********************************
		GRAPHICS 
**********************************/
bool ApplicationOgre::runGraphics()
{
	return mGraphicsOgre->runGraphics();
}

/*********************************
		GUI
**********************************/

void ApplicationOgre::initializeGui()
{
	mGraphicsOgre->initializeGui();
}

