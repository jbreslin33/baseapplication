#ifndef CLIENT_H
#define CLIENT_H

#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"

template <class entity_type> class State;

#include <string>

#include "../message/message.h"

#include <vector>
#include <string.h>
#include <netinet/in.h>

typedef int SOCKET;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Connection states
#define DREAMSOCK_CONNECTING			0
#define DREAMSOCK_CONNECTED			1
#define DREAMSOCK_DISCONNECTING			2
#define DREAMSOCK_DISCONNECTED			4

#define DREAMSOCK_INVALID_SOCKET	-1

// Error codes
#define DREAMSOCK_SERVER_ERROR			1
#define DREAMSOCK_CLIENT_ERROR			2

// Introduce classes
class Server;
class Network;
class Shape;
class Game;

class Client : public BaseEntity
{
public:
	Client(Server* server, struct sockaddr *address, int clientID, bool permanent);

~Client();

StateMachine<Client>* mStateMachine;
StateMachine<Client>* mLoginStateMachine;
StateMachine<Client>* mControlStateMachine;
StateMachine<Client>* mPermanenceStateMachine;

bool mPermanence;

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

	//update
	virtual void update();
	
	//handle letter 
  	virtual bool  handleLetter(Letter* letter);

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


};
#endif
