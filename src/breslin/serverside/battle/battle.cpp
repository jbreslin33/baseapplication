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
  
	//add shapes to battle shapeVector
        for (unsigned int i = 0; i < shapeVector.size(); i++)
        {
                mShapeVector.push_back(shapeVector.at(i));
        }

        for (unsigned int i = 0; i < shapeVector.size(); i++)
	{
		if (mShapeVector.at(i)->mClient)
		{
			LogString("id:%d",mShapeVector.at(i)->mClient->mClientID);
		}
	}
}

Battle::~Battle()
{
}

void Battle::processUpdate()
{
	//this is where you should send questions....
	//select * from questions_attempts limit 10;
}
