#ifndef GAME_H
#define GAME_H

#include <string.h>

#include <vector>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

#define COMMAND_HISTORY_SIZE		64

//class Network;
class Message;
class Server;
class Client;
class Shape;
class Vector3D;

class Game
{
public:

//statics
static const char mCommandKey          = 1;
static const char mCommandMilliseconds = 2;
static const char mMessageServerExit = 3;

	Ogre::Root* mRoot;

	Server	*mServer;  //go between for game(contains game logic) and Network(handles sending message across internets)

	//time
	int		mRealTime;				// Real server up-time in ms
	int		mServerTime;				// Server frame * 100 ms
	long	mFramenum;
	int     mFrameTime;

	//shapes
	std::vector<Shape*> mShapeVector;	//every tangible item in game world..

public:
	Game();
	~Game();

	//server
	virtual void createServer();

	//world
	virtual void createWorld();

	//index
	unsigned int getOpenIndex      ();

	// Network
	void	sendCommand();
	void	sendExitNotification();
	void	readDeltaMoveCommand(Message *mes, Client *client);
	
	//time
	void	frame(int msec);
	
	//collision detection
	virtual void checkCollisions();
	virtual void collision(Shape* shape1, Shape* shape2);
	
	//scope
 	bool    checkScope(Client* client, Shape* shape);

	//commands
	virtual void storeCommands(Shape* shape);

};

#endif
