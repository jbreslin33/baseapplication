//parent
#include "combatantStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//combatant
#include "../combatant.h"

//client
#include "../../client/robust/partido/clientPartido.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_COMBATANT* GLOBAL_COMBATANT::Instance()
{
  static GLOBAL_COMBATANT instance;
  return &instance;
}
void GLOBAL_COMBATANT::enter(Combatant* combatant)
{
}
void GLOBAL_COMBATANT::execute(Combatant* combatant)
{

}
void GLOBAL_COMBATANT::exit(Combatant* combatant)
{
}
bool GLOBAL_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

/*****************************************
	INIT_COMBATANT
****************************************/
INIT_COMBATANT* INIT_COMBATANT::Instance()
{
	static INIT_COMBATANT instance;
	return &instance;
}
void INIT_COMBATANT::enter(Combatant* combatant)
{
}
void INIT_COMBATANT::execute(Combatant* combatant)
{
	//we are ready to go if we have a foe
	if (combatant->mFoe)
	{
/*
		ClientPartido* client = combatant->mClientPartido;
        	client->mKey = 0;

        	combatant->mScore = 0;
        	combatant->mClientPartido->mQuizmWaitingForAnswer = false;
        	combatant->mQuestionString = "";
        	client->mShape->mCollidable = false; //no more collisions while in battle
	
		//let internet client know to start a battle
		combatant->mClientPartido->sendSimpleMessage(mServerPartido->mMessageBattleStart);
               
		//change to sending question even it your a computer          
		clientPartido->mBattleStateMachine->changeState(SENDING_QUESTION::Instance());
*/
	}
/*
  	if (clientPartido->mShapePartido)
        {
                if (!clientPartido->mWaitingForAnswer && clientPartido->mShapePartido->mOpponent)
                {
                        clientPartido->mBattleStateMachine->changeState(Sending_Question::Instance());
                }
        }
*/
	
//	combatant->mClient1->mCombatant = combatant;	
//	combatant->mClient2->mCombatant = combatant;	
/*
	if (mOpponent == NULL && mOpponentLast != shape)
        {
                if (mClientPartido)
                {
                        mOpponent = (ShapePartido*)shape;
                }
        }

        //reset
        mCollisionTimeoutCounter = mCollisionTimeout;
        mCollidable = false;
*/
}
void INIT_COMBATANT::exit(Combatant* combatant)
{
}
bool INIT_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}


/*****************************************
	SENDING_QUESTION
****************************************/
SENDING_QUESTION* SENDING_QUESTION::Instance()
{
  static SENDING_QUESTION instance;
  return &instance;
}
void SENDING_QUESTION::enter(Combatant* combatant)
{
}
void SENDING_QUESTION::execute(Combatant* combatant)
{
/*
        if (combatant->mClientPartido->mLoggedIn)
        {
        	if (combatant->mWaitingForAnswer == false)
                {
                        combatant->sendQuestion(clientPartido->getNewQuestionID());
                	combatant->mStateMachine->changeState(WAITING_FOR_ANSWER::Instance());
                }
        }
        else //computer so just go right to wating...
        {
                mCombatant->mStateMachine->changeState(WAITING_FOR_ANSWER::Instance());
        }
*/
}
void SENDING_QUESTION::exit(Combatant* combatant)
{
}
bool SENDING_QUESTION::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

/*****************************************
	WAITING_FOR_ANSWER
****************************************/
WAITING_FOR_ANSWER* WAITING_FOR_ANSWER::Instance()
{
	static WAITING_FOR_ANSWER instance;
	return &instance;
}
void WAITING_FOR_ANSWER::enter(Combatant* combatant)
{
/*
	clientPartido->mComputerAskedTime = clientPartido->mServer->mGameTime;

        int randomAnswerTime = rand() % 3000;
        clientPartido->mComputerAnswerTime = randomAnswerTime;

        clientPartido->mWaitingForAnswer = true;
*/

}
void WAITING_FOR_ANSWER::execute(Combatant* combatant)
{
/*
	if (!clientPartido->mShapePartido->mOpponent)
        {
                //clientPartido->mBattleStateMachine->changeState(BATTLE_OFF::Instance());
        }

        if (!clientPartido->mWaitingForAnswer && clientPartido->mShapePartido->mOpponent)
        {
                //clientPartido->mBattleStateMachine->changeState(Sending_Question::Instance());
        }

        //mServerPartido->mAnswerVector.at(mQuestionID)
        if (!clientPartido->mLoggedIn) //send to readAnswer(int,string)
        {
                if (clientPartido->mComputerAskedTime + clientPartido->mComputerAnswerTime < clientPartido->mServer->mGameTime)
                {
                        clientPartido->readAnswer(clientPartido->mComputerAnswerTime,clientPartido->mServerPartido->mQuestionVector.at(clientPartido->mQuestionID)->answer);
                }
        }

*/
}
void WAITING_FOR_ANSWER::exit(Combatant* combatant)
{
}
bool WAITING_FOR_ANSWER::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

/*****************************************
             YIELD 
****************************************/
YIELD* YIELD::Instance()
{
        static YIELD instance;
        return &instance;
}
void YIELD::enter(Combatant* combatant)
{
 	//reset opponent pointers and vars for answers...
/*
        mBattleScore      = 0;

        mQuestionString   = "";

        //relieve your last opponents last opponent if it was you
        if (mShapePartido->mOpponentLast)
        {
                if (mShapePartido->mOpponentLast->mOpponentLast == mShapePartido)
                {
                        mShapePartido->mOpponentLast->mOpponentLast = NULL;
                }
        }

        //set your last opponent
        mShapePartido->mOpponentLast = mShapePartido->mOpponent;

        //clear you opponent
        mShapePartido->mOpponent = NULL;

        mShapePartido->mCollidable = true;
*/
}
void YIELD::execute(Combatant* combatant)
{
	//stand down and do nothing or change cleanup
}
void YIELD::exit(Combatant* combatant)
{
}
bool YIELD::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

