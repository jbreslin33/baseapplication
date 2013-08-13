#ifndef QUIZ_H
#define QUIZ_H

#include "../../fsm/stateMachine.h"

#include "../message/message.h"

#include <string>
#include <vector>


class QuestionAttempts;
class Message;
class ClientPartido;

class Quiz 
{
public:
	
	Quiz(ClientPartido* clientPartido);
	~Quiz();

void update();

StateMachine<Quiz>* mStateMachine;

//client
ClientPartido* mClientPartido;

//message
Message mMessage;

//question
int mQuestionID;
std::string mQuestionString;
int mComputerAskedTime;

//answer
int mComputerAnswerTime;
bool mWaitingForAnswer;
};

#endif
