#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "../message/message.h"

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
class ClientStateMachine;

class Client
{
public:
	Client(Server* server, struct sockaddr *address, int clientID);

~Client();

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;

	//Message
        Message mMessage;

	//id used just for browser clients for now, if it's 0 then we know it's a c++ java client.
	int mClientID;

	int				mConnectionState;		

	signed short	mDroppedPackets;

	struct sockaddr	mSocketAddress;

	int				mLastMessageTime;

	bool mLoggedIn;
	std::string mStringUsername;
	std::string mStringPassword;

	int mKey;
	int mKeyLast;

public:

	//processUpdate
	virtual void processUpdate();

	//timeout
	void checkForTimeout();

	//client
	void remove();

	//connect
	void sendConnected();

	//login
	void login();
	void logout();
	bool checkLogin(Message* mes);
        bool getPasswordMatch(std::string username,std::string password);
	void readLoginMessage(Message* mes);


	//clients address to send back messages to
	struct sockaddr *GetSocketAddress(void) { return &mSocketAddress; }
	void setSocketAddress(struct sockaddr *address); 

    	Shape* mShape;  //on server: everybody's got one ...same on clientside mShape is the avatar.
	void setShape(Shape* shape);  

	Server* mServer;

	//game
        std::vector<Game*> mGameVector;
	void addGame(Game* game);
	Game* mGame;
	Game* getGame();
	virtual void setGame(int gameID);
	
	//db
	int         db_id;
        std::string db_username;
        std::string db_password;
        std::string db_first_name;
        std::string db_last_name;
        int         db_school_id;

	ClientStateMachine* mGameControlStateMachine;
	ClientStateMachine* mLoginStateMachine;
};
#endif
