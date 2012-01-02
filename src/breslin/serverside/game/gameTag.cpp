//
#include "gameTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/serverTag.h"

//shape
#include "../shape/shapeTag.h"

//client
#include "../client/client.h"

//abilitys
#include "../ability/rotation/rotation.h"
#include "../ability/move/move.h"
#include "../ability/ai/ai.h"

//math
#include "../../math/vector3D.h"

//bounds
#include "../bounds/bounds.h"

GameTag::GameTag()
{
	LogString("Hosting GameTag");
	mBounds->a = new Vector3D(-40.0,0.0f,-40.0f);
	mBounds->b = new Vector3D(-40.0,0.0f,40.0f);
	mBounds->c = new Vector3D(40.0,0.0f,40.0f);
	mBounds->d = new Vector3D(40.0,0.0f,-40.0f);
}

GameTag::~GameTag()
{
}

void GameTag::createServer()
{
	LogString("createServer in GameTag breslin");
	mServerTag = new ServerTag(this,"", 30004);
	mServer = mServerTag;
}

void GameTag::createWorld()
{
	LogString("createWorld in GameTag");
	//ai guys, let's make them sinbads
	for(int i = 0; i < 12; i++)
	{                 
		Vector3D* position = new Vector3D();
		position->x = 1.5f * i;
		position->y = 0.0f;
		position->z = 1.5f * i;

		Shape* shape = new ShapeTag(getOpenIndex(),this,0,position,new Vector3D(),new Vector3D(),
			mRoot,true,true,.66f,1,true); 

		mShapeIt = shape;
		mShapeNoTagBack = shape;
	}
}
void GameTag::collision(Shape* shape1, Shape* shape2)
{
	Game::collision(shape1,shape2);
	
	//LogString("shape1:%d",shape1->mIndex);
	//LogString("shape2:%d",shape2->mIndex);
	//let's make someone it
	if (shape1 == mShapeIt && shape2 != mShapeNoTagBack)
	{
		mShapeIt = shape2;
		mShapeNoTagBack = shape1;

		//LogString("shape1:%d",shape1->mIndex);
		//LogString("shape2:%d",shape2->mIndex);
	}
	else if (shape2 == mShapeIt && shape1 != mShapeNoTagBack)
	{
		mShapeIt = shape1;
		mShapeNoTagBack = shape2;

		//LogString("shape1:%d",shape1->mIndex);
		//LogString("shape2:%d",shape2->mIndex);
	}
}
void GameTag::checkBounds(Shape* shape)
{
	if (shape->mSceneNode->getPosition().x < mBounds->a->x)
	{
		shape->mSceneNode->setPosition(mBounds->a->x, shape->mSceneNode->getPosition().y, shape->mSceneNode->getPosition().z); 
	}

	if (shape->mSceneNode->getPosition().x > mBounds->c->x)
	{
		shape->mSceneNode->setPosition(mBounds->c->x, shape->mSceneNode->getPosition().y, shape->mSceneNode->getPosition().z); 
	}


	if (shape->mSceneNode->getPosition().z < mBounds->a->z)
	{
		shape->mSceneNode->setPosition(shape->mSceneNode->getPosition().x, shape->mSceneNode->getPosition().y, mBounds->a->z); 
	}

	if (shape->mSceneNode->getPosition().z > mBounds->c->z)
	{
		shape->mSceneNode->setPosition(shape->mSceneNode->getPosition().x, shape->mSceneNode->getPosition().y, mBounds->c->z); 
	}

/*	
	if (shape->mSceneNode->getPosition().x > bounds)
	{
		shape->mSceneNode->setPosition(bounds, shape->mSceneNode->getPosition().y, shape->mSceneNode->getPosition().z);

	}
	if (shape->mSceneNode->getPosition().x < bounds * -1)
	{

		shape->mSceneNode->setPosition(bounds * -1, shape->mSceneNode->getPosition().y, shape->mSceneNode->getPosition().z);
	}
	
	if (shape->mSceneNode->getPosition().z > bounds)
	{

		shape->mSceneNode->setPosition(shape->mSceneNode->getPosition().x, shape->mSceneNode->getPosition().y, bounds);
	}

	if (shape->mSceneNode->getPosition().z < bounds * -1)
	{

		shape->mSceneNode->setPosition(shape->mSceneNode->getPosition().x, shape->mSceneNode->getPosition().y, bounds * -1);
	}
*/
}
void GameTag::storeCommands(Shape* shape)
{
	Game::storeCommands(shape);
}
