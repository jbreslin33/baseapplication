#ifndef CLIENTTAGALL_H
#define CLIENTTAGALL_H

//parent
#include "clientTag.h"

class ServerTagAll;

class ClientTagAll : public ClientTag
{
public:
	ClientTagAll(ServerTagAll* serverTagAll, struct sockaddr *address);

~ClientTagAll();

virtual void createShape();

};
#endif
