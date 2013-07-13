#ifndef CLIENTROBUST_H
#define CLIENTROBUST_H

#include "../../client/client.h"

class Server;
class Network;
class Shape;
class Game;

class ClientRobust : public Client 
{
public:

ClientRobust(Server* server, struct sockaddr *address, int clientID, bool permanent);
~ClientRobust();

//update
virtual void update();
	
//handle letter 
virtual bool  handleLetter(Letter* letter);


};
#endif
