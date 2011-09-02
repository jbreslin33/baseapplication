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

//dispatch
import breslin.clientside.bytebuffer.Dispatch;

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


	//for nonblocking recieve
	try
	{
    	//lets setup one for client and then get the port as this will be used for sending and recieving henceforth and it will
    	//be what port the serverside will think we are using. So we better be listening on it and sending on it!
       	mInetSocketAddressClient = new InetSocketAddress(0);
       	mClientPort = mInetSocketAddressClient.getPort();

		//DatagramChannel to be used for send and reviece
	    mDatagramChannel = DatagramChannel.open();
		mDatagramChannel.socket().bind(new InetSocketAddress(mClientPort));
		mDatagramChannel.configureBlocking(false);

		//lets setup a SocketAddress for server so we can send,
		//let's also connect to it so we can avoid overhead of security check
		mInetSocketAddressServer = new InetSocketAddress("192.168.1.103", 30004);
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
Command mCommandToServer;
Command mLastCommandToServer;

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
	while(checkForDispatch(byteBuffer))
	{

		byteBuffer.flip(); //BeginReading() c++ equivalent

		int type = byteBuffer.get();
		System.out.println("type:" + type);

		if (mParser.mMessageConnect == type)
		{
			System.out.println("connect message -101 recieved");
		}

		if (mParser.mMessageAddShape == type)
		{
			System.out.println("addShape");
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

boolean checkForDispatch(ByteBuffer byteBuffer)
{
   try
    {
		//byteBuffer.clear();

		if (mDatagramChannel.receive(byteBuffer) != null)
		{

			//byteBuffer.flip();  //this sets marker to beginning of buffer just like BeginReading in c++.

			// Parse system messages
			//parsePacket(byteBuffer);
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
/*
	mes->BeginReading();

	int type = mes->ReadByte();

	// Check if the type is a positive number
	// = is the packet sequenced
	if(type > 0)
	{
		unsigned short sequence		= mes->ReadShort();

		if(sequence <= mIncomingSequence)
		{
			LogString("Client: (sequence: %d <= incoming seq: %d)",
				sequence, mIncomingSequence);

			LogString("Client: Sequence mismatch");
		}

		mDroppedPackets = sequence - mIncomingSequence + 1;

		mIncomingSequence = sequence;
	}
	*/
}

/***************************************
*   		SEND PACKETS
***************************************/


public void sendConnect()
{
	Dispatch dispatch = new Dispatch();
	dispatch.WriteByte(mParser.mMessageConnect);
	send(dispatch);
}

public void sendCommand()
{

}

public void send(Dispatch dispatch)
{
	try
  	{
      	dispatch.mByteBuffer.flip(); //get buffer ready for send, sets mark to beginning.
		mDatagramChannel.write(dispatch.mByteBuffer); //write to channel you are connecting to.
	}
    catch (Exception e)
    {
      	System.err.println(e);
    }
}



}


