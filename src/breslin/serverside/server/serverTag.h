#ifndef SERVERTAG_H
#define SERVERTAG_H

//parent
#include "server.h"

class ServerTag : public Server
{
public:
	ServerTag(Game* serverSideGame,const char *localIP, int serverPort);
	~ServerTag();

	void addClient(Client* client);
};

#endif
