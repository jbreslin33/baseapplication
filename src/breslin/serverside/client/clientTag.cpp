//parent
#include "clientTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shapeTagPlayer.h"

//server
#include "../server/server.h"

//game
#include "../game/game.h"

//math
#include "../../math/vector3D.h"

//server side client constructor, many instances will be made, one for each client connected.
ClientTag::ClientTag(Server* server, struct sockaddr *address) : Client(server,address)
{
	
}

ClientTag::~ClientTag()
{

}

void ClientTag::createShape()
{
	//create the shape for this client -- the avatar
	LogString("create ShapeTagPlayer in ClientTag");
	mShape = new ShapeTagPlayer(mServer->mGame->getOpenIndex(),mServer->mGame,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 

}


