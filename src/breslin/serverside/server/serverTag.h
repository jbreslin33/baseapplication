#ifndef SERVERTAG_H
#define SERVERTAG_H

//parent
#include "server.h"

class ServerTag : public Server
{
public:
	ServerTag(Game* serverSideGame,const char *localIP, int serverPort);
	~ServerTag();

	//client
	void createClient(struct sockaddr *address);
	void addClient(Client* client);
};

#endif
