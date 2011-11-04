#ifndef GAMETAG_H
#define GAMETAG_H

//parent
#include "game.h"

class GameTag : public Game
{
public:

GameTag();
~GameTag();

//server
virtual void createServer();

//world
virtual void createWorld();

//collision
virtual void collision(Shape* shape1, Shape* shape2);

//delta move command
virtual void buildDeltaMoveCommand(Message *mes, Shape* shape);
virtual int  setFlag(Shape* shape);
virtual void buildDeltaMoveMessage(int flags, Message* message, Shape* shape);

//commands
virtual void storeCommands(Shape* shape);

Shape* mItShape;
  

};

#endif
