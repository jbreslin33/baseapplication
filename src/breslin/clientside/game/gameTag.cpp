//header
#include "gameTag.h"

//applicationBreslin
#include "../application/applicationBreslin.h"

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
GameTag::GameTag(ApplicationBreslin* applicationBreslin) :
Game(applicationBreslin)
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
	ShapeTag* shapeTag = new ShapeTag(mApplicationBreslin,byteBuffer,false);  //you should just need to call this...

	//ability
	shapeTag->addAbility(new AbilityRotation(shapeTag));
	shapeTag->addAbility(new AbilityMove(shapeTag));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector->push_back(shapeTag);
	mShapeGhostVector->push_back(shapeTag->mGhost);	
}
