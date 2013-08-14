#ifndef QUIZ_H
#define QUIZ_H

#include "../../fsm/stateMachine.h"

#include "../message/message.h"

#include <string>
#include <vector>

class QuestionAttempts;
class Message;
class Combatant;

class Quiz 
{
public:
	
Quiz(Combatant* combatant);
~Quiz();

void update();

StateMachine<Quiz>* mStateMachine;

//combatant
Combatant* mCombatant;

//message
Message mMessage;

//question
int mQuestionID;
std::string mQuestionString;
int mComputerAskedTime;
void sendQuestion(int questionID);

//answer
int mComputerAnswerTime;
bool mWaitingForAnswer;
void readAnswer(int answerTime, std::string answer);
};

#endif
