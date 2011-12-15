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

GameTag::GameTag()
{
	LogString("Hosting GameTag");
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
	for(int i = 0; i < 2; i++)
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


void GameTag::storeCommands(Shape* shape)
{
	Game::storeCommands(shape);
}