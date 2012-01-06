//header
#include "serverTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/gameTag.h"

//client
#include "../client/clientTag.h"


ServerTag::ServerTag(GameTag* gameTag,const char *localIP, int serverPort) : Server(gameTag,localIP,serverPort)
{
	mGameTag = gameTag;
}

ServerTag::~ServerTag()
{
}

void ServerTag::createClient(struct sockaddr *address)
{
	Client* client = new ClientTag(this, address);
	client->createShape();
	//let this client know about all shapes(it will sending add for it's avatar as that is done right above.)
	client->sendAllShapes();

}

