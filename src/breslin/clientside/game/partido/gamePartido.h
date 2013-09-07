#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "../game.h"

//Ogre
#include <OgreEntity.h>

//standard library
#include <vector>

class ApplicationPartido;

class GamePartido : public Game 
{
public:
	
	GamePartido(ApplicationPartido* applicationPartido);
	~GamePartido();

public:

ApplicationPartido* mApplicationPartido;

// constants

//question
static const char mMessageAskQuestion = -76;

//battle
static const char mMessageBattleStart = -75;
static const char mMessageBattleEnd   = -74;

//showCorrectAnswer
static const char mMessageCorrectAnswerStart = -61;
static const char mMessageCorrectAnswer = -62;
static const char mMessageCorrectAnswerEnd = -63;

virtual void checkByteBuffer(ByteBuffer* byteBuffer);
void askQuestion(ByteBuffer* byteBuffer);
void correctAnswer(ByteBuffer* byteBuffer);

//battle
bool mBattleStart;
bool mBattleEnd;

//correctAnswer
bool mCorrectAnswerStart;
bool mCorrectAnswer;
bool mCorrectAnswerEnd;
};

#endif