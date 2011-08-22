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

// Dispatches
static const char mCommandKey          = 1;
static const char mCommandMilliseconds = 2;

static const char mMessageFrame = 1;
static const char mMessageConnect     = -101;
static const char mMessageDisconnect  = -102;
static const char mMessageAddShape    = -103;
static const char mMessageRemoveShape = -104;

static const char mMessageNonDeltaFrame = 2;
static const char mMessageServerExit = 3;
static const char mMessageKeepAlive = 12;


};

#endif
