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
	void			sendAddAIShape(Shape* shape);
	void			sendAddShape(Client* client);
	void			sendRemoveShape(Shape* shape);
	void			addClient(struct sockaddr *address);
	void			writeAddShape(Client* client, Shape* shape, char local, bool skipNewClient);
	void			writeAddShapes(Client* client, Shape* shape, char local, bool skipNewClient);
	void			removeClient(Client *client);

	
	void			parsePacket(Message *mes, struct sockaddr *address);
	int				checkForTimeout(char *data, struct sockaddr *from);

	std::vector<Client*> mClientVector;

	int				port;					// Port

	bool			init;

public:
					Server(Game* serverSideGame,const char *localIP, int serverPort);
					~Server();

	int				getPacket(char *data, struct sockaddr *from);
	void			sendPackets(void);

	int				getPort(void)			{ return port; }

	Game* mGame;
	Network* mNetwork;

	void	readPackets(void);
	const char *mLocalIP;

	//codes
	static const int mConnect     = -101;
	static const int mDisconnect  = -102;
	static const int mAddShape    = -103;
	static const int mRemoveShape = -104;

};

#endif
