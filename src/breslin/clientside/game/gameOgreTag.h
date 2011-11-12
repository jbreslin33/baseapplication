#ifndef GAMEOGRETAG_H
#define GAMEOGRETAG_H

/***************************************
*   		INCLUDES
***************************************/

//parents
#include "gameOgre.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

//ByteBuffer
class ByteBuffer;

class GameOgreTag : public GameOgre
{
public:
	
	GameOgreTag(const char* serverIP, int serverPort);
	~GameOgreTag();

/***************************************
*   		MEMBER VARIABLES
***************************************/


/***************************************
*			          METHODS
***************************************/

//shape
virtual void addShape(bool b, ByteBuffer* byteBuffer);

};

#endif
