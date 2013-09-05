#ifndef ABILITY_H
#define ABILITY_H

//parent
#include "../../baseentity/baseEntity.h"

class Shape;

class Ability : public BaseEntity
{
public:

	Ability(Shape* shape);
	~Ability();

Shape* mShape;

virtual void processTick() { }
virtual void interpolateTick(float renderTime) { }

//update
virtual void update() { }

//handle letter
virtual bool  handleLetter(Letter* letter) { }


};

#endif
