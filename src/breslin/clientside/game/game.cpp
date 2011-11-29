//header
#include "game.h"

//applicationBreslin
#include "../application/applicationBreslin.h"

//shape
#include "../shape/shape.h"

//bytebuffer
#include "../bytebuffer/byteBuffer.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
Game::Game(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

Game::~Game()
{
	mShapeVector.clear();
	mShapeGhostVector.clear();
}
/*********************************
		TICK
**********************************/
void Game::run()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->interpolateTick(mApplicationBreslin->getRenderTime());
	}
}

void Game::removeShape(ByteBuffer* byteBuffer)
{
	int index = byteBuffer->ReadByte();
	
	Shape* shape = getShape(index);

	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		if (mShapeVector.at(i) == shape)
		{
			delete mShapeVector.at(i);
			mShapeVector.erase (mShapeVector.begin()+i);
		}
	}
}

Shape* Game::getShape(int id)
{
	Shape* shape = NULL;

	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		Shape* curShape = mShapeVector.at(i);
		if (curShape->mIndex == id)
		{
			shape = curShape;
		}
	}

	if(!shape)
	{
		return NULL;
	}
	else
	{
		return shape;
	}
}

/*************************************************
*
*   OGRE_SPECIFIC
*
**************************************************

/*********************************
*		SHAPE
**********************************/
void Game::addShape(bool b, ByteBuffer* byteBuffer)
{
	Shape* shape = new Shape(mApplicationBreslin,byteBuffer,false);  //you should just need to call this...

	//ability
	shape->addAbility(new AbilityRotation(shape));
	shape->addAbility(new AbilityMove(shape));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector.push_back(shape);
	mShapeGhostVector.push_back(shape->mGhost);	
}
