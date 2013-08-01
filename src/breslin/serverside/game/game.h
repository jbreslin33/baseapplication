#ifndef GAME_H
#define GAME_H

#include "../message/message.h"

#include <string.h>
#include <vector>

//postgres
#include <postgresql/libpq-fe.h>

using namespace std;

#define COMMAND_HISTORY_SIZE		64

class Server;
class ClientRobust;
class Shape;
class Vector3D;
class Bounds;

class Game
{
public:

//statics
static const char mMessageKey        = 1;
static const char mMessageFrameTime  = 2;
static const char mMessageServerExit = 3;

	int mID;

	Server	*mServer;  //go between for game(contains game logic) and Network(handles sending message across internets)

	//bounds
	Bounds* mBounds;	

        //Message
        Message mMessage;

	//shapes
	std::vector<Shape*>* mShapeVector;	//every tangible item in game world..

	//db
     	PGconn* mDBConnection;

public:
	Game(Server* server, int id);
	virtual ~Game();

	//index
	unsigned int getOpenIndex ();
	Vector3D* getOpenPoint    ();

	//end game
	virtual bool checkForEndOfGame() { }

	// Network
	void	sendExitNotification();
	void	readDeltaMoveCommand(Message *mes, ClientRobust *client);
	
	//time
	virtual void	update();
	
	//collision detection
	void checkCollisions();
	void checkBounds(Shape* shape);
		
	//scope
 	bool    checkScope(ClientRobust* client, Shape* shape);


	//join
	void join(ClientRobust* client);
	void leave(ClientRobust* client);
	
	//shapes
	virtual void createShapes();
	virtual void sendShapes(Client* client);
	Shape* getShapeFromID(int id);
};

#endif
