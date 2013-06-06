#ifndef CLIENTPARTIDO_H
#define CLIENTPARTIDO_H

#include "client.h"

#include <vector>

//postgresql
#include <postgresql/libpq-fe.h>

class ServerPartido;
class GamePartido;
class ShapePartido;
class Utility;

class ClientPartido : public Client
{

public:

ClientPartido(ServerPartido* server, struct sockaddr *address, int clientID);	
~ClientPartido();

static const int WIN  = 1;
static const int TIE  = 0;
static const int LOSS = -1;

void sendSchools();
void parseAnswer();

ServerPartido* mServerPartido;	

//utility
Utility* utility;

//game
void addGame(GamePartido* gamePartido);
std::vector<GamePartido*> mGamePartidoVector;
GamePartido* mGamePartido;
GamePartido* getGame();
virtual void setGame(int gameID);

//battle
int mQuestionID;
std::vector<int> mMasteredQuestionIDVector;
bool mWaitingForAnswer;
std::string mQuestionString;
int mBattleScore;

int mWins;
int mLosses;
int mTies;

//questions
int getLowestUnpassedLevel(int maxLevel);
int getMaxLevelAskedID();
bool checkLevel(int level);


//answer
virtual void readAnswer(Message* message);
std::string mStringAnswer;
int mAnswerTime;
void insertAnswerAttempt();

//shape
ShapePartido* mShapePartido;
void setShape(ShapePartido* shapePartido);

//battle
virtual void processUpdate();
int getNewQuestionID();
void sendQuestion(int questionID);
void sendBattleStart();
void battleStart(ShapePartido* whoToBattle);
void sendBattleEnd();
void scoreBattle(int result);
void sendBattleRecord(); 
void resetBattle();
void resetRecords();
void resetOpponents();
};
#endif
