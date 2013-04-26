#include "battle.h"

//client
#include "../client/clientPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shape.h"

Battle::Battle(Game* game, std::vector<Shape*> shapeVector)
{
	mOver = false;
/*
	mShapeVector.push_back(shape1);
	mShapeVector.push_back(shape2);

	if (shape1->mClient)
	{
		LogString("client in battle:%d",shape1->mClient->mClientID);
		LogString("client in battle:%d",shape2->mClient->mClientID);
	}
*/
}

Battle::~Battle()
{
}

void Battle::processUpdate()
{
	//this is where you should send questions....

}
