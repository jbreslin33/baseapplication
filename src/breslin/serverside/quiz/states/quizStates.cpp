//parent
#include "quizStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//quiz
#include "../quiz.h"

//client
#include "../../client/robust/partido/clientPartido.h"

//combatant
#include "../../combatant/combatant.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_QUIZ* GLOBAL_QUIZ::Instance()
{
  static GLOBAL_QUIZ instance;
  return &instance;
}
void GLOBAL_QUIZ::enter(Quiz* quiz)
{
}
void GLOBAL_QUIZ::execute(Quiz* quiz)
{

}
void GLOBAL_QUIZ::exit(Quiz* quiz)
{
}
bool GLOBAL_QUIZ::onLetter(Quiz* quiz, Letter* letter)
{
        return true;
}

/*****************************************
	INIT_QUIZ
****************************************/
INIT_QUIZ* INIT_QUIZ::Instance()
{
	static INIT_QUIZ instance;
	return &instance;
}
void INIT_QUIZ::enter(Quiz* quiz)
{
}
void INIT_QUIZ::execute(Quiz* quiz)
{
	if (quiz->mStateMachine->currentState() == WAITING_FOR_ANSWER::Instance());
	
}
void INIT_QUIZ::exit(Quiz* quiz)
{
}
bool INIT_QUIZ::onLetter(Quiz* quiz, Letter* letter)
{
        return true;
}


/*****************************************
	SENDING_QUESTING
****************************************/
SENDING_QUESTION* SENDING_QUESTION::Instance()
{
  static SENDING_QUESTION instance;
  return &instance;
}
void SENDING_QUESTION::enter(Quiz* quiz)
{
}
void SENDING_QUESTION::execute(Quiz* quiz)
{
	if (quiz->mCombatant->mClientPartido->mLoggedIn)
        {
                if (quiz->mWaitingForAnswer == false)
                {
                        //quiz->sendQuestion(clientPartido->getNewQuestionID());
                        quiz->mStateMachine->changeState(WAITING_FOR_ANSWER::Instance());
                }
        }
        else //computer so just go right to wating...
        {
                quiz->mStateMachine->changeState(WAITING_FOR_ANSWER::Instance());
        }

}
void SENDING_QUESTION::exit(Quiz* quiz)
{
}
bool SENDING_QUESTION::onLetter(Quiz* quiz, Letter* letter)
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
void WAITING_FOR_ANSWER::enter(Quiz* quiz)
{
/*
        clientPartido->mComputerAskedTime = clientPartido->mServer->mGameTime;

        int randomAnswerTime = rand() % 3000;
        clientPartido->mComputerAnswerTime = randomAnswerTime;

        clientPartido->mWaitingForAnswer = true;
*/

}
void WAITING_FOR_ANSWER::execute(Quiz* quiz)
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
void WAITING_FOR_ANSWER::exit(Quiz* quiz)
{
}
bool WAITING_FOR_ANSWER::onLetter(Quiz* quiz, Letter* letter)
{
        return true;
}

/*****************************************
	OVER_QUIZ
****************************************/
OVER_QUIZ* OVER_QUIZ::Instance()
{
	static OVER_QUIZ instance;
	return &instance;
}
void OVER_QUIZ::enter(Quiz* quiz)
{
}
void OVER_QUIZ::execute(Quiz* quiz)
{
}
void OVER_QUIZ::exit(Quiz* quiz)
{
}
bool OVER_QUIZ::onLetter(Quiz* quiz, Letter* letter)
{
        return true;
}
