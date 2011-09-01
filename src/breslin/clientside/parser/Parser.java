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
public static final byte mCommandKey          = 1;
public static final byte mCommandMilliseconds = 2;

public static final byte mMessageFrame = 1;
public static final byte mMessageConnect     = -101;
public static final byte mMessageDisconnect  = -102;
public static final byte mMessageAddShape    = -103;
public static final byte mMessageRemoveShape = -104;

public static final byte mMessageNonDeltaFrame = 2;
public static final byte mMessageServerExit = 3;
public static final byte mMessageKeepAlive = 12;

//network flags
public static final byte mCommandOriginX      = 4;
public static final byte mCommandOriginY      = 8;
public static final byte mCommandOriginZ      = 16;
public static final byte mCommandRotationX    = 32;
public static final byte mCommandRotationZ    = 64;


}


