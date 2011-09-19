package breslin.clientside.network;

/***************************************
*   		INCLUDES
***************************************/
//standard library
import java.io.*;
import java.net.*;

//nonblocking receive
import java.net.SocketAddress;
import java.net.InetSocketAddress;
import java.nio.channels.DatagramChannel;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.CharBuffer;

//game
import breslin.clientside.game.Game;


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
	mClientPort = 30003;

	//sequences
	mOutgoingSequence		= 1;
	mIncomingSequence		= 0;

	//parse
	mIncomingSequence = 0;
	mDroppedPackets = 0;


	try
	{
		String serverIPString = new String(mServerIP, "UTF8");
		System.out.println("NETWORK CONSTRUCTOR: serverIP:" + serverIPString + " serverPort:" + serverPort);

	}
	catch (UnsupportedEncodingException e)
	{
	    e.printStackTrace();
	}

	//for nonblocking recieve
	try
	{
    	//lets setup one for client and then get the port as this will be used for sending and recieving henceforth and it will
    	//be what port the serverside will think we are using. So we better be listening on it and sending on it! let's bind to it.
    	//we will also make it non-blocking to avoid threading our game loop.
       	mInetSocketAddressClient = new InetSocketAddress(0);
       	mClientPort = mInetSocketAddressClient.getPort();

		//DatagramChannel to be used for send and reviece
	    mDatagramChannel = DatagramChannel.open();
		mDatagramChannel.socket().bind(new InetSocketAddress(mClientPort));
		mDatagramChannel.configureBlocking(false);

		//lets setup a SocketAddress for server so we can send,
		//let's also connect to it so we can avoid overhead of security check

		String mServerIPString = new String(mServerIP, "UTF8");
		mInetSocketAddressServer = new InetSocketAddress(mServerIPString, 30004);
    	mDatagramChannel.connect(mInetSocketAddressServer);

	}
	catch (IOException ioe)
	{
		System.out.println("ERROR in nonblocking socket in network constructor");
	}

}


/***************************************
*   		MEMBER VARIABLES
***************************************/

//game
Game mGame;

//nonblocking recieve
DatagramChannel mDatagramChannel;
InetSocketAddress   mInetSocketAddressClient;
InetSocketAddress   mInetSocketAddressServer;
//DatagramSocket  mDatagramSocket;

//command
public Command mCommandToServer;
public Command mLastCommandToServer;

//parser
Parser mParser;

//server address
byte[] mServerIP;
String mServerIPString;
int mServerPort;
int mClientPort;

//sequences
short	mOutgoingSequence;		// OutFgoing packet sequence
short	mIncomingSequence;		// Incoming packet sequence
short	mDroppedPackets;			// Dropped packets


//graphics
//GraphicsOgre mGraphicsOgre;

/***************************************
*			          METHODS
*
*
*
*
***************************************/

/***************************************
*   		RECIEVE PACKETS
***************************************/

public void readPackets()
{



	ByteBuffer byteBuffer = ByteBuffer.allocate(1400);
	while(checkForByteBuffer(byteBuffer))
	{

		byteBuffer.position(0); //BeginReading() c++ equivalent

		int type = byteBuffer.get();


		if (mParser.mMessageConnect == type)
		{
			//System.out.println("connect message -101 recieved");
		}

		if (mParser.mMessageAddShape == type)
		{
			mGame.addShape(true,byteBuffer);
		}

		if (mParser.mMessageRemoveShape == type)
		{
			mGame.removeShape(byteBuffer);
		}

		if (mParser.mMessageFrame == type)
		{
			mGame.readServerTick(byteBuffer);
		}

		if (mParser.mMessageServerExit == type)
		{
			//	mGame.shutdown();
		}
		byteBuffer.clear();
	}
}

boolean checkForByteBuffer(ByteBuffer byteBuffer)
{
   try
    {
		if (mDatagramChannel.receive(byteBuffer) != null)
		{

			byteBuffer.position(0);  //this sets marker to beginning of buffer just like BeginReading in c++.

			// Parse system messages
			parsePacket(byteBuffer);
			return true;
		}
		else
		{



			return false;
		}
	}
	catch (Exception ex)
	{
        System.err.println("bres:" + ex);
    }
    return false;
}

void parsePacket(ByteBuffer byteBuffer)
{

	byteBuffer.position(0);

	int type = byteBuffer.get();
	// Check if the type is a positive number
	// = is the packet sequenced
	if(type > 0)
	{
		short sequence		= byteBuffer.getShort();

		if(sequence <= mIncomingSequence)
		{
			System.out.println("Client..Sequence mismatch");

		}
		//mDroppedPackets = sequence - mIncomingSequence + add1;

		mIncomingSequence = sequence;
	}

}

/***************************************
*   		SEND PACKETS
***************************************/


public void sendConnect()
{
	byte[] mCharArray = new byte[1400];
	ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);
	byteBuffer.put(mParser.mMessageConnect);
	send(byteBuffer);
}

public void sendCommand()
{

}


public void send(ByteBuffer byteBuffer)
{
	try
  	{
      	byteBuffer.flip(); //get buffer ready for send, sets mark to beginning.
		mDatagramChannel.write(byteBuffer); //write to channel you are connecting to.
	}
    catch (Exception e)
    {
      	System.err.println(e);
    }
}

}


