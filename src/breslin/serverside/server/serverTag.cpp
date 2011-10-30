//header
#include "serverTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"


ServerTag::ServerTag(Game* game,const char *localIP, int serverPort) : Server(game,localIP,serverPort)
{
}

ServerTag::~ServerTag()
{
}

void ServerTag::addClient(Client* client)
{
	mClientVector.push_back(client);
}
