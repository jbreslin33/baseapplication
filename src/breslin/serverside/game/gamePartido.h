#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "game.h"

using namespace std;

//class Network;
class Server;

class GamePartido : public Game
{
public:

	GamePartido(Server* server, int id);
	~GamePartido();

	//time
	void	processUpdate();
};

#endif
