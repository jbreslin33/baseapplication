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


/***************************************
*			          CONSTRUCTORS
***************************************/
Game::Game(const char* serverIP, int serverPort)
{
	StartLog();

	//command
	mLastCommandToServer = new Command();
	mCommandToServer = new Command(); 

	// network
	mNetwork = new Network(serverIP,serverPort);

	//time
	mTime = new Time();
	mFrameTime		 = 0.0f;
	mOldTime         = 0;

	//initilize
 	mInit			 = false;
	mNetworkShutdown = false;

	mInit = true;

	//parser
	mParser = new Parser();
}

Game::~Game()
{
//	delete mClient;
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
		processUnbufferedInput();
		runNetwork(getRenderTime() * 1000);
		interpolateFrame();
		if (!runGraphics())
		{
			break;
		}
		initializeGui();
	}
}

void Game::shutdown(void)
{
	if(!mInit)
		return;
	mInit = false;
	sendDisconnect();
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

void Game::frame(Dispatch* dispatch)
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
		if (mNetworkShutdown)
		{
			return;
		}

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

void Game::interpolateFrame()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->interpolateTick(getRenderTime());
	}
}

/*********************************
		NETWORK
**********************************/
void Game::runNetwork(int msec)
{
	static int time = 0;
	time += msec;

	readPackets();
	
	// Framerate is too high
	if(time > (1000 / 60))
	{
		sendCommand();
		mFrameTime = time / 1000.0f;
		time = 0;
	}
}

void Game::readPackets()
{
	int type;
	int ret;

	Dispatch* dispatch = new Dispatch();

	while(ret = mNetwork->checkForDispatch(dispatch))
	{
		dispatch->BeginReading();

		type = dispatch->ReadByte();

		switch(type)
		{
			case mParser->mMessageAddShape:
				addShape(true,dispatch);
			break;

			case mParser->mMessageRemoveShape:
				removeShape(dispatch);
			break;

			case mParser->mMessageFrame:
				frame(dispatch);
			break;

			case mParser->mMessageServerExit:
				shutdown();
			break;
		}
	}
}
void Game::sendConnect(const char *name)
{
	Dispatch* dispatch = new Dispatch();
	dispatch->WriteByte(mParser->mMessageConnect);
	dispatch->WriteString(name);
	mNetwork->send(dispatch);
}

void Game::sendDisconnect()
{
	Dispatch* dispatch = new Dispatch();
	dispatch->WriteByte(mParser->mMessageDisconnect);
	mNetwork->send(dispatch);
	mNetwork->reset();
}

void Game::sendCommand(void)
{
	Dispatch* dispatch = new Dispatch();
	dispatch->WriteByte(mParser->mMessageFrame);					
	dispatch->WriteShort(mNetwork->mOutgoingSequence);

	// Build delta-compressed move command
	int flags = 0;

	// Check what needs to be updated
	if(mLastCommandToServer->mKey != mCommandToServer->mKey)
	{
		flags |= mParser->mCommandKey;
	}

	if(mLastCommandToServer->mMilliseconds != mCommandToServer->mMilliseconds)
	{
		flags |= mParser->mCommandMilliseconds;
	}

	// Add to the message
	dispatch->WriteByte(flags);

	if(flags & mParser->mCommandKey)
	{
		dispatch->WriteByte(mCommandToServer->mKey);
	}

	if(flags & mParser->mCommandMilliseconds)
	{
		dispatch->WriteByte(mCommandToServer->mMilliseconds);
	}
	
	//set 'last' commands for diff
	mLastCommandToServer->mKey = mCommandToServer->mKey;
	mLastCommandToServer->mMilliseconds = mCommandToServer->mMilliseconds;

	// Send the packet
	mNetwork->send(dispatch);
}


