//header
#include "application.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shapeOgre.h"

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

//game
#include "game.h"


/***************************************
*			          CONSTRUCTORS
***************************************/
Application::Application(const char* serverIP, int serverPort)
{
	StartLog();

	// network
	mNetwork = new Network(this,serverIP,serverPort);

	//time
	mTime = new Time();
	mFrameTime		 = 0.0f;
	mOldTime         = 0;

	mGame = 0;

	//time
	mRenderTime = 0;

	//keys
	mKeyUp = 1;
	mKeyDown = 2;
	mKeyLeft = 4;
	mKeyRight = 8;
	mKeyCounterClockwise = 16;
	mKeyClockwise = 32;

	//initilize
	mInitializeGui = false;
	mJoinGame    = false;
	mPlayingGame = false;
}

Application::~Application()
{
	mNetwork->close();
	delete mNetwork;
}

/*********************************
		START/LOOP/END
**********************************/
void Application::gameLoop()
{

	while(true)
    {
		//input
		processInput();
		
		//network
		runNetwork(getRenderTime() * 1000.0f);
		
		//move objects
		mGame->interpolateTick();

		//draw
		if (!runGraphics())
		{
			break;
		}
	}
}

void Application::shutdown()
{
	mNetwork->sendDisconnect();
}


void Application::readServerTick(ByteBuffer* byteBuffer)
{
	// Skip sequences
	byteBuffer->ReadShort();

	while (byteBuffer->getReadCount() <= byteBuffer->GetSize())
	{
		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

		int id = byteBuffer->ReadByte();

		Shape* shape = NULL;
		shape = mGame->getShape(id);

		if (shape)
		{
			shape->readDeltaMoveCommand(byteBuffer);
			shape->processTick();
		}
	}
}

/*********************************
		NETWORK
**********************************/
void Application::runNetwork(float msec)
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




