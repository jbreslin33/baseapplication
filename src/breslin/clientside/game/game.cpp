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

//ObjectTitle
#include "../billboard/objectTitle.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
Game::Game(ApplicationBreslin* application)
{
	mApplication = application;

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

	//time
    	mRunNetworkTime = 0.0f;
	mFrameTimeServer = 0.0f;

	//set Camera
	// Position it at 500 in Z direction
    	mApplication->getCamera()->setPosition(Ogre::Vector3(0,20,20));
    	// Look back along -Z
    	mApplication->getCamera()->lookAt(Ogre::Vector3(0,0,0));
    	mApplication->getCamera()->setNearClipDistance(5);

	createScene();

	LogString("Game::Game");

	mStateMachine = new StateMachine();
}
/*


*/
Game::~Game()
{
}

void Game::createStates()
{
	mGameGlobal     = new GameGlobal    (this);
	mGameInitialize = new GameInitialize(this);
	mGamePlay       = new GamePlay      (this);
	mGamePause      = new GamePause     (this);
}

void Game::setStates()
{
	mStateMachine->setGlobalState(mGameGlobal);
	mStateMachine->changeState   (mGamePlay);
}

//i am guessing i am not clearing the shape arrray???
void Game::remove()
{
        if (mShapeVector)
        {
                for (unsigned int i = 0; i < mShapeVector->size(); i++)
                {
			Shape* shape = mShapeVector->at(i);

        		//delete objectTitles
			if (shape)
			{
        			delete shape->mGhost->mObjectTitle;
        			delete shape->mObjectTitle;
			}
                }
        }
	
	mApplication->getSceneManager()->destroyAllEntities();
        mApplication->mSceneMgr->destroyLight(mPointLight);

	//clear the vectors....	
	mShapeVector->clear();
	mShapeGhostVector->clear();
}

/*********************************
		Update
**********************************/
void Game::processUpdate()
{
	mStateMachine->update();

	for (unsigned int i = 0; i < mShapeVector->size(); i++)
	{
		mShapeVector->at(i)->interpolateTick(mApplication->getRenderTime());
	}
}

/*********************************
*		SHAPE
**********************************/
void Game::addShape(ByteBuffer* byteBuffer)
{
	Shape* shape = new Shape(mApplication,byteBuffer,false);  //you should just need to call this...

	//ability
	shape->addAbility(new AbilityRotation(shape));
	shape->addAbility(new AbilityMove(shape));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector->push_back(shape);
	mShapeGhostVector->push_back(shape->mGhost);
}

void Game::removeShape(ByteBuffer* byteBuffer)
{
	//get the index which is the mIndex...
	int index = byteBuffer->ReadByte();
	
	//let's loop so we can also get index of vector where shape resides so we can erase it as well as deleting other parts of shape.
	for (unsigned int i = 0; i < mShapeVector->size(); i++)
	{
		if (mShapeVector->at(i)->mIndex == index)
		{
			Shape* shape = mShapeVector->at(i);
			
			//delete objectTitles
 			delete shape->mGhost->mObjectTitle;
 			delete shape->mObjectTitle;

			//delete entities by name
 			mApplication->getSceneManager()->destroyEntity(shape->mGhost->mName);
 			mApplication->getSceneManager()->destroyEntity(shape->mName);

			//erase shapes from vectors
			mShapeVector->erase(mShapeVector->begin()+i);
			mShapeGhostVector->erase(mShapeGhostVector->begin()+i);
		}
	}
}

/*
        if (mShapeVector)
        {
                for (unsigned int i = 0; i < mShapeVector->size(); i++)
                {
                        delete mShapeVector->at(i);
                        delete mShapeGhostVector->at(i);
                }
        }
*/

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

void Game::createScene()
{
        mApplication->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

        mPointLight = mApplication->mSceneMgr->createLight("pointLight");
        mPointLight->setType(Ogre::Light::LT_POINT);
        mPointLight->setPosition(Ogre::Vector3(250, 150, 250));
        mPointLight->setDiffuseColour(Ogre::ColourValue::White);
        mPointLight->setSpecularColour(Ogre::ColourValue::White);

// create a floor mesh resource

        MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
               Plane(Vector3::UNIT_Y, -10), 100, 50, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

                // create a floor entity, give it a material, and place it at the origin
        mFloor = mApplication->mSceneMgr->createEntity("Floor", "floor");
        mFloor->setMaterialName("Examples/Rockwall");
        mFloor->setCastShadows(false);
        //mApplication->mSceneMgr->getRootSceneNode()->attachObject(mFloor);

	mFloorNode = mApplication->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mFloorNode->attachObject(mFloor);

	mFloorNode->setPosition(50,0,25);
}

/*********************************
		Network
**********************************/

void Game::checkByteBuffer(ByteBuffer* byteBuffer)
{
	byteBuffer->BeginReading();

        int type = byteBuffer->ReadByte();

        switch(type)
        {
        	case mMessageAddShape:
                	addShape(byteBuffer);
                        break;

                case mMessageRemoveShape:
                 	removeShape(byteBuffer);
                        break;

                case mMessageFrame:
                       	if (!mApplication->mNetwork->mIgnorePacket)
			{
                        	readServerTick(byteBuffer);
                        }
                        break;
	}
}

void Game::readServerTick(ByteBuffer* byteBuffer)
{
        // Skip sequences
        short sequence = byteBuffer->ReadShort();
        mFrameTimeServer = byteBuffer->ReadByte();
        //LogString("mFrameTimeServer:%f",mFrameTimeServer);

        while (byteBuffer->getReadCount() <= byteBuffer->GetSize())
        {
                mApplication->mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

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

void Game::sendByteBuffer()
{
	mRunNetworkTime += mApplication->getRenderTime() * 1000.0f;

    	// Framerate is too high
    	if(mRunNetworkTime > (1000 / 60))
    	{
        	// Build delta-compressed move command
        	int flags = 0;

        	//if key has not been changed return having done nothing 
        	if(mKeyLast != mKeyCurrent)
        	{
                	flags |= mMessageKey;
        	}
		else
		{
			return;
		}

		//create byteBuffer
		ByteBuffer* byteBuffer = new ByteBuffer();

		//WRITE: type
		byteBuffer->WriteByte(mMessageFrame);

                //WRITE: key
               	byteBuffer->WriteByte(mKeyCurrent);

        	//set 'last' commands for diff
        	mKeyLast = mKeyCurrent;

        	// Send the packet
        	mApplication->mNetwork->send(byteBuffer);

		mRunNetworkTime = 0.0f;
    	}
}




/*************************************************
*
*   OGRE_SPECIFIC
*
**************************************************



/***************************************
*			INPUT
******************************************/


void Game::processInput()
{
	mKeyCurrent = 0;

	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_I)) // Forward
   	{
		mKeyCurrent |= mKeyUp;
   	}

   	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_K)) // Backward
   	{
		mKeyCurrent |= mKeyDown;
   	}

	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_J)) // Left
   	{
		mKeyCurrent |= mKeyLeft;
   	}

   	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_L)) // Right
   	{
		mKeyCurrent |= mKeyRight;
   	}

	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_Z)) // Rotate -Yaw(counter-clockwise)
   	{
		mKeyCurrent |= mKeyCounterClockwise;
   	}

   	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_X)) // Right + Yaw(clockwise)
   	{
		mKeyCurrent |= mKeyClockwise;
   	}
}
