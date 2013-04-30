#ifndef BATTLER_H
#define BATTLER_H

#include <vector>
using namespace std;

#include <string>
#include "../message/message.h"

class Shape;
class Battle;

class Battler 
{
public:
	
	Battler(Battle* battle, Shape* shape);
	~Battler();

void processUpdate();
void getQuestionLevelID();
void sendQuestion();	
Battle* mBattle; 
Shape* mShape;
int mFirstUnmasteredQuestionID;	
std::vector<int> mMasteredQuestionIDVector;    
bool mWaitingForAnswer;
std::string mQuestion;
int mAnswer;
Message mMessage;
};

#endif
