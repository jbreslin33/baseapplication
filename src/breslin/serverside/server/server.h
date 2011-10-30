#ifndef SERVER_H
#define SERVER_H

#include "../message/message.h"

#include <vector>

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

// Introduce classes
class Network;
class Client;
class Game;
class Shape;

class Server
{
public:

	//clients
	std::vector<Client*> mClientVector;

	//port
	int				port;					// Port

	//initialize
	bool			init;

	//game
	Game* mGame;

	//network
	Network* mNetwork;

	//address
	const char *mLocalIP;

	//codes
	static const int mConnect     = -101;
	static const int mDisconnect  = -102;
	static const int mAddShape    = -103;
	static const int mRemoveShape = -104;

public:
	Server(Game* serverSideGame,const char *localIP, int serverPort);
	~Server();

	//timeout
	int  checkForTimeout(char *data, struct sockaddr *from);

	//client
	void createClient(struct sockaddr *address);
	void addClient(Client* client);
	
	//shapes
	void sendRemoveShape(Shape* shape);

	//packets
	int	 getPacket(char *data, struct sockaddr *from);
	void sendPackets();
	void readPackets();
	void parsePacket(Message *mes, struct sockaddr *address);
	
	//port
	int	getPort() { return port; }


};

#endif
