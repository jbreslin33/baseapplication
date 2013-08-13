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

	//let this clients test know about this quiz
	mCombatant->mClientPartido->mTest->mQuiz = this; 
 
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

void Quiz::readAnswer(int answerTime, std::string answer)
{
	LogString("readA");
/*
        //clear answer string
        mStringAnswer.clear();
        mAnswerTime = answerTime;
        mStringAnswer = answer;

        insertAnswerAttempt(mQuiz->mQuestionID);

        if (mStringAnswer.compare(mClientPartido->mServerPartido->mQuestionVector.at(mQuestionID)->answer) != 0 || mAnswerTime > 2000)
        {
                ShapePartido* opponent  = mShapePartido->mOpponent;

                if (opponent)
                {
                        //score battle
                        scoreBattle(LOSS);
                        opponent->mClientPartido->scoreBattle(WIN);

                        //set battle record text .. mBattleRecordText
                        setBattleRecordText();
                        opponent->mClientPartido->setBattleRecordText();

                        //set Text of shape .. mText
                        mShapePartido->setText(mBattleRecordText);
                        opponent->mClientPartido->mShapePartido->setText(opponent->mClientPartido->mBattleRecordText);

                        //reset battle
                        resetBattle();
                        opponent->mClientPartido->resetBattle();

                        //send battle end to client
                        sendBattleEnd();
                        opponent->mClientPartido->sendBattleEnd();
                }
                else //opponent took care of loss....
                {
                }
        }
        else
        {
                mBattleScore++;
        }
        if (mBattleScore > 9)
        {
                ShapePartido* opponent  = mShapePartido->mOpponent;

                //score battle
                scoreBattle(WIN);
                opponent->mClientPartido->scoreBattle(LOSS);

                //set battle record text .. mBattleRecordText
                setBattleRecordText();
                opponent->mClientPartido->setBattleRecordText();

                //set Text of shape .. mText
                mShapePartido->setText(mBattleRecordText);
                opponent->mClientPartido->mShapePartido->setText(opponent->mClientPartido->mBattleRecordText);

                //reset battle
                resetBattle();
                opponent->mClientPartido->resetBattle();

                //send battle end to client
                sendBattleEnd();
                opponent->mClientPartido->sendBattleEnd();
        }

        //set vars for new question and answer combo....
        mWaitingForAnswer = false;
        mQuestionString = "";
*/
}

