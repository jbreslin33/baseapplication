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
virtual void createClientAvatar(Client* client, bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
	
};

#endif
