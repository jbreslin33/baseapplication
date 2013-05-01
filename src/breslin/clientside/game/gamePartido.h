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
//question
static const char mMessageAskQuestion = -76;

//battle
static const char mMessageBattleStart = -75;
static const char mMessageBattleEnd   = -74;

virtual void checkByteBuffer(ByteBuffer* byteBuffer);
void askQuestion(ByteBuffer* byteBuffer);

void battleStart(ByteBuffer* byteBuffer);
void battleEnd(ByteBuffer* byteBuffer);

};

#endif
