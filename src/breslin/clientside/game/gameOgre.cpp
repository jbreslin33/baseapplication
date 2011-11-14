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
	Shape* shape = new Shape(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	shape->addAbility(new AbilityRotation(shape));
	shape->addAbility(new AbilityMove(shape));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector.push_back(shape);
	mShapeGhostVector.push_back(shape->mGhost);	

	shape->mShapeOgre->mApplicationOgre = mApplicationOgre;
	shape->mGhost->mShapeOgre->mApplicationOgre = mApplicationOgre;

	shape->mShapeOgre->createShape();
	shape->mGhost->mShapeOgre->createShape();
}

