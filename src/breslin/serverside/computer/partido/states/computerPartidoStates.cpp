//parent
#include "computerPartidoStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//rand
#include <stdlib.h>
#include <time.h>

#define MAX_RUN_SPEED 1.66           // character running speed in units per second


/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalComputerPartido* GlobalComputerPartido::Instance()
{
  static GlobalComputerPartido instance;
  return &instance;
}
void GlobalComputerPartido::enter(ComputerPartido* computerPartido)
{
}
void GlobalComputerPartido::execute(ComputerPartido* computerPartido)
{

}
void GlobalComputerPartido::exit(ComputerPartido* computerPartido)
{
}
bool GlobalComputerPartido::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}


/*****************************************
*******       COMPUTER    ******************
****************************************/

/*****************************************
*******      RANDOM COMPUTER    ******************
****************************************/
/*   ComputerPartido_Controlled   */

/*
ComputerPartido_Controlled* ComputerPartido_Controlled::Instance()
{
  static ComputerPartido_Controlled instance;
  return &instance;
}

void ComputerPartido_Controlled::enter(ComputerPartido* computerPartido)
{

}

void ComputerPartido_Controlled::execute(ComputerPartido* computerPartido)
{
	if (computerPartido->mShape->mSeek)
	{
		if (computerPartido->mShape->mClient->db_id == 5)
		{
			for (int i = 0; i < computerPartido->mShape->mGame->mShapeVector.size(); i++)
			{
				if (computerPartido->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 4)
				{
					computerPartido->mShape->mSeek->setSeekShape(computerPartido->mShape->mGame->mShapeVector.at(i));	
				}
			}
		}
	}

	//is this human controlled?
	if (computerPartido->mShape->mClient->mConnectionState == 1)
	{
		computerPartido->mStateMachine->changeState(Human_Controlled::Instance());
	}
}

void ComputerPartido_Controlled::exit(ComputerPartido* computerPartido)
{
}
bool ComputerPartido_Controlled::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}

*/

/*****************************************
*******      RANDOM COMPUTER    ******************
****************************************/
/*
Human_Controlled* Human_Controlled::Instance()
{
	static Human_Controlled instance;
	return &instance;
}

void Human_Controlled::enter(ComputerPartido* computerPartido)
{
}

void Human_Controlled::execute(ComputerPartido* computerPartido)
{
}

void Human_Controlled::exit(ComputerPartido* computerPartido)
{
}
bool Human_Controlled::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}
*/

