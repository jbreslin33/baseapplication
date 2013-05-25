#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/serverPartido.h"

//shape
#include "../shape/shapePartido.h"

//client
#include "../client/clientPartido.h"

//vector3d
#include "../../math/vector3D.h"

#include <stdio.h>

GamePartido::GamePartido(ServerPartido* serverPartido, int id) : Game(serverPartido,id)
{
	mServerPartido = serverPartido;
}

GamePartido::~GamePartido()
{
}

//you should call this from server processUpdate
void GamePartido::processUpdate()
{
	Game::processUpdate();
}

void GamePartido::createShapes()
{
        for (unsigned int i = 0; i < mServerPartido->mClientVector.size(); i++)
        {
                mServerPartido->mClientPartidoVector.at(i)->setShape( new ShapePartido(getOpenIndex(),this,mServerPartido->mClientPartidoVector.at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServerPartido->mRoot,true,true,30.0f,1,false) );
        }
}

void GamePartido::sendAnswer(ClientPartido* client, int answerTime, std::string answer)
{
	LogString("GamePartido::sendAnswer");
}
