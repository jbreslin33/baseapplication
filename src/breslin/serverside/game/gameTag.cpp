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
	for(int i = 0; i < 1; i++)
	{                 
		Vector3D* position = new Vector3D();
		position->x = 5.0f;
		position->y = 0.0f;
		position->z = 2.0f * i;

		Shape* shape = new ShapeTag(getOpenIndex(),this,0,new Vector3D(),new Vector3D(),new Vector3D(),
			mRoot,true,true,.66f,1,true); 

		mItShape = mShapeVector.at(0);
	}
}
void GameTag::collision(Shape* shape1, Shape* shape2)
{
	Game::collision(shape1,shape2);
	
	//let's make someone it
	if (shape1 == mItShape)
	{
		mItShape = shape2;
	}
	else if (shape2 == mItShape)
	{
		mItShape = shape1;
	}
}


void GameTag::storeCommands(Shape* shape)
{
	Game::storeCommands(shape);
}