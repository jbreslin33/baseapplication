#ifndef GAMEPARTIDO_H
#define GAMEPARTIDO_H

#include "../game.h"

using namespace std;
#include <string>

class ServerPartido;
class ShapePartido;
class ClientPartido;
class Battle;
class Utility;

class GamePartido : public Game
{
public:

	GamePartido(ServerPartido* serverPartido, int id);
	~GamePartido();

	//utility
	Utility* mUtility;

	//updates
	void update();

	//serverPartido
	ServerPartido* mServerPartido;

	//battles
        std::vector<Battle*> mBattleVector;    

	//shapes
        std::vector<ShapePartido*> mShapePartidoVector;       //every tangible item in game world..
	void createShapes();
	void sendShapes(ClientPartido* clientPartido);

	//coldet
	virtual void checkCollisions();

	//end of game
	bool checkForEndOfGame();
	void reset();

	//massiveInserts
	void massiveQuestionsAttemptsInsert();
	void massiveBattleInsert();

	std::string mMassiveInsert;

};
#endif
