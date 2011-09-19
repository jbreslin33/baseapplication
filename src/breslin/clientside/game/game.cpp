//header
#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shapeDynamicOgre.h"

//math
#include "../../math/vector3D.h"

//byteBuffer
#include "../byteBuffer/byteBuffer.h"

//time
#include "../time/time.h"

//network
#include "../network/network.h"

//abilitys
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

//command
#include "../command/command.h"


/***************************************
*			          CONSTRUCTORS
***************************************/
Game::Game(const char* serverIP, int serverPort)
{
	StartLog();

	// network
	mNetwork = new Network(this,serverIP,serverPort);

	//time
	mTime = new Time();
	mFrameTime		 = 0.0f;
	mOldTime         = 0;
}

Game::~Game()
{
	mNetwork->close();
	delete mNetwork;
}

/*********************************
		START/LOOP/END
**********************************/
void Game::gameLoop()
{

	while(true)
    {
		//input
		processInput();
		
		//network
		runNetwork(getRenderTime() * 1000.0f);
		
		//move objects
		interpolateTick();

		//draw
		if (!runGraphics())
		{
			break;
		}
	}
}

void Game::shutdown()
{
	mNetwork->sendDisconnect();
}

/*********************************
		SHAPE
**********************************/
void Game::addShape(bool b, ByteBuffer* byteBuffer)
{

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



/*********************************
		TICK
**********************************/
void Game::interpolateTick()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->interpolateTick(getRenderTime());
	}
}

void Game::readServerTick(ByteBuffer* byteBuffer)
{
	// Skip sequences
	byteBuffer->ReadShort();

	while (byteBuffer->getReadCount() <= byteBuffer->GetSize())
	{
		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

		int id = byteBuffer->ReadByte();

		ShapeDynamic* shape = NULL;
		shape = getShapeDynamic(id);

		if (shape)
		{
			shape->readDeltaMoveCommand(byteBuffer);
		}
	}
}

/*********************************
		NETWORK
**********************************/
void Game::runNetwork(float msec)
{
	static float time = 0.0f;
	time += msec;

	mNetwork->readPackets();
	
	// Framerate is too high
	if(time > (1000 / 60))
	{
		mNetwork->sendCommand();
		mFrameTime = time / 1000.0f;
		time = 0;
	}
}




