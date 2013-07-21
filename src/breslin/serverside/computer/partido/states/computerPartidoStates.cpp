#include "computerPartidoStates.h"

//computer states
#include "../../states/computerStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//computerPartido
#include "../computerPartido.h"

#include "../../../shape/shape.h"
#include "../../../client/robust/clientRobust.h"
#include "../../../game/game.h"
#include "../../../avoid/avoid.h"
#include "../../../seek/seek.h"

//rand
#include <stdlib.h>
#include <time.h>

#define MAX_RUN_SPEED 1.66           // character running speed in units per second


/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_COMPUTER_PARTIDO* GLOBAL_COMPUTER_PARTIDO::Instance()
{
  static GLOBAL_COMPUTER_PARTIDO instance;
  return &instance;
}
void GLOBAL_COMPUTER_PARTIDO::enter(ComputerPartido* computerPartido)
{
}
void GLOBAL_COMPUTER_PARTIDO::execute(ComputerPartido* computer)
{
	if (computer->mTactic == 0 && computer->mShape->mClient->mLoggedIn == false && computer->mComputerPartidoStateMachine->currentState() != COMPUTER_CONTROLLED_PARTIDO::Instance())
	{
                computer->mComputerPartidoStateMachine->changeState(COMPUTER_CONTROLLED_PARTIDO::Instance());
	}
}
void GLOBAL_COMPUTER_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool GLOBAL_COMPUTER_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}


/*****************************************
*******       COMPUTER    ******************
****************************************/
/*
agressive-no avoid, seek closest 
scared-no seek, avoid all

preciseAttack-seek one, avoid all else
sloppyAttack-seek one, avoid no one


*/

/*****************************************
*******      COMPUTER CONTROLLED   ******************
****************************************/
/*   COMPUTER_CONTROLLED_PARTIDO   */

COMPUTER_CONTROLLED_PARTIDO* COMPUTER_CONTROLLED_PARTIDO::Instance()
{
  static COMPUTER_CONTROLLED_PARTIDO instance;
  return &instance;
}

void COMPUTER_CONTROLLED_PARTIDO::enter(ComputerPartido* computer)
{
	LogString("COMPUTER_CONTROLLED_PARTIDO");
	if (computer->mShape->mAvoid)
        {
                if (computer->mShape->mClient->db_id == 5)
                {
                        for (int i = 0; i < computer->mShape->mGame->mShapeVector.size(); i++)
                        {
                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 4)
                                {
                                        computer->mShape->mAvoid->addAvoidShape(computer->mShape->mGame->mShapeVector.at(i));
                                }

                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 3)
                                {
                                        computer->mShape->mAvoid->addAvoidShape(computer->mShape->mGame->mShapeVector.at(i));
                                }
                        }
                }
        }

}

void COMPUTER_CONTROLLED_PARTIDO::execute(ComputerPartido* computer)
{
       if (computer->mShape->mSeek)
        {
                if (computer->mShape->mClient->db_id == 5)
                {
                        for (int i = 0; i < computer->mShape->mGame->mShapeVector.size(); i++)
                        {
                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 2)
                                {
                                        computer->mShape->mSeek->setSeekShape(computer->mShape->mGame->mShapeVector.at(i));
                                }
                        }
                }
        }

        //is this human controlled?
        if (computer->mShape->mClient->mLoggedIn)
        {
                computer->mComputerPartidoStateMachine->changeState(HUMAN_CONTROLLED_PARTIDO::Instance());
        }

}

void COMPUTER_CONTROLLED_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool COMPUTER_CONTROLLED_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}

/*****************************************
*******      HUMAN     ******************
****************************************/
HUMAN_CONTROLLED_PARTIDO* HUMAN_CONTROLLED_PARTIDO::Instance()
{
	static HUMAN_CONTROLLED_PARTIDO instance;
	return &instance;
}

void HUMAN_CONTROLLED_PARTIDO::enter(ComputerPartido* computerPartido)
{
	LogString("HUMAN_CONTROLLED_PARTIDO");
}

void HUMAN_CONTROLLED_PARTIDO::execute(ComputerPartido* computer)
{
        if (!computer->mShape->mClient->mLoggedIn)
        {
                computer->mComputerPartidoStateMachine->changeState(COMPUTER_CONTROLLED_PARTIDO::Instance());
        }
}

void HUMAN_CONTROLLED_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool HUMAN_CONTROLLED_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}

