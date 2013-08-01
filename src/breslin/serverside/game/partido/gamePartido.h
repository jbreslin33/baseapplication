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
	virtual ~GamePartido();

	//updates
	virtual void update();

	//serverPartido
	ServerPartido* mServerPartido;

	//shapes
        std::vector<ShapePartido*>* mShapePartidoVector;       //every tangible item in game world..
	virtual void createShapes();

	//end of game
	virtual bool checkForEndOfGame();
	virtual void reset();
};

#endif
