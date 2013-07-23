/***
these states are always on...as their is always a gamePartido..and these clients are in it. it really should handle the mechanics of quiz... 

*/
//parent
#include "clientPartidoStates.h"

//log
#include "../../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../../fsm/stateMachine.h"

//ability
#include "../clientPartido.h"

//server
#include "../../../../server/partido/serverPartido.h"

//shapePartido
#include "../../../../shape/partido/shapePartido.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_CLIENT_PARTIDO* GLOBAL_CLIENT_PARTIDO::Instance()
{
  static GLOBAL_CLIENT_PARTIDO instance;
  return &instance;
}
void GLOBAL_CLIENT_PARTIDO::enter(ClientPartido* clientPartido)
{
}
void GLOBAL_CLIENT_PARTIDO::execute(ClientPartido* clientPartido)
{

}
void GLOBAL_CLIENT_PARTIDO::exit(ClientPartido* clientPartido)
{
}
bool GLOBAL_CLIENT_PARTIDO::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;
}


/*****************************************
*******       CLIENT PARTIDO STATES    ******************       
****************************************/

/*****************************************
                GAME_PARTIDO_MODE               
****************************************/
GAME_PARTIDO_MODE* GAME_PARTIDO_MODE::Instance()
{
  static GAME_PARTIDO_MODE instance;
  return &instance;
}
void GAME_PARTIDO_MODE::enter(ClientPartido* clientPartido)
{
        //LogString("GAME_PARTIDO_MODE:%d",clientPartido->db_id);
}
void GAME_PARTIDO_MODE::execute(ClientPartido* clientPartido)
{
  	if (clientPartido->mShapePartido->mOpponent)
        {
                clientPartido->mClientPartidoStateMachine->changeState(BATTLE::Instance());
        }
}
void GAME_PARTIDO_MODE::exit(ClientPartido* clientPartido)
{
}
bool GAME_PARTIDO_MODE::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false; 
}
/***************************************
       	BATTLE
****************************************/
BATTLE* BATTLE::Instance()
{
  static BATTLE instance;
  return &instance;
}
void BATTLE::enter(ClientPartido* clientPartido)
{
        //LogString("BATTLE:%d",clientPartido->db_id);
	if (clientPartido->mLoggedIn)
        {
                clientPartido->sendBattleStart();
        }
	clientPartido->mKey = 0;
        clientPartido->mBattleScore = 0;
        clientPartido->mWaitingForAnswer = false;
        clientPartido->mQuestionString = "";
        clientPartido->mShapePartido->mCollidable = false;
}
void BATTLE::execute(ClientPartido* clientPartido)
{
  	if (!clientPartido->mShapePartido->mOpponent)
        {
                clientPartido->mClientPartidoStateMachine->changeState(GAME_PARTIDO_MODE::Instance());
        }
}
void BATTLE::exit(ClientPartido* clientPartido)
{
}
bool BATTLE::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;
}


/*****************************************
****        BATTLE STATES   ********   
****************************************/


/****************************************
	BATTLE_OFF	
****************************************/
BATTLE_OFF* BATTLE_OFF::Instance()
{
  static BATTLE_OFF instance;
  return &instance;
}
void BATTLE_OFF::enter(ClientPartido* clientPartido)
{
        //LogString("BATTLE_OFF:%d",clientPartido->db_id);
}
void BATTLE_OFF::execute(ClientPartido* clientPartido)
{
	if (clientPartido->mShapePartido)
	{
		if (!clientPartido->mWaitingForAnswer && clientPartido->mShapePartido->mOpponent)
		{
                	clientPartido->mBattleStateMachine->changeState(SENDING_QUESTION::Instance());
		}
	}
}
void BATTLE_OFF::exit(ClientPartido* clientPartido)
{
}

bool BATTLE_OFF::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;  
}


/*****************************************
        SENDING_QUESTION
****************************************/
SENDING_QUESTION* SENDING_QUESTION::Instance()
{
  static SENDING_QUESTION instance;
  return &instance;
}
void SENDING_QUESTION::enter(ClientPartido* clientPartido)
{
        //LogString("SENDING_QUESTION:%d",clientPartido->db_id);
}
void SENDING_QUESTION::execute(ClientPartido* clientPartido)
{
  	if (!clientPartido->mShapePartido->mOpponent)
        {
                clientPartido->mBattleStateMachine->changeState(BATTLE_OFF::Instance());
        }

        if (clientPartido->mLoggedIn)
        {
                if (clientPartido->mShapePartido)
                {
                        if (clientPartido->mShapePartido->mOpponent && clientPartido->mWaitingForAnswer == false)
                        {
                                clientPartido->sendQuestion(clientPartido->getNewQuestionID());
                		clientPartido->mBattleStateMachine->changeState(WAITING_FOR_ANSWER::Instance());
                        }
                }
        }
	else //computer so just go right to wating...
	{
               	clientPartido->mBattleStateMachine->changeState(WAITING_FOR_ANSWER::Instance());
	}
}
void SENDING_QUESTION::exit(ClientPartido* clientPartido)
{
}
bool SENDING_QUESTION::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false; 
}


/*****************************************
        WAITING FOR ANSWER       
****************************************/
WAITING_FOR_ANSWER* WAITING_FOR_ANSWER::Instance()
{
  static WAITING_FOR_ANSWER instance;
  return &instance; 
} 
void WAITING_FOR_ANSWER::enter(ClientPartido* clientPartido)
{
        //LogString("WAITING_FOR_ANSWER:%d",clientPartido->db_id);

	clientPartido->mComputerAskedTime = clientPartido->mServer->mGameTime;	

 	int randomNumber = rand() % 1000;
 	clientPartido->mComputerAnswerTime = 1500 + randomNumber;

        clientPartido->mWaitingForAnswer = true;
}       
void WAITING_FOR_ANSWER::execute(ClientPartido* clientPartido)
{
  	if (!clientPartido->mShapePartido->mOpponent)
        {
                clientPartido->mBattleStateMachine->changeState(BATTLE_OFF::Instance());
        }
	
	if (!clientPartido->mWaitingForAnswer && clientPartido->mShapePartido->mOpponent)
	{
        	clientPartido->mBattleStateMachine->changeState(SENDING_QUESTION::Instance());
	}
	
	//mServerPartido->mAnswerVector.at(mQuestionID)
	if (!clientPartido->mLoggedIn) //send to readAnswer(int,string)
	{
		if (clientPartido->mComputerAskedTime + clientPartido->mComputerAnswerTime < clientPartido->mServer->mGameTime)
		{		
			clientPartido->readAnswer(clientPartido->mComputerAnswerTime,clientPartido->mServerPartido->mAnswerVector.at(clientPartido->mQuestionID));
		}
	}
	
}
void WAITING_FOR_ANSWER::exit(ClientPartido* clientPartido)
{

}
bool WAITING_FOR_ANSWER::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;   
}
