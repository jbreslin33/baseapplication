#ifndef CLIENTSTABLE_H
#define CLIENTSTABLE_H

#include "../../client/client.h"
#include <netinet/in.h>

class Server;

class ClientStable : public Client 
{
public:

ClientStable(Server* server, struct sockaddr *address, int clientID, bool permanent);
~ClientStable();


//update
virtual void update() { }
	
//handle letter 
virtual bool  handleLetter(Letter* letter) { } 


};
#endif
