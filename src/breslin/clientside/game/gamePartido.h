#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "game.h"

//Ogre
#include <OgreEntity.h>


//standard library
#include <vector>

class GamePartido : public Game 
{
public:
	
	GamePartido(ApplicationBreslin* applicationBreslin);
	~GamePartido();

public:

// constants
static const char mMessageAskQuestion = -76;

};

#endif
