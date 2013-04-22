#include "battle.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shape.h"

Battle::Battle(Game* game, Shape* shape1, Shape* shape2)
{
	mOver = false;
}

Battle::~Battle()
{
}

void Battle::processUpdate()
{
	//this is where you should send questions....

}
