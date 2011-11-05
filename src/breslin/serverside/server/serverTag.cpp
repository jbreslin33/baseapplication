//header
#include "serverTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//client
#include "../client/clientTag.h"


ServerTag::ServerTag(Game* game,const char *localIP, int serverPort) : Server(game,localIP,serverPort)
{
}

ServerTag::~ServerTag()
{
}

void ServerTag::createClient(struct sockaddr *address)
{
	LogString("client ClientTag in ServerTag");
	Client* client = new ClientTag(this, address);

}

