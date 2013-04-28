#ifndef BATTLE_H
#define BATTLE_H

#include <vector>

using namespace std;

class Shape;
class Game;

class Battle 
{
public:
	
	Battle(Game* game, std::vector<Shape*> shapeVector);
	~Battle();

//shapes
std::vector<Shape*> mShapeVector;       //every shape in the battle..

void processUpdate();
int getQuestionLevelID();

bool mOver;


};

#endif
