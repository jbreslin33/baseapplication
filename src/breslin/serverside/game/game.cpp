#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//parser
#include "../parser/parser.h"

//server
#include "../server/server.h"

//network
#include "../network/network.h"

//client
#include "../client/client.h"

//shape
#include "../shape/shape.h"

//command
#include "../command/command.h"

Game::Game()
{
	mParser = new Parser();

	StartLog();

#ifdef _DEBUG
	mRoot = new Ogre::Root("plugins_d.cfg");
#else
	mRoot = new Ogre::Root("plugins.cfg");
#endif

	mRealTime	= 0;
	mServerTime	= 0;
	mFramenum	= 0;
	mFrameTime  = 0;
}

Game::~Game()
{
	StopLog();
	delete mServer;
}

void Game::createServer()
{
	LogString("createServer in Game");
	mServer = new Server(this,"", 30004);
}

void Game::createWorld()
{

}

void Game::frame(int msec)
{
	mRealTime += msec;

	mFrameTime += msec;

	// Read packets from clients
	mServer->readPackets();

	//just processtick for ai guys because their moves come from ai class/states
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		if (mShapeVector.at(i)->mClient == NULL) //your an ai guy
		{
			mShapeVector.at(i)->processTick();
		}
	}

	checkCollisions();

	// Wait full 32 ms before allowing to send
	if(mRealTime < mServerTime)
	{
		// never let the time get too far off
		if(mServerTime - mRealTime > 32)
		{
			mRealTime = mServerTime - 32;
		}

		return;
	}

	// Bump frame number, and calculate new mServerTime
	mFramenum++;
	mServerTime = mFramenum * 32;

	if(mServerTime < mRealTime)
		mRealTime = mServerTime;

	sendCommand();
	mFrameTime = 0;
}
/*
game is tag but what should i do here i think this is where we need to extend classes.

*/
void Game::checkCollisions()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
	  
		if (mShapeVector.at(i)->mCollidable == true)
		{
			for (unsigned int j = i+1; j < mShapeVector.size(); j++) 
			{
				if (mShapeVector.at(j)->mCollidable == true)
				{
					float x1 = mShapeVector.at(i)->mSceneNode->getPosition().x;
					float z1 = mShapeVector.at(i)->mSceneNode->getPosition().z;
					float x2 = mShapeVector.at(j)->mSceneNode->getPosition().x;
					float z2 = mShapeVector.at(j)->mSceneNode->getPosition().z;

					float distSq = pow((x1-x2),2) + pow((z1-z2),2);
					
					//i am simply adding the 2 collisionradius's of the 2 objects in question then comparing
					//to distSQ between them. IS this right or is it working by chance?
					if(distSq < mShapeVector.at(i)->mCollisionRadius + mShapeVector.at(j)->mCollisionRadius)
					{
						collision(mShapeVector.at(i),mShapeVector.at(j));
					}
				}
			}
		}
	}
}

void Game::collision(Shape* shape1, Shape* shape2)
{
	shape1->mCommand.mPosition = shape1->mCommand.mPositionOld;
	shape2->mCommand.mPosition = shape2->mCommand.mPositionOld;

	float x3 = shape1->mCommand.mPositionOld.x;
	float z3 = shape1->mCommand.mPositionOld.z;
	float x4 = shape2->mCommand.mPositionOld.x;
	float z4 = shape2->mCommand.mPositionOld.z;

	shape1->mSceneNode->setPosition(x3,0.0,z3);
	shape2->mSceneNode->setPosition(x4,0.0,z4);
}

