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
