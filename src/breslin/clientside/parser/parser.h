#ifndef PARSER_H
#define PARSER_H

/***************************************
*   		INCLUDES
***************************************/
//standard library
#include <vector>

//parents


/***************************************
*   		FORWARD DECLARATIONS
***************************************/

class Parser 
{
public:
	
	Parser();
	~Parser();

/***************************************
*   		MEMBER VARIABLES
***************************************/

// ByteBufferes

static const char mMessageFrame = 1;
static const char mMessageConnect     = -101;
static const char mMessageDisconnect  = -102;
static const char mMessageAddShape    = -103;
static const char mMessageRemoveShape = -104;

static const char mMessageNonDeltaFrame = 2;
static const char mMessageServerExit = 3;
static const char mMessageKeepAlive = 12;

//network flags
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

};

#endif
