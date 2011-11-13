//header
#include "gameOgre.h"

//shape
#include "../shape/shapeDynamicOgre.h"

//ability
#include "../ability/ability.h"



//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GameOgre::GameOgre(ApplicationOgre* applicationOgre, const char* serverIP, int serverPort) : 
Game((Application*)applicationOgre,serverIP,serverPort)
{
	mApplicationOgre = applicationOgre;
}

GameOgre::~GameOgre()
{

}


/*********************************
*		SHAPE
**********************************/
void GameOgre::addShape(bool b, ByteBuffer* byteBuffer)
{
	ShapeDynamic* shapeDynamicOgre = new ShapeDynamicOgre(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	shapeDynamicOgre->addAbility(new AbilityRotation(shapeDynamicOgre));
	shapeDynamicOgre->addAbility(new AbilityMove(shapeDynamicOgre));
}

