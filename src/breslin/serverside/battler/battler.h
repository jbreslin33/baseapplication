#ifndef BATTLER_H
#define BATTLER_H

#include <vector>
using namespace std;

#include <string>

class Shape;
class Battle;

class Battler 
{
public:
	
	Battler(Battle* battle, Shape* shape);
	~Battler();

void processUpdate();
void getQuestionLevelID();
	
Battle* mBattle; 
Shape* mShape;
int mFirstUnmasteredQuestionID;	
std::vector<int> mMasteredQuestionIDVector;    
std::string mQuestion;
int mAnswer;
};

#endif
