//header
#include "gameTag.h"

//application
#include "../game/application.h"

//shape
#include "../shape/shapeTag.h"

//bytebuffer
#include "../bytebuffer/byteBuffer.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GameTag::GameTag(Application* application) :
Game(application)
{

}

GameTag::~GameTag()
{

}

/*********************************
*		SHAPE
**********************************/
void GameTag::addShape(bool b, ByteBuffer* byteBuffer)
{
	ShapeTag* shapeTag = new ShapeTag(mApplication,byteBuffer,false);  //you should just need to call this...

	//ability
	shapeTag->addAbility(new AbilityRotation(shapeTag));
	shapeTag->addAbility(new AbilityMove(shapeTag));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector.push_back(shapeTag);
	mShapeGhostVector.push_back(shapeTag->mGhost);	
}
