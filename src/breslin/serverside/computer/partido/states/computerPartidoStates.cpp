#include "computerPartidoStates.h"

//computer states
#include "../../states/computerStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//computerPartido
#include "../computerPartido.h"

#include "../../../shape/partido/shapePartido.h"
#include "../../../client/robust/clientRobust.h"
#include "../../../game/partido/gamePartido.h"
#include "../../../avoid/avoid.h"
#include "../../../seek/seek.h"
#include "../../../shape/shape.h"
#include "../../../seek/states/seekStates.h"

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
        //is this human controlled?
        if (computer->mShape->mClient->mLoggedIn)
        {
		if (computer->mComputerPartidoStateMachine->currentState() != HUMAN_CONTROLLED_PARTIDO::Instance())
                computer->mComputerPartidoStateMachine->changeState(HUMAN_CONTROLLED_PARTIDO::Instance());
        }
	else
	{
		if (computer->mTactic == 0 && computer->mComputerPartidoStateMachine->currentState() != COMPUTER_CONTROLLED_PARTIDO::Instance())
		{
                	computer->mComputerPartidoStateMachine->changeState(COMPUTER_CONTROLLED_PARTIDO::Instance());
		}

		if (computer->mTactic == 1 && computer->mComputerPartidoStateMachine->currentState() != BEZERKER_PARTIDO::Instance())
		{
                	computer->mComputerPartidoStateMachine->changeState(BEZERKER_PARTIDO::Instance());
		}
		if (computer->mTactic == 2 && computer->mComputerPartidoStateMachine->currentState() != SCARED_PARTIDO::Instance())
		{
                	computer->mComputerPartidoStateMachine->changeState(SCARED_PARTIDO::Instance());
		}
		if (computer->mTactic == 3 && computer->mComputerPartidoStateMachine->currentState() != SNIPER_PARTIDO::Instance())
		{
                	computer->mComputerPartidoStateMachine->changeState(SNIPER_PARTIDO::Instance());
		}
		if (computer->mTactic == 4 && computer->mComputerPartidoStateMachine->currentState() != SLOPPY_PARTIDO::Instance())
		{
                	computer->mComputerPartidoStateMachine->changeState(SLOPPY_PARTIDO::Instance());
		}
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
bezerker-no avoid, seek closest 
scared-no seek, avoid all

sniper-seek one, avoid all else
sloppy-seek one, avoid no one


*/

/*****************************************
*******      BEZERKER_PARTIDO   ******************
****************************************/

BEZERKER_PARTIDO* BEZERKER_PARTIDO::Instance()
{
  static BEZERKER_PARTIDO instance;
  return &instance;
}

void BEZERKER_PARTIDO::enter(ComputerPartido* computer)
{
        LogString("BEZERKER_PARTIDO:%d",computer->mShape->mClient->db_id);

	//let's reset all seeks and avoids
	computer->mShape->mAvoid->mAvoidVector.clear();
	computer->mShape->mSeek->setSeekShape(NULL);
	computer->mShape->mSeek->setDestinationShape(NULL);

	//find closest shape that you have not just battled then seek it.......		
	ShapePartido* shape = computer->getClosestBattleShape();
       	if (computer->mShape->mSeek)
        {
        	computer->mShape->mSeek->setDestinationShape((Shape*)shape);
        }
}

void BEZERKER_PARTIDO::execute(ComputerPartido* computer)
{
	//if you found your prey go back to COMPUTER_CONTROLLED TO get reassigned
	if (computer->mShape->mSeek->mStateMachine->currentState() == REACHED_DESTINATION::Instance())
	{
		computer->mComputerPartidoStateMachine->changeState(COMPUTER_CONTROLLED_PARTIDO::Instance());
	}
}

void BEZERKER_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool BEZERKER_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}

/*****************************************
*******      SCARED_PARTIDO   ******************
****************************************/

SCARED_PARTIDO* SCARED_PARTIDO::Instance()
{
  static SCARED_PARTIDO instance;
  return &instance;
}

void SCARED_PARTIDO::enter(ComputerPartido* computer)
{
        LogString("SCARED_PARTIDO_PARTIDO:%d",computer->mShape->mClient->db_id);

	//let's reset all seeks and avoids
	computer->mShape->mAvoid->mAvoidVector.clear();
	computer->mShape->mSeek->setSeekShape(NULL);
	computer->mShape->mSeek->setDestinationShape(NULL);

	for (int i = 0; i < computer->mShapePartido->mGamePartido->mShapePartidoVector.size(); i++)
	{
		if (computer->mShapePartido->mGamePartido->mShapePartidoVector.at(i) == computer->mShapePartido)
		{
			continue;
		}
		
		computer->mShapePartido->mAvoid->addAvoidShape(computer->mShapePartido->mGamePartido->mShapePartidoVector.at(i));					
	}
}

