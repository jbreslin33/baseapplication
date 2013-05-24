#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "game.h"

using namespace std;
#include <string>

//class Network;
class ServerPartido;
class ShapePartido;
class Battle;
class ClientPartido;

class GamePartido : public Game
{
public:

	GamePartido(ServerPartido* serverPartido, int id);
	~GamePartido();

	//time
	void processUpdate();
	void collision(Shape* shape1, Shape* shape2);
	void battleCollision(ShapePartido* shapePartido1, ShapePartido* shapePartido2);

	std::vector<Battle*> mBattleVector;  

	ServerPartido* mServerPartido;
	void sendAnswer(ClientPartido* client, int answerTime, std::string answer);

	//shapes
        std::vector<ShapePartido*> mShapePartidoVector;       //every tangible item in game world..
	void createShapes();
};

#endif
