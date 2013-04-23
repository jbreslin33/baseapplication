#include "serverPartido.h"

#include "../game/gamePartido.h"

ServerPartido::ServerPartido(Ogre::Root* root, const char *localIP, int serverPort) 
:
 Server(root, localIP, serverPort)
{
	//get questions
        getQuestions();

	//create game partido!
	//mGameVector.push_back(new GamePartido(this,2));
	//mGameVector.push_back(new GamePartido(this,2));
 	mGameVector.push_back(new Game(this,2));
}

ServerPartido::~ServerPartido()
{
}

void ServerPartido::processUpdate()
{

}
