package breslin.clientside.network;

/***************************************
*   		INCLUDES
***************************************/
//standard library
import java.io.*;
import java.net.*;

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


	try
	{
		String mServerIPString = new String(mServerIP, "UTF8");
		System.out.println("NETWORK CONSTRUCTOR: serverIP:" + mServerIPString + " serverPort:" + serverPort);

	}
	catch (UnsupportedEncodingException e)
	{
	    e.printStackTrace();
	}
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
String mServerIPString;
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

public void sendConnect()
{
	Dispatch dispatch = new Dispatch();
	dispatch.WriteByte(mParser.mMessageConnect);
	send(dispatch);
}

public void send(Dispatch dispatch)
{
	try
  	{
     	// Get the internet address of the specified host
      	InetAddress address = InetAddress.getByName("localhost");

      	// Initialize a datagram packet with data and address
      	DatagramPacket packet = new DatagramPacket(dispatch.getByteArray(), dispatch.getByteArray().length,
      	    address, mServerPort);

      	// Create a datagram socket, send the packet through it, close it.
      	DatagramSocket dsocket = new DatagramSocket();
      	dsocket.send(packet);
      	dsocket.close();
	}
    catch (Exception e)
    {
      	System.err.println(e);
    }
}



}