bool Game::checkScope(Client* client, Shape* shape)
{
	//let's check scop here...
	float x1 = client->mShape->mSceneNode->getPosition().x;  //clientshape
	float z1 = client->mShape->mSceneNode->getPosition().z;
	float x2 = shape->mSceneNode->getPosition().x;  //build shape
	float z2 = shape->mSceneNode->getPosition().z;

	float distSq = pow((x1-x2),2) + pow((z1-z2),2);
			
	if(distSq < 10000000.0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

//send to updates to all clients about all shapes
void Game::sendCommand(void)
{
	// Fill messages..for all clients
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{
		//standard initialize of mMessage for client in this case
		mServer->mClientVector.at(i)->mMessage.Init(mServer->mClientVector.at(i)->mMessage.outgoingData,
			sizeof(mServer->mClientVector.at(i)->mMessage.outgoingData));

		//start filling said mMessage that belongs to client
		mServer->mClientVector.at(i)->mMessage.WriteByte(mServer->mMessageFrame);			// type
		mServer->mClientVector.at(i)->mMessage.WriteShort(mServer->mClientVector.at(i)->mOutgoingSequence);

		//this is where you need to actually loop thru the shapes not the clients but put write to client mMessage
		for (unsigned int j = 0; j < mShapeVector.size(); j++)
		{                         //the client to send to's message        //the shape command it's about
			//if (checkScope(mServer->mClientVector.at(i),mShapeVector.at(i)))
			//{
				buildDeltaMoveCommand(&mServer->mClientVector.at(i)->mMessage, mShapeVector.at(j));
			//}
		}
	}

	// Send messages to all clients
	mServer->sendPackets();

	// Store the sent command in mLastCommand.
	for (unsigned int i = 0; i < mServer->mGame->mShapeVector.size(); i++)
	{
		memcpy(&mServer->mGame->mShapeVector.at(i)->mLastCommand, &mServer->mGame->mShapeVector.at(i)->mCommand, sizeof(Command));
		mServer->mGame->mShapeVector.at(i)->mCommand.mMillisecondsTotal = 0;
	}
}


//this is the whole shabang server exit not a player or shape exit
void Game::sendExitNotification(void)
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{

		mServer->mClientVector.at(i)->mMessage.Init(mServer->mClientVector.at(i)->mMessage.outgoingData,
			sizeof(mServer->mClientVector.at(i)->mMessage.outgoingData));

		mServer->mClientVector.at(i)->mMessage.WriteByte(mParser->mMessageServerExit);	// type
		mServer->mClientVector.at(i)->mMessage.WriteShort(mServer->mClientVector.at(i)->mOutgoingSequence);
	}

	mServer->sendPackets();
}

//this is just for clients right now, should i make another or hijack this function??
void Game::readDeltaMoveCommand(Message *mes, Client *client)
{
	//LogString("dd");
	int flags = 0;

	// Flags
	flags = mes->ReadByte();
	//LogString("flags:%d",flags);

	// Key
	if(flags & mParser->mCommandKey)
	{
		client->mShape->mCommand.mKey = mes->ReadByte();
		//LogString("key:%d",client->mShape->mCommand.mKey);
	}

	// Milliseconds
	if(flags & mParser->mCommandMilliseconds)
	{
		//LogString("mil:%d",client->mShape->mCommand.mMilliseconds);
		client->mShape->mCommand.mMilliseconds = mes->ReadByte();
		
	}
	//LogString("cmil:%d",client->mShape->mCommand.mMilliseconds);
	//let's keep a tally called mMillisecondsTotal by adding up everytime we ReadDeltaMove...
	client->mShape->mCommand.mMillisecondsTotal += client->mShape->mCommand.mMilliseconds;

	//do i want to tally up the mKeys too???? especially if I'm not going to act on them as soon as i read them, atleast that is the plan.

	//let's set the shape's clientFrameTime right here.....
	client->mShape->mCommand.mClientFrametime = client->mShape->mCommand.mMilliseconds / 1000.0f;
}

//does this even care that a client is passed it? other than that it needs it access mShape? which
//i should already have?
void Game::buildDeltaMoveCommand(Message* mes, Shape* shape)
{
	Command* command = &shape->mCommand;

	int flags = setFlag(command,shape);
	buildDeltaMoveMessage(command,flags,mes,shape);

}

int Game::setFlag(Command* command, Shape* shape)
{

	int flags = 0;

	//Origin
	if(shape->mLastCommand.mPosition.x != command->mPosition.x)
	{
		flags |= mParser->mCommandOriginX;
	}
	if(shape->mLastCommand.mPosition.y != command->mPosition.y)
	{
		flags |= mParser->mCommandOriginY;
	}
	if(shape->mLastCommand.mPosition.z != command->mPosition.z)
	{
		flags |= mParser->mCommandOriginZ;
	}

	//Rotation
	if(shape->mLastCommand.mRotation.x != command->mRotation.x)
	{
		flags |= mParser->mCommandRotationX;
	}
	if(shape->mLastCommand.mRotation.z != command->mRotation.z)
	{
		flags |= mParser->mCommandRotationZ;
	}
	
	//Milliseconds
	if(shape->mLastCommand.mMillisecondsTotal != command->mMillisecondsTotal)
	{
		flags |= mParser->mCommandMilliseconds;
	}
	/*
	if(shape->mLastCommand.mPiggyBit != command->mPiggyBit)
	{
		flags |= mParser->mCommandPiggyBit;
	}
	*/
	return flags;
	

	
}

void Game::buildDeltaMoveMessage(Command* command, int flags, Message* message, Shape* shape)
{
	message->WriteByte(shape->mIndex);

	// Flags
	message->WriteByte(flags);  

	//Origin
	if(flags & mParser->mCommandOriginX)
	{
		message->WriteFloat(command->mPosition.x);
	}
	if(flags & mParser->mCommandOriginY)
	{
		message->WriteFloat(command->mPosition.y);
	}
	if(flags & mParser->mCommandOriginZ)
	{
		message->WriteFloat(command->mPosition.z);
	}

	//Rotation
	if(flags & mParser->mCommandRotationX)
	{
		message->WriteFloat(command->mRotation.x);
	}
	if(flags & mParser->mCommandRotationZ)
	{
		message->WriteFloat(command->mRotation.z);
	}

	//Milliseconds
	if(flags & mParser->mCommandMilliseconds)
	{
		message->WriteByte(command->mMillisecondsTotal);
	}
}


unsigned int Game::getOpenIndex()
{
	bool proposedIndexOpen = false;
	for (unsigned int proposedIndex = 1; !proposedIndexOpen; proposedIndex++) //keep going till you get an index
	{
		bool someoneHasThisIndex = false;
		for (unsigned int i = 0; i < mShapeVector.size(); i++)
		{
			if (mShapeVector.at(i)->mIndex == proposedIndex)
			{
				someoneHasThisIndex = true;
			}
		}
		if (someoneHasThisIndex == false)
		{
			return  proposedIndex;
		}
	}
	return 0;
}
