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

	//Message
	Message mMessage;

	//address
	const char *mLocalIP;

	//codes
	//frames
	static const int mMessageFrame 	          = 1;
	static const int mMessageFrameBrowser     = 2;

	//questions	
	static const int mMessageQuestion        = -105;
	static const int mMessageQuestionBrowser = -115;

	//answer
	static const int mMessageAnswer          = -106;
	static const int mMessageAnswerBrowser   = -116;

	//connect
	static const int mConnect                = -101;
	static const int mConnectBrowser         = -111;
	static const int mConnectNode            = -121;

	//join game
	static const int mJoinGame               = -107;
	static const int mJoinGameBrowser        = -117;

	//quit game
	static const int mQuitGame               = -108;
	static const int mQuitGameBrowser        = -118;

	//disconnect	
	static const int mDisconnect             = -102;
	static const int mDisconnectBrowser      = -112;

	//add shape	
	static const int mAddShape    	         = -103;
	static const int mRemoveShape 	         = -104;

public:
	Server(Game* serverSideGame,const char *localIP, int serverPort);
	~Server();

	//timeout
	int  checkForTimeout();

	//client
	virtual void createClient(struct sockaddr *address); //c++ java
	virtual void createClient(struct sockaddr *address, int clientID); //browser

	void addClient(Client* client);
	
	//shapes
	void sendRemoveShape(Shape* shape);

	//packets
	int	 getPacket(char *data, struct sockaddr *from);
	void sendPackets();
	void readDB();
	void readPackets();
	void parsePacket(Message *mes, struct sockaddr *address);
	void checkClientQuit(int type, Client* client, Message* mes);
	void checkClientQuitGame(int type, Client* client, Message* mes);
	
	//port
	int	getPort() { return port; }


};

#endif
