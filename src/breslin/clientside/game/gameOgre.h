#ifndef GAMEOGRE_H
#define GAMEOGRE_H

/***************************************
*   		INCLUDES
***************************************/
//standard library

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//parents
#include "game.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
//graphics
class GraphicsOgre;

//ByteBuffer
class ByteBuffer;

class GameOgre : public Game
{
public:
	
	GameOgre(const char* serverIP, int serverPort);
	~GameOgre();

/***************************************
*   		MEMBER VARIABLES
***************************************/

//graphics
GraphicsOgre* mGraphicsOgre;

/***************************************
*			          METHODS
***************************************/

//shape
void addShape(bool b, ByteBuffer* byteBuffer);

//time
float getRenderTime();

//graphics
virtual bool runGraphics();

virtual void initializeGui();

virtual void processInput();




};

#endif
