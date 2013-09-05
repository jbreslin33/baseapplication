#include "ability.h"

Ability::Ability(Shape* shape) : BaseEntity(BaseEntity::getNextValidID())
{
	mShape = shape;
}

Ability::~Ability()
{
}


