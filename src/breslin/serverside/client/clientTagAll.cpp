//parent
#include "clientTagAll.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shapeTagAll.h"

//server
#include "../server/serverTagAll.h"

//game
#include "../game/gameTagAll.h"

//math
#include "../../math/vector3D.h"

//server side client constructor, many instances will be made, one for each client connected.
ClientTagAll::ClientTagAll(ServerTagAll* serverTagAll, struct sockaddr *address) : ClientTag(serverTagAll,address)
{
	mServerTagAll = serverTagAll;
}

ClientTagAll::~ClientTagAll()
{

}

void ClientTagAll::createShape()
{
	//create the shape for this client -- the avatar
	LogString("create ShapeTagAll in ClientTagAll createShape");
	mShape = new ShapeTagAll(mServer->mGame->getOpenIndex(),mServerTag->mGameTagAll,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 

}


