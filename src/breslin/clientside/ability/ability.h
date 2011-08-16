#ifndef ABILITY_H
#define ABILITY_H

class Shape;

class Ability
{
public:

	Ability(Shape* shape);
	~Ability();

	Shape* mShape;

	virtual void update();

};

#endif
