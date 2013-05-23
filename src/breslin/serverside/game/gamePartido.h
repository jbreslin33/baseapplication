#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "game.h"

using namespace std;

//class Network;
class ServerPartido;
class Shape;
class Battle;

class GamePartido : public Game
{
public:

	GamePartido(ServerPartido* server, int id);
	~GamePartido();

	//time
	void processUpdate();
	void collision(Shape* shape1, Shape* shape2);

	std::vector<Battle*> mBattleVector;  

	ServerPartido* mServer;

	void sendAnswer();
};

#endif
