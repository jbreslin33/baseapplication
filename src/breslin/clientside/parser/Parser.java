package breslin.clientside.parser;

/***************************************
*   		INCLUDES
***************************************/

public class Parser
{

/***************************************
*   		MEMBER VARIABLES
***************************************/

// Dispatches
static final byte mCommandKey          = 1;
static final byte mCommandMilliseconds = 2;

static final byte mMessageFrame = 1;
static final byte mMessageConnect     = -101;
static final byte mMessageDisconnect  = -102;
static final byte mMessageAddShape    = -103;
static final byte mMessageRemoveShape = -104;

static final byte mMessageNonDeltaFrame = 2;
static final byte mMessageServerExit = 3;
static final byte mMessageKeepAlive = 12;

//network flags
static final byte mCommandOriginX      = 4;
static final byte mCommandOriginY      = 8;
static final byte mCommandOriginZ      = 16;
static final byte mCommandRotationX    = 32;
static final byte mCommandRotationZ    = 64;


}


