#ifndef OGRESHAPE_H
#define OGRESHAPE_H

//messages
#include "../message/message.h"

//command
#include "../../command/command.h"

//game
#include "../game/game.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//utility
#include <string.h>

//math
#include "../../math/vector3D.h"

#define COMMAND_HISTORY_SIZE		64

class OgreShape 
{

public:
OgreShape();
OgreShape(unsigned int index, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root);
~OgreShape();

};

#endif

