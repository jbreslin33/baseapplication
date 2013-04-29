#ifndef BATTLER_H
#define BATTLER_H

class Shape;
class Battle;

class Battler 
{
public:
	
	Battler(Battle* battle, Shape* shape);
	~Battler();

void processUpdate();
int getQuestionLevelID();
	
Battle* mBattle; 
Shape* mShape;
int mQuestionLevelID;	
};

#endif
