#ifndef BATTLE_H
#define BATTLE_H

class Shape;
class Game;

class Battle 
{
public:
	
	Battle(Game* game, Shape* shape1, Shape* shape2);
	~Battle();

void processUpdate();

bool mOver;

};

#endif
