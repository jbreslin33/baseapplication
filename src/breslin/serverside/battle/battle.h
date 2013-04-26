#ifndef BATTLE_H
#define BATTLE_H

#include <vector>

using namespace std;

class Shape;
class Game;

class Battle 
{
public:
	
	Battle(Game* game, Shape* shape1, Shape* shape2);
	~Battle();

//shapes
std::vector<Shape*> mShapeVector;       //every shape in the battle..

void processUpdate();

bool mOver;


};

#endif
