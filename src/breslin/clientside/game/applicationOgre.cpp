//header
#include "applicationOgre.h"

//standard library
#include <string>

//log
#include "../tdreamsock/dreamSockLog.h"

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
*		SHAPE
**********************************/
void ApplicationOgre::addShape(bool b, ByteBuffer* byteBuffer)
{
	ShapeDynamic* shapeDynamicOgre = new ShapeDynamicOgre(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	shapeDynamicOgre->addAbility(new AbilityRotation(shapeDynamicOgre));
	shapeDynamicOgre->addAbility(new AbilityMove(shapeDynamicOgre));
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

