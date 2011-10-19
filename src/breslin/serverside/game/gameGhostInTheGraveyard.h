#ifndef GAMEGHOSTINTHEGRAVEYARD_H
#define GAMEGHOSTINTHEGRAVEYARD_H

//parent
#include "game.h"

class GameGhostInTheGraveyard : public Game
{
public:

GameGhostInTheGraveyard();
~GameGhostInTheGraveyard();

//shapes
virtual void createClientAvatar(Client* client, bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
	
};

#endif
