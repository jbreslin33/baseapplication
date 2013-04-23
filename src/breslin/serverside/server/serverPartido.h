#ifndef SERVERPARTIDO_H
#define SERVERPARTIDO_H

#include "server.h"

class ServerPartido : public Server
{
public:
	ServerPartido(Ogre::Root* root, const char *localIP, int serverPort);	
	~ServerPartido();

void processUpdate();
};

#endif
