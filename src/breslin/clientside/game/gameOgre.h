#ifndef GAMEOGRE_H
#define GAMEOGRE_H

/***************************************
*   		INCLUDES
***************************************/
//parent
#include "game.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class ApplicationOgre;
class ByteBuffer;
class ShapeDynamic;

class GameOgre : public Game
{
public:
	
	GameOgre(ApplicationOgre* applicationOgre, const char* serverIP, int serverPort);
	~GameOgre();

/***************************************
*   		MEMBER VARIABLES
***************************************/
//application
ApplicationOgre* mApplicationOgre;

	
/***************************************
*			          METHODS
***************************************/
//shape
virtual void          addShape       (bool b, ByteBuffer* byteBuffer);

};

#endif
