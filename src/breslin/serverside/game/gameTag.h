#ifndef GAMETAG_H
#define GAMETAG_H

//parent
#include "game.h"

class GameTag : public Game
{
public:

GameTag();
~GameTag();

//shapes
//virtual void addShape(Client* client, bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
virtual void checkCollisions();

//server
virtual void createServer();

//world
virtual void createWorld();

//delta move command
virtual void buildDeltaMoveCommand(Message *mes, Shape* shape);
virtual int  setFlag(Command* command, Shape* shape);
virtual void buildDeltaMoveMessage(Command* command, int flags, Message* message, Shape* shape);

Shape* mItShape;
  

};

#endif
