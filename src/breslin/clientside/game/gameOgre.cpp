//header
#include "gameOgre.h"

//shape
#include "../shape/shapeOgre.h"

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
	ShapeDynamic* shapeOgre = new ShapeOgre(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	shapeOgre->addAbility(new AbilityRotation(shapeOgre));
	shapeOgre->addAbility(new AbilityMove(shapeOgre));
}

