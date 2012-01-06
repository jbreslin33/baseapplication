//header
#include "serverTagAll.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/gameTagAll.h"

//client
#include "../client/clientTagAll.h"

ServerTagAll::ServerTagAll(GameTagAll* gameTagAll, const char *localIP, int serverPort) :
ServerTag(gameTagAll,localIP,serverPort)
{
	mGameTagAll = gameTagAll;
}

ServerTagAll::~ServerTagAll()
{

}

void ServerTagAll::createClient(struct sockaddr *address)
{
	LogString("client ClientTag in ServerTag");
	Client* client = new ClientTagAll(this, address);
	client->createShape();
	//let this client know about all shapes(it will sending add for it's avatar as that is done right above.)
	client->sendAllShapes();

}

