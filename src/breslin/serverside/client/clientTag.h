#ifndef CLIENTTAG_H
#define CLIENTTAG_H

//parent
#include "client.h"

class ClientTag : public Client
{
public:
	ClientTag(Server* server, struct sockaddr *address);

~ClientTag();

virtual void createShape();

};
#endif
