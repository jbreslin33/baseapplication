//header
#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//applicationBreslin
#include "../application/applicationBreslin.h"

//network
#include "../network/network.h"

//shape
#include "../shape/shape.h"

//bytebuffer
#include "../bytebuffer/byteBuffer.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

//state machine
#include "../../statemachine/stateMachine.h"
#include "states/gameGlobal.h"
#include "states/gameInitialize.h"
#include "states/gamePlay.h"
#include "states/gamePause.h"


/***************************************
*			          CONSTRUCTORS
***************************************/
Game::Game(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;

	mShapeVector = new std::vector<Shape*>();
	mShapeGhostVector = new std::vector<Shape*>();
	
	//keys
	mKeyUp = 1;
	mKeyDown = 2;
	mKeyLeft = 4;
	mKeyRight = 8;
	mKeyCounterClockwise = 16;
	mKeyClockwise = 32;
	
	//input
	mKeyCurrent = 0;
	mKeyLast = 0;
	mMillisecondsCurrent = 0;
	mMillisecondsLast = 0;

	//sequence
        mOutgoingSequence               = 1;

	//time
        mFrameTime = 0.0f;
        mRunNetworkTime = 0.0f;


	mStateMachine = new StateMachine();
	mGameGlobal = new GameGlobal(this);
	mGameInitialize = new GameInitialize(this);
	mGamePlay = new GamePlay(this);
	mGamePause = new GamePause(this);
	
	mStateMachine->setGlobalState(mGameGlobal);
	mStateMachine->changeState(mGamePlay);

	//set Camera
	// Position it at 500 in Z direction
    	mApplicationBreslin->getCamera()->setPosition(Ogre::Vector3(0,20,20));
    	// Look back along -Z
    	mApplicationBreslin->getCamera()->lookAt(Ogre::Vector3(0,0,0));
    	mApplicationBreslin->getCamera()->setNearClipDistance(5);
}

Game::~Game()
{
	LogString("Destructor for Game");
	for (unsigned int i = 0; i < mShapeVector->size(); i++)
	{
		delete mShapeVector->at(i);
		delete mShapeGhostVector->at(i);
	}
	

//ShapeVector::~mShapeVector();
//	ShapeGhostVector::VectormShapeGhostVector();
}
/*********************************
		TICK
**********************************/
void Game::processUpdate()
{
	mStateMachine->update();

	for (unsigned int i = 0; i < mShapeVector->size(); i++)
	{
		mShapeVector->at(i)->interpolateTick(mApplicationBreslin->getRenderTime());
	}
}

void Game::removeShape(ByteBuffer* byteBuffer)
{
	int index = byteBuffer->ReadByte();
	
	Shape* shape = getShape(index);

	for (unsigned int i = 0; i < mShapeVector->size(); i++)
	{
		if (mShapeVector->at(i) == shape)
		{
			delete mShapeVector->at(i);
			mShapeVector->erase (mShapeVector->begin()+i);
		}
	}
}

Shape* Game::getShape(int id)
{
	Shape* shape = NULL;

	for (unsigned int i = 0; i < mShapeVector->size(); i++)
	{
		Shape* curShape = mShapeVector->at(i);
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

void Game::runNetwork()
{
        mRunNetworkTime += mApplicationBreslin->getRenderTime() * 1000.0f;

        readPackets();

        // Framerate is too high
        if(mRunNetworkTime > (1000 / 60))
        {
                sendCommand();
                mFrameTime = mRunNetworkTime / 1000.0f;
                mRunNetworkTime = 0.0f;
        }
}


void Game::readPackets()
{
        int type = 0;

        ByteBuffer* byteBuffer = new ByteBuffer();

        while(mApplicationBreslin->mNetwork->checkForByteBuffer(byteBuffer))
        {
                byteBuffer->BeginReading();

                type = byteBuffer->ReadByte();

                switch(type)
                {
                        case mMessageAddShape:
                        	addShape(true,byteBuffer);
                        break;

                        case mMessageRemoveShape:
                                removeShape(byteBuffer);
                        break;

                        case mMessageFrame:
                                readServerTick(byteBuffer);
                        break;
                }
        }
}

void Game::readServerTick(ByteBuffer* byteBuffer)
{
        // Skip sequences
        short sequence = byteBuffer->ReadShort();

        while (byteBuffer->getReadCount() <= byteBuffer->GetSize())
        {
                //mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

                int id = byteBuffer->ReadByte();

                Shape* shape = NULL;
                shape = getShape(id);
                
		if (shape)
                {
                        shape->processDeltaByteBuffer(byteBuffer);
                }
                else
                {
                        //LogString("INVALID SHAPE ID");
                }
        }
}

void Game::sendCommand()
{
        //create byteBuffer
        ByteBuffer* byteBuffer = new ByteBuffer();
        
	//WRITE: type
        byteBuffer->WriteByte(mMessageFrame);                                   
        //WRITE: sequence
        byteBuffer->WriteShort(mOutgoingSequence);
        
        mOutgoingSequence++; //increase for next time...

        // Build delta-compressed move command
        int flags = 0;



        // Check what needs to be updated
        if(mKeyLast != mKeyCurrent)
        {
                flags |= mCommandKey;
        }

        if(mMillisecondsLast != mMillisecondsCurrent)
        {
                flags |= mCommandMilliseconds;
        }

        // Add to the message
        byteBuffer->WriteByte(flags);

        if(flags & mCommandKey)
        {
                //WRITE: key
                byteBuffer->WriteByte(mKeyCurrent);
        }

        if(flags & mCommandMilliseconds)
        {
                //WRITE: milliseconds
                byteBuffer->WriteByte(mMillisecondsCurrent);
        }
        
        //set 'last' commands for diff
        mKeyLast = mKeyCurrent;
        mMillisecondsLast = mMillisecondsCurrent;

        // Send the packet
        mApplicationBreslin->mNetwork->send(byteBuffer);
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
	mShapeVector->push_back(shape);
	mShapeGhostVector->push_back(shape->mGhost);	
}

/***************************************
*			INPUT
******************************************/


void Game::processInput()
{
	mKeyCurrent = 0;
    
	if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_I)) // Forward
   {
		mKeyCurrent |= mKeyUp;
   }

   if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_K)) // Backward
   {
		mKeyCurrent |= mKeyDown;
   }

	if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_J)) // Left
   {
		mKeyCurrent |= mKeyLeft;
   }

   if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_L)) // Right
   {
		mKeyCurrent |= mKeyRight;
   }
    
	if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_Z)) // Rotate -Yaw(counter-clockwise)
   {
		mKeyCurrent |= mKeyCounterClockwise;
   }

   if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_X)) // Right + Yaw(clockwise)
   {
		mKeyCurrent |= mKeyClockwise;
   }
   
	mMillisecondsCurrent = (int) (mFrameTime * 1000);
}
