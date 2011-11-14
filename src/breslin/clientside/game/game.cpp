//header
#include "game.h"

//application
#include "../game/application.h"

//shape
#include "../shape/shapeOgre.h"

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