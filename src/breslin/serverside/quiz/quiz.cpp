#include "quiz.h"
#include "states/quizStates.h"
#include "../client/robust/partido/clientPartido.h"
#include "../server/partido/serverPartido.h"
#include "../question/question.h"
#include "../network/network.h"
#include "../../utility/utility.h"
#include "../question/questionAttempts.h"
#include "../combatant/combatant.h"
#include "../test/test.h"

Quiz::Quiz(Combatant* combatant)
{
	mCombatant = combatant;

	mTest = mCombatant->mClientPartido->mTest;

	//quiz states
        mStateMachine =  new StateMachine<Quiz>(this);
        mStateMachine->setCurrentState      (INIT_QUIZ::Instance());
        mStateMachine->setPreviousState     (INIT_QUIZ::Instance());
        mStateMachine->setGlobalState       (GLOBAL_QUIZ::Instance());

       	//question 
	mComputerAskedTime = 0;
        
	//answer	
	mComputerAnswerTime = 0;

	//correctAnswer
	mCorrectAnswerTime = 5000;
	mCorrectAnswerStartTime = 0;

        //question
        mQuestionID = 1;

        //time
        mAnswerTime = 0;

}

Quiz::~Quiz()
{
	//delete mTest;
	delete mStateMachine;
}

void Quiz::update()
{
	mStateMachine->update();
}

void Quiz::readAnswer(int answerTime, std::string answer)
{
        //clear answer string
        mStringAnswer.clear();
        mAnswerTime = answerTime;
        mStringAnswer = answer;

        mTest->insertAnswerAttempt(mQuestionID,mStringAnswer,mAnswerTime);

        if (mStringAnswer.compare(mCombatant->mClientPartido->mServerPartido->mQuestionVector.at(mQuestionID)->answer) != 0 || mAnswerTime > 2000)
        {
                mTest->mShowCorrectAnswer = true;
        }
        else
        {
                if (mCombatant)
                {
                    	mCombatant->mScore++;
                        mTest->mShowCorrectAnswer = false;
                }

        }

        //send another question
        mStateMachine->changeState(SENDING_QUESTION::Instance());
        mTest->mQuestionString = "";
}

