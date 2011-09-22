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
short mIncomingSequence;		// Incoming packet sequence
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
			System.out.println("BRESSAGE: mMessageConnect");
		}

		if (mParser.mMessageAddShape == type)
		{
			mGame.addShape(true,byteBuffer);
			System.out.println("BRESSAGE: mMessageAddShape");
		}

		if (mParser.mMessageRemoveShape == type)
		{
			mGame.removeShape(byteBuffer);
			System.out.println("BRESSAGE: mMessageRemoveShape");
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
	//bools
	boolean sendKey          = false;
	boolean sendMilliseconds = false;

	//create byteBuffer
   	byte[] mCharArray = new byte[1400];
	ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);

	//WRITE: type
	byteBuffer.put(mParser.mMessageFrame);  //type

	//WRITE: sequence
	byteBuffer.putShort(mOutgoingSequence);  //sequence
	byte one = byteBuffer.get(1);
	byte two = byteBuffer.get(2);
	byteBuffer.put(1,two);
	byteBuffer.put(2,one);

	// Build delta-compressed move command
	int flags = 0;

	// Check what needs to be updated
	if(mLastCommandToServer.mKey != mCommandToServer.mKey)
	{
		sendKey = true;
		flags |= mParser.mCommandKey;
	}
	System.out.println("_______________________________________");
	System.out.println("mLastCommandToServer.mMilliseconds:" + mLastCommandToServer.mMilliseconds);
	System.out.println("mCommandToServer.mMilliseconds:" + mCommandToServer.mMilliseconds);
	if(mLastCommandToServer.mMilliseconds != mCommandToServer.mMilliseconds)
	{
		sendMilliseconds = true;
		System.out.println("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		flags |= mParser.mCommandMilliseconds;
	}


	// Add to the message
	byteBuffer.put((byte)flags);

	//int x = flags & mParser.mCommandKey;
	//if(x == 1)
	if (sendKey)
	{
		System.out.println("KKKKKKKKKKKKKKKKKKKKKKKKKKKK");
		//WRITE: key
		byteBuffer.put((byte)mCommandToServer.mKey);
	}

	//int y = flags & mParser.mCommandMilliseconds;
	//if(y == 1)
	if (sendMilliseconds)
	{
		//WRITE: milliseconds
		System.out.println("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
		byteBuffer.put((byte)mCommandToServer.mMilliseconds);
	}

	//set 'last' commands for diff
	mLastCommandToServer.mKey = mCommandToServer.mKey;
	mLastCommandToServer.mMilliseconds = mCommandToServer.mMilliseconds;

	// Send the packet
	send(byteBuffer);
}


public void reset()
{
    mOutgoingSequence                = 1;
    mIncomingSequence                = 0;
}

public void send(ByteBuffer byteBuffer)
{
	try
  	{
/*
     		byteBuffer.position(0);

      		System.out.println("$type:" + byteBuffer.get());


			byte one = byteBuffer.get(1);
			byte two = byteBuffer.get(2);
			byteBuffer.put(1,two);
			byteBuffer.put(2,one);
			byteBuffer.position(1);
            System.out.println("$seq:" + byteBuffer.getShort());

			byte flags = byteBuffer.get();
			System.out.println("$flags:" + flags);

			int x = flags & mParser.mCommandKey;
			if(x == 1)
			{
				System.out.println("$key:" + byteBuffer.get());
			}


			x = flags & mParser.mCommandMilliseconds;
			if(x == 1)
			{
				System.out.println("$mil:" + byteBuffer.get());
			}
*/
      	byteBuffer.position(0);

		mDatagramChannel.write(byteBuffer); //write to channel you are connecting to.
	}
    catch (Exception e)
    {
      	System.err.println(e);
    }



byteBuffer.position(0);

	int type = byteBuffer.get();
	// Check if the type is a positive number
	// = is the packet sequenced
	if(type > 0)
	{

		mOutgoingSequence++;
	}
}

}


