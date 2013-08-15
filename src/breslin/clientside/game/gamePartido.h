#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "game.h"

//Ogre
#include <OgreEntity.h>

//standard library
#include <vector>

class ApplicationPartido;
class GamePlayPartidoBattle;
class GamePlayPartidoShowCorrectAnswer;

class GamePartido : public Game 
{
public:
	
	GamePartido(ApplicationPartido* applicationPartido);
	~GamePartido();

public:

ApplicationPartido* mApplicationPartido;

//states
State* mGamePlayPartidoBattle;
State* mGamePlayPartidoShowCorrectAnswer;

// constants
//question
static const char mMessageAskQuestion = -76;

//battle
static const char mMessageBattleStart = -75;
static const char mMessageBattleEnd   = -74;

//showCorrectAnswer
static const char mMessageShowCorrectAnswer = -62;

//states
virtual void createStates();
virtual void setStates();

virtual void checkByteBuffer(ByteBuffer* byteBuffer);
void askQuestion(ByteBuffer* byteBuffer);
void showCorrectAnswer(ByteBuffer* byteBuffer);

bool mBattleStart;
bool mBattleEnd;
bool mShowCorrectAnswer;
bool mShowCorrectAnswerEnd;
};

#endif
