//header
#include "gameOgreTag.h"

//standard library
#include <string>

//log
#include "../tdreamsock/dreamSockLog.h"

//graphics
#include "../graphics/graphicsOgre.h"

//shape
#include "../shape/shapeDynamicOgreTag.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"


/*********************************
*		CONSTRUCTORS
**********************************/
GameOgreTag::GameOgreTag(const char* serverIP, int serverPort) : GameOgre(serverIP, serverPort)
{
	LogString("GAMEOGRETAG!!!!!!!!!!!!!!!!");
}

GameOgreTag::~GameOgreTag()
{
}

/*********************************
*		SHAPE
**********************************/
void GameOgreTag::addShape(bool b, ByteBuffer* byteBuffer)
{
	ShapeDynamic* shapeDynamicOgre = new ShapeDynamicOgre(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	shapeDynamicOgre->addAbility(new AbilityRotation(shapeDynamicOgre));
	shapeDynamicOgre->addAbility(new AbilityMove(shapeDynamicOgre));
}
