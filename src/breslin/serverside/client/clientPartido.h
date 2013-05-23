#ifndef CLIENTPARTIDO_H
#define CLIENTPARTIDO_H

#include "client.h"
#include "../battler/battler.h"

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



	ServerPartido* mServer;	
	GamePartido* mGame;

	//answer
        virtual void readAnswer(Message* message);
        std::string mStringAnswer;
        int mAnswerTime;

	//shape
	ShapePartido* mShapePartido;
	void setShape(ShapePartido* shapePartido);

	//battler
	Battler* mBattler;
	void setBattler(Battler* battler) { mBattler = battler; }
};

#endif
