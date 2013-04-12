#ifndef GAMETAG_H
#define GAMETAG_H

//parent
#include "game.h"

class ServerTag;

class GameTag : public Game
{
public:

GameTag(Server* server);
~GameTag();

//world
virtual void createWorld();

//
virtual void checkForEndOfGame();

//collision
virtual void collision(Shape* shape1, Shape* shape2);

//commands
virtual void storeCommands(Shape* shape);
virtual void checkBounds(Shape* shape);

Shape* mShapeIt;
Shape* mShapeNoTagBack;
ServerTag* mServerTag;
  

};

#endif