void SCARED_PARTIDO::execute(ComputerPartido* computer)
{

}

void SCARED_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool SCARED_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}

/*****************************************
*******      SNIPER_PARTIDO   ******************
****************************************/

SNIPER_PARTIDO* SNIPER_PARTIDO::Instance()
{
  static SNIPER_PARTIDO instance;
  return &instance;
}

void SNIPER_PARTIDO::enter(ComputerPartido* computer)
{
        LogString("SNIPER_PARTIDO:%d",computer->mShape->mClient->db_id);

	//let's reset all seeks and avoids
	computer->mShape->mAvoid->mAvoidVector.clear();
	computer->mShape->mSeek->setSeekShape(NULL);
	computer->mShape->mSeek->setDestinationShape(NULL);

	//pick a shape at random to snipe
	int numberOfShapes = computer->mShapePartido->mGamePartido->mShapePartidoVector.size(); 
	computer->mShape->mSeek->setDestinationShape(NULL);
	computer->mShape->mSeek->setSeekShape(NULL);

	while (!computer->mShape->mSeek->getDestinationShape())
	{
		int shapeElementToSnipe  = rand() % numberOfShapes;
        	if (computer->mShape == computer->mShapePartido->mGamePartido->mShapePartidoVector.at(shapeElementToSnipe))
		{
			continue;
		}
		else
		{
			computer->mShape->mSeek->setDestinationShape((Shape*)computer->mShapePartido->mGamePartido->mShapePartidoVector.at(shapeElementToSnipe));
		}
	}	
	
		
}

void SNIPER_PARTIDO::execute(ComputerPartido* computer)
{
	//if you found your prey go back to COMPUTER_CONTROLLED TO get reassigned
	if (computer->mShape->mSeek->mStateMachine->currentState() == REACHED_DESTINATION::Instance())
	{
		computer->mComputerPartidoStateMachine->changeState(COMPUTER_CONTROLLED_PARTIDO::Instance());
	}
}

void SNIPER_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool SNIPER_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}

/*****************************************
*******      SLOPPY_PARTIDO   ******************
****************************************/

SLOPPY_PARTIDO* SLOPPY_PARTIDO::Instance()
{
  static SLOPPY_PARTIDO instance;
  return &instance;
}

void SLOPPY_PARTIDO::enter(ComputerPartido* computer)
{
        LogString("SLOPPY_PARTIDO:%d",computer->mShape->mClient->db_id);

	//let's reset all seeks and avoids
	computer->mShape->mAvoid->mAvoidVector.clear();
	computer->mShape->mSeek->setSeekShape(NULL);
	computer->mShape->mSeek->setDestinationShape(NULL);

	for (int i = 0; i < computer->mShapePartido->mGamePartido->mShapePartidoVector.size(); i++)
        {
                if (computer->mShapePartido->mGamePartido->mShapePartidoVector.at(i) == computer->mShapePartido)
                {
                        continue;
                }

                computer->mShapePartido->mAvoid->addAvoidShape(computer->mShapePartido->mGamePartido->mShapePartidoVector.at(i));
        }

}

void SLOPPY_PARTIDO::execute(ComputerPartido* computer)
{
}

void SLOPPY_PARTIDO::exit(ComputerPartido* computerPartido)
{
}
bool SLOPPY_PARTIDO::onLetter(ComputerPartido* computerPartido, Letter* letter)
{
        return true;
}


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
	LogString("COMPUTER_CONTROLLED_PARTIDO:%d",computer->mShape->mClient->db_id);

	//let's reset all seeks and avoids
	computer->mShape->mAvoid->mAvoidVector.clear();
	computer->mShape->mSeek->setSeekShape(NULL);
	computer->mShape->mSeek->setDestinationShape(NULL);

	//let's give you a new random tactic
	int tactic = rand() % 4;
	tactic++;
	computer->mTactic = tactic; 
}

void COMPUTER_CONTROLLED_PARTIDO::execute(ComputerPartido* computer)
{
	


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

void HUMAN_CONTROLLED_PARTIDO::enter(ComputerPartido* computer)
{
	LogString("HUMAN_CONTROLLED_PARTIDO:%d",computer->mShape->mClient->db_id);
	//let's reset all seeks and avoids
	computer->mShape->mAvoid->mAvoidVector.clear();
	computer->mShape->mSeek->setSeekShape(NULL);
	computer->mShape->mSeek->setDestinationShape(NULL);
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

