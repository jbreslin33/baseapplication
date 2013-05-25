#ifndef CLIENTPARTIDO_H
#define CLIENTPARTIDO_H

#include "client.h"

#include <vector>

class ServerPartido;
class GamePartido;
class ShapePartido;

class ClientPartido : public Client
{

public:

ClientPartido(ServerPartido* server, struct sockaddr *address, int clientID);	
~ClientPartido();

void sendSchools();
void parseAnswer();

ServerPartido* mServerPartido;	

//game
GamePartido* mGamePartido;
void setGame(GamePartido* gamePartido);
GamePartido* getGame();

//battle
int mFirstUnmasteredQuestionID;
std::vector<int> mMasteredQuestionIDVector;
bool mWaitingForAnswer;
std::string mQuestion;
int mAnswer;
int mLimit;


//answer
virtual void readAnswer(Message* message);
std::string mStringAnswer;
int mAnswerTime;

//shape
ShapePartido* mShapePartido;
void setShape(ShapePartido* shapePartido);

//battle
void initializeBattle();
virtual void processUpdate();
void getQuestionLevelID();
void sendQuestion();
void sendBattleStart();
void sendBattleEnd();

};

#endif
