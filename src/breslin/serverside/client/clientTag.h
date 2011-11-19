#ifndef CLIENTTAG_H
#define CLIENTTAG_H

//parent
#include "client.h"

class ServerTag;

class ClientTag : public Client
{
public:
	ClientTag(ServerTag* serverTag, struct sockaddr *address);

~ClientTag();

	ServerTag* mServerTag;

virtual void createShape();

};
#endif
