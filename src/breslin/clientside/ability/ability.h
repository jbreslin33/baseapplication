#ifndef ABILITY_H
#define ABILITY_H

class Shape;

class Ability
{
public:

	Ability(Shape* shape);
	~Ability();

/******************************************************
*				VARIABLES
********************************************************/
Shape* mShape;

/******************************************************
*				METHODS
********************************************************/

virtual void processTick() { }
virtual void interplateTick(float renderTime) { }

};

#endif
