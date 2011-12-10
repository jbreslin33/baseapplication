//header
#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//applicationBreslin
#include "../application/applicationBreslin.h"

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

	mStateMachine = new StateMachine();
	mGameGlobal = new GameGlobal(this);
	mGameInitialize = new GameInitialize(this);
	mGamePlay = new GamePlay(this);
	mGamePause = new GamePause(this);
	
	mStateMachine->setGlobalState(mGameGlobal);
	mStateMachine->changeState(mGamePlay);
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
void Game::run()
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
   
	mMillisecondsCurrent = (int) (mApplicationBreslin->mFrameTime * 1000);
}
