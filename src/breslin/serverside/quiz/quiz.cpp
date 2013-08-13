#include "quiz.h"
#include "states/quizStates.h"
#include "../client/robust/partido/clientPartido.h"
#include "../server/partido/serverPartido.h"
#include "../question/question.h"
#include "../network/network.h"
#include "../../utility/utility.h"
#include "../question/questionAttempts.h"

Quiz::Quiz(Combatant* combatant)
{
	mCombatant = combatant;
 
	//quiz states
        mStateMachine =  new StateMachine<Quiz>(this);
        mStateMachine->setCurrentState      (INIT_QUIZ::Instance());
        mStateMachine->setPreviousState     (INIT_QUIZ::Instance());
        mStateMachine->setGlobalState       (GLOBAL_QUIZ::Instance());

       	//question 
	mQuestionID = 0;
	mComputerAskedTime = 0;
        
	//answer	
	mComputerAnswerTime = 0;
        mWaitingForAnswer = false;
}

Quiz::~Quiz()
{
}

void Quiz::update()
{
	mStateMachine->update();
}


