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

void sendSchools();
void parseAnswer();

ServerPartido* mServerPartido;	

//db
PGconn          *conn;


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
int mAnswer;
int mLimit;

//answer
virtual void readAnswer(Message* message);
std::string mStringAnswer;
int mAnswerTime;
void insertAnswerAttempt();

//shape
ShapePartido* mShapePartido;
void setShape(ShapePartido* shapePartido);

//battle
void initializeBattle();
virtual void processUpdate();
void getQuestion();
void sendQuestion();
void sendBattleStart();
void sendBattleEnd();

};

#endif
