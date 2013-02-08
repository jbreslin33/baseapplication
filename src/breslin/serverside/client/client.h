#ifndef CLIENT_H
#define CLIENT_H

#include "../message/message.h"

#ifdef WIN32
	#pragma comment (lib,"ws2_32.lib")
#pragma message ("Auto linking WinSock2 library")

	#include <winsock2.h>
#else
	#include <string.h>
	#include <netinet/in.h>
#endif

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
#define DREAMSOCK_CONNECTED				1
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

class Client
{
public:
	Client(Server* server, struct sockaddr *address);
	Client(Server* server, struct sockaddr *address, int clientID);

~Client();


	//id used just for browser clients for now, if it's 0 then we know it's a c++ java client.
	int mClientID;

	int				mConnectionState;		// Connecting, connected, disconnecting, disconnected

	signed short	mDroppedPackets;			// Dropped packets

	struct sockaddr	mMyaddress;				// Socket address

	int				mLastMessageTime;

public:
	virtual void createShape();
	void remove();
	void			SendPacket(Message *message);
	void sendAllShapes();
	//clients address to send back messages to
	struct sockaddr *GetSocketAddress(void) { return &mMyaddress; }
	void			SetSocketAddress(struct sockaddr *address) { memcpy(&mMyaddress, address, sizeof(struct sockaddr)); }


    Shape* mShape;  //on server: everybody's got one ...same on clientside mShape is the clients personal avatar..

	Server* mServer;

};
#endif
