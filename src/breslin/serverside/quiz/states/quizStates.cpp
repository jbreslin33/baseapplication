//parent
#include "quizStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//quiz
#include "../quiz.h"

//client
#include "../../client/robust/partido/clientPartido.h"

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
	
	//quiz->mClient1->mQuiz = quiz;	
	//quiz->mClient2->mQuiz = quiz;	
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
void INIT_QUIZ::exit(Quiz* quiz)
{
}
bool INIT_QUIZ::onLetter(Quiz* quiz, Letter* letter)
{
        return true;
}


/*****************************************
	NORMAL_QUIZ
****************************************/
NORMAL_QUIZ* NORMAL_QUIZ::Instance()
{
  static NORMAL_QUIZ instance;
  return &instance;
}
void NORMAL_QUIZ::enter(Quiz* quiz)
{
}
void NORMAL_QUIZ::execute(Quiz* quiz)
{
}
void NORMAL_QUIZ::exit(Quiz* quiz)
{
}
bool NORMAL_QUIZ::onLetter(Quiz* quiz, Letter* letter)
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
