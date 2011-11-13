#ifndef APPLICATIONOGRE_H
#define APPLICATIONOGRE_H

/***************************************
*   		INCLUDES
***************************************/
//standard library

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//parents
#include "application.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
//game
class GameOgre;

//graphics
class GraphicsOgre;

//ByteBuffer
class ByteBuffer;

class ApplicationOgre : public Application
{
public:
	
	ApplicationOgre(const char* serverIP, int serverPort);
	~ApplicationOgre();

/***************************************
*   		MEMBER VARIABLES
***************************************/
//game
GameOgre* mGameOgre;

//graphics
GraphicsOgre* mGraphicsOgre;

/***************************************
*			          METHODS
***************************************/

//time
virtual float getRenderTime();

//graphics
virtual bool runGraphics();

virtual void initializeGui();

virtual void processInput();

};

#endif
