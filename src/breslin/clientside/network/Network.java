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
***************************************/

//packets
boolean checkForDispatch(Dispatch dispatch)
{
   try
    {
		ByteBuffer buf = ByteBuffer.allocate(48);
		buf.clear();

		if (mDatagramChannel.receive(buf) != null)
		{
			buf.flip();  //this sets marker to beginning of buffer just like BeginReading in c++.
			System.out.println("first byte:" + buf.get());
			System.out.println("2nd byte:" + buf.get());
			System.out.println("3d byte:" + buf.get());
		}
	}
	catch (Exception ex)
	{
        System.err.println("bres:" + ex);
    }

	return false;
}

public void readPackets   ()
{
	//int type;
	//int ret;

	Dispatch dispatch = new Dispatch();

	while(checkForDispatch(dispatch))
	{
		//dispatch->BeginReading();

		int type = dispatch.ReadByte();

		if (mParser.mMessageAddShape == type)
		{
			mGame.addShape(true,dispatch);
		}
/*
		switch(type)
		{
			case mParser.mMessageAddShape:
				mGame.addShape(true,dispatch);
			break;

			case mParser.mMessageRemoveShape:
				mGame.removeShape(dispatch);
			break;

			case mParser.mMessageFrame:
				mGame.readServerTick(dispatch);
			break;

			//case mParser.mMessageServerExit:
			//	mGame.shutdown();
			break;
		}
*/
	}

}


//send


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


