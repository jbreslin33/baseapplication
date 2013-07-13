#ifndef CLIENTROBUST_H
#define CLIENTROBUST_H

#include "../../client/client.h"

#include "../../../fsm/stateMachine.h"

template <class entity_type> class State;

#include <string>

#include "../../message/message.h"

#include <vector>
#include <string.h>
#include <netinet/in.h>

// Define SOCKET data type for UNIX (defined in WinSock for Win32)
// And socklen_t for Win32
#ifdef WIN32
	typedef int socklen_t;
#else
	typedef int SOCKET;

	#ifndef TRUE
	#define TRUE 1
	#endif
	#ifndef FALSE
	#define FALSE 0
	#endif
#endif

// Connection states
#define DREAMSOCK_CONNECTING			0
#define DREAMSOCK_CONNECTED			1
#define DREAMSOCK_DISCONNECTING			2
#define DREAMSOCK_DISCONNECTED			4

#ifdef WIN32
	#define DREAMSOCK_INVALID_SOCKET	INVALID_SOCKET
#else
	#define DREAMSOCK_INVALID_SOCKET	-1
#endif

// System messages
// Note (for all messages - system and user):
// positive = sequenced message
// negative = un-sequenced message

// Error codes
#define DREAMSOCK_SERVER_ERROR			1
#define DREAMSOCK_CLIENT_ERROR			2

// Introduce classes
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
