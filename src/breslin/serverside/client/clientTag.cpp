//parent
#include "clientTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shapeTag.h"

//server
#include "../server/serverTag.h"

//game
#include "../game/gameTag.h"

//math
#include "../../math/vector3D.h"

//server side client constructor, many instances will be made, one for each client connected.
ClientTag::ClientTag(ServerTag* serverTag, struct sockaddr *address) : Client(serverTag,address)
{
	mServerTag = serverTag;
}

ClientTag::~ClientTag()
{

}

void ClientTag::createShape()
{
	//create the shape for this client -- the avatar
	mShape = new ShapeTag(mServer->mGame->getOpenIndex(),mServerTag->mGameTag,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 
}


