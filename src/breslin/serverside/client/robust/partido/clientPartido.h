#ifndef CLIENTPARTIDO_H
#define CLIENTPARTIDO_H

#include "../clientRobust.h"

#include <vector>

//postgresql
#include <postgresql/libpq-fe.h>

class ServerPartido;
class GamePartido;
class ShapePartido;
class Utility;
class Quiz;

class ClientPartido : public ClientRobust
{

public:

ClientPartido(ServerPartido* server, struct sockaddr *address, int clientID, bool permanence, int i, std::string username, std::string p, std::string first_name, std::string m1, std::string m2, std::string m3, std::string last_name, int s);	
~ClientPartido();

StateMachine<ClientPartido>* mClientPartidoStateMachine;

static const int WIN  = 1;
static const int TIE  = 0;
static const int LOSS = -1;

ServerPartido* mServerPartido;	

//quiz
Quiz* mQuiz;

//utility
Utility* utility;

//game
void addGame(GamePartido* gamePartido);
std::vector<GamePartido*> mGamePartidoVector;
GamePartido* mGamePartido;
GamePartido* getGame();
virtual void setGame(int gameID);

//shape
ShapePartido* mShapePartido;
void setShape(ShapePartido* shapePartido);

//update
virtual void update();

//handle letter 
virtual bool  handleLetter(Letter* letter);

};
#endif
