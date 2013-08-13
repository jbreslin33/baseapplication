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

StateMachine<Quiz>* mStateMachine;

//client
ClientPartido* mClientPartido;

//message
Message mMessage;

//question
int mQuestionID;
std::string mQuestionString;

//questions
std::vector<QuestionAttempts*> mQuestionAttemptsVector;
std::vector<QuestionAttempts*> mQuestionAttemptsVectorTemp;
int getLowestUnpassedLevel(int maxLevel);

//answer
std::string mStringAnswer;
int mAnswerTime;
void insertAnswerAttempt();

int getNewQuestionID();
void sendQuestion(int questionID);

void update();
void getQuestionAttempts();
void insertAnswerAttempts();
int  getMaxLevelAskedID();
bool checkLevel(int level);
void readAnswer(int answerTime, std::string answer);
void parseAnswer(Message* message);


};

#endif
