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

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;

//db
int         db_id;
std::string db_username;
std::string db_password;
std::string db_first_name;
std::string db_last_name;
int         db_school_id;

//update
virtual void update();
	
//handle letter 
virtual bool  handleLetter(Letter* letter);


};
#endif
