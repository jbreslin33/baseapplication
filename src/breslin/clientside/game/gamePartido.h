#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "game.h"

//Ogre
#include <OgreEntity.h>

//standard library
#include <vector>

class ApplicationPartido;
class GamePlayPartidoBattle;

class GamePartido : public Game 
{
public:
	
	GamePartido(ApplicationPartido* applicationPartido);
	~GamePartido();

public:

ApplicationPartido* mApplication;

//states
State* mGamePlayPartidoBattle;

// constants
//question
static const char mMessageAskQuestion = -76;

//battle
static const char mMessageBattleStart = -75;
static const char mMessageBattleEnd   = -74;

virtual void createStates();
virtual void checkByteBuffer(ByteBuffer* byteBuffer);
void askQuestion(ByteBuffer* byteBuffer);

void battleStart(ByteBuffer* byteBuffer);
void battleEnd(ByteBuffer* byteBuffer);

bool mBattleStart;
bool mBattleEnd;

};

#endif
