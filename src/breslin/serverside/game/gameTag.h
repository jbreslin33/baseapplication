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
virtual int  setFlag(Command* command, Shape* shape);
virtual void buildDeltaMoveMessage(Command* command, int flags, Message* message, Shape* shape);

Shape* mItShape;
  

};

#endif
