//header
#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shapeDynamicOgre.h"

//math
#include "../../math/vector3D.h"

//dispatch
#include "../dispatch/dispatch.h"

//time
#include "../time/time.h"

//network
#include "../network/network.h"

//abilitys
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

//parser
#include "../parser/parser.h"

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

	//parser
	mParser = new Parser();
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
void Game::addShape(bool b, Dispatch* dispatch)
{

}

void Game::removeShape(Dispatch* dispatch)
{
	int index = dispatch->ReadByte();
	
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


void Game::readServerTick(Dispatch* dispatch)
{
	int newTime;
	int time;

	// Skip sequences
	dispatch->ReadShort();

	newTime = mTime->dreamSock_GetCurrentSystemTime();
	time = newTime - mOldTime;
    mOldTime = newTime;

	while (dispatch->getReadCount() <= dispatch->GetSize())
	{
		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(dispatch->GetSize()));

		int id = dispatch->ReadByte();

		ShapeDynamic* shape = NULL;
		shape = getShapeDynamic(id);

		if (shape)
		{
			shape->readDeltaMoveCommand(dispatch);
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




