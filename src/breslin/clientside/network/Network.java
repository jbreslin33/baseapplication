package breslin.clientside.network;

/***************************************
*   		INCLUDES
***************************************/
//standard library

//game
import breslin.clientside.game.Game;

//dispatch
import breslin.clientside.dispatch.Dispatch;

//command
import breslin.clientside.command.Command;

//parser
import breslin.clientside.parser.Parser;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class Network
{

public Network(Game game, byte[] serverIP, int serverPort)
{
	//game
	mGame = game;

	//command
	mCommandToServer     = new Command();
	mLastCommandToServer = new Command();

	//parser
	mParser = new Parser();

	//server address
	mServerIP = serverIP;
	mServerPort = serverPort;

	//sequences
	mOutgoingSequence		= 1;
	mIncomingSequence		= 0;

//	mSocket = open();

//	setSendToAddress(mServerIP,mServerPort);

	//parse
	mIncomingSequence = 0;
	mDroppedPackets = 0;

	//LogString("Server's information: IP address: %s, port: %d", mServerIP, mServerPort);
}


/***************************************
*   		MEMBER VARIABLES
***************************************/

//game
Game mGame;


//command
Command mCommandToServer;
Command mLastCommandToServer;

//parser
Parser mParser;

//server address
byte[] mServerIP;
int mServerPort;

//sequences
short	mOutgoingSequence;		// OutFgoing packet sequence
short	mIncomingSequence;		// Incoming packet sequence
short	mDroppedPackets;			// Dropped packets


//graphics
//GraphicsOgre mGraphicsOgre;

/***************************************
*			          METHODS
***************************************/

}
