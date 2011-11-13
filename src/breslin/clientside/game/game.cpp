//header
#include "game.h"

//application
#include "../game/application.h"

//shape
#include "../shape/shapeDynamicOgre.h"

//bytebuffer
#include "../bytebuffer/byteBuffer.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
Game::Game(Application* application,const char* serverIP, int serverPort)
{
	mApplication = application;
}

Game::~Game()
{

}
/*********************************
		TICK
**********************************/
void Game::interpolateTick()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->interpolateTick(mApplication->getRenderTime());
	}
}

/*********************************
*		SHAPE
**********************************/
void Game::addShape(bool b, ByteBuffer* byteBuffer)
{
	/*
	ShapeDynamic* shapeDynamicOgre = new ShapeDynamicOgre(this,byteBuffer,false);  //you should just need to call this...
	
	//ability
	shapeDynamicOgre->addAbility(new AbilityRotation(shapeDynamicOgre));
	shapeDynamicOgre->addAbility(new AbilityMove(shapeDynamicOgre));
	*/
}


void Game::removeShape(ByteBuffer* byteBuffer)
{
	int index = byteBuffer->ReadByte();
	
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		if (mShapeVector.at(i)->mIndex == index)
		{
			delete mShapeVector.at(i);
			mShapeVector.erase (mShapeVector.begin()+i);
		}
	}
}

ShapeDynamic* Game::getShapeDynamic(int id)
{
	ShapeDynamic* shape = NULL;

	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		ShapeDynamic* curShape = mShapeVector.at(i);
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