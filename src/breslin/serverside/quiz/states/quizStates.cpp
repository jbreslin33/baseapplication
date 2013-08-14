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
#include "../../combatant/states/combatantStates.h"

//test
#include "../../test/test.h"

//server
#include "../../server/partido/serverPartido.h"

//question
#include "../../question/question.h"

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
	LogString("INIT_QUIZ:%d",quiz->mCombatant->mClientPartido->id);	
}
void INIT_QUIZ::execute(Quiz* quiz)
{
	LogString("init");
	if (quiz->mCombatant->mStateMachine->currentState() == NORMAL_COMBATANT::Instance())
	{
        	quiz->mStateMachine->changeState(SENDING_QUESTION::Instance());
	}
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
	LogString("SENDING_QUESTION:%d",quiz->mCombatant->mClientPartido->id);	
}
void SENDING_QUESTION::execute(Quiz* quiz)
{
	if (quiz->mCombatant->mClientPartido->mLoggedIn)
        {
                if (quiz->mWaitingForAnswer == false)
                {
                        quiz->sendQuestion(quiz->mCombatant->mClientPartido->mTest->getNewQuestionID());
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
	LogString("WAITING_FOR_ANSWER:%d",quiz->mCombatant->mClientPartido->id);	
        quiz->mComputerAskedTime  = quiz->mCombatant->mClientPartido->mServerPartido->mGameTime;
        int randomAnswerTime      = rand() % 3000;
        quiz->mComputerAnswerTime = randomAnswerTime;
        quiz->mWaitingForAnswer   = true;
}

void WAITING_FOR_ANSWER::execute(Quiz* quiz)
{
	if (quiz->mCombatant->mStateMachine->currentState() == YIELD::Instance())
        {
                quiz->mStateMachine->changeState(OVER_QUIZ::Instance());
        }

        if (!quiz->mWaitingForAnswer)
        {
                quiz->mStateMachine->changeState(SENDING_QUESTION::Instance());
        }

	if (!quiz->mCombatant->mClientPartido->mLoggedIn)
        {
                if (quiz->mComputerAskedTime + quiz->mComputerAnswerTime < quiz->mCombatant->mClientPartido->mServerPartido->mGameTime)
                {
                        quiz->readAnswer(quiz->mComputerAnswerTime,quiz->mCombatant->mClientPartido->mServerPartido->mQuestionVector.at(quiz->mQuestionID)->answer);
                }
        }
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
	LogString("OVER_QUIZ:%d",quiz->mCombatant->mClientPartido->id);	
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
