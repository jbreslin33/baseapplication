//header
#include "gameOgre.h"

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
GameOgre::GameOgre(const char* serverIP, int serverPort) : Game(serverIP, serverPort)
{
	mGraphicsOgre = new GraphicsOgre(this);
}

GameOgre::~GameOgre()
{
}

/*********************************
*		TIME
***********************************/
float GameOgre::getRenderTime()
{
	//LogString("r:%f",mGraphicsOgre->mRenderTime);
	return mGraphicsOgre->mRenderTime;
}


/*********************************
*		SHAPE
**********************************/
void GameOgre::addShape(bool b, ByteBuffer* byteBuffer)
{
	ShapeDynamic* shapeDynamicOgre = new ShapeDynamicOgre(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	//shapeDynamicOgre->addAbility(new AbilityRotation(shapeDynamicOgre));
	shapeDynamicOgre->addAbility(new AbilityMove(shapeDynamicOgre));
}

/*********************************
		INPUT
**********************************/

void GameOgre::processInput()
{
	mGraphicsOgre->processInput();
}

/*********************************
		GRAPHICS ed isseilmann lincoln tech 215-969-0869
**********************************/
bool GameOgre::runGraphics()
{
	return mGraphicsOgre->runGraphics();
}

/*********************************
		GUI
**********************************/

void GameOgre::initializeGui()
{
	mGraphicsOgre->initializeGui();
}

