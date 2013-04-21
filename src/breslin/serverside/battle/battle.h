#ifndef BATTLE_H
#define BATTLE_H

class Shape;

class Battle 
{
public:
	
	Battle(Shape* shape1, Shape* shape2);
	~Battle();

void processUpdate();

bool mOver;

};

#endif
