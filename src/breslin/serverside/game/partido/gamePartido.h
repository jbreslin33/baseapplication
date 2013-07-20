#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "../game.h"

using namespace std;
#include <string>

class ServerPartido;
class ShapePartido;
class ClientPartido;

class GamePartido : public Game
{
public:

	GamePartido(ServerPartido* serverPartido, int id);
	~GamePartido();

	//updates
	void update();

	//serverPartido
	ServerPartido* mServerPartido;

	//shapes
        std::vector<ShapePartido*> mShapePartidoVector;       //every tangible item in game world..
	void createShapes();
	void sendShapes(ClientPartido* clientPartido);

	//end of game
	bool checkForEndOfGame();
	void reset();
};

#endif
