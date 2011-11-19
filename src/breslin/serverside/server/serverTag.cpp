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
	LogString("client ClientTag in ServerTag");
	Client* client = new ClientTag(this, address);

}

