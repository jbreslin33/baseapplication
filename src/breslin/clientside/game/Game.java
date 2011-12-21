package breslin.clientside.game;

/***************************************
*           INCLUDES
***************************************/

//state machine
import breslin.statemachine.StateMachine;
import breslin.statemachine.State;

//states
import breslin.clientside.game.states.GameGlobal;
import breslin.clientside.game.states.GameInitialize;
import breslin.clientside.game.states.GamePlay;
import breslin.clientside.game.states.GamePause;

//applicationBreslin
import breslin.clientside.application.ApplicationBreslin;

//shape
import breslin.clientside.shape.Shape;

//ability
import breslin.clientside.ability.rotation.AbilityRotation;
import breslin.clientside.ability.move.AbilityMove;

//standard library
import java.io.*;
import java.util.ArrayList;
import java.nio.ByteBuffer;
import com.jme3.math.Vector3f;

//keyboard
import org.lwjgl.input.Keyboard;



/***************************************
*           CLASS
***************************************/
public class Game
{


public Game(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;

//Shapes
mShapeVector = new ArrayList<Shape>(); //all shapes in the client world
mShapeGhostVector = new ArrayList<Shape>(); //all shapes in the client world's ghost


	//keys
	mKeyUp = 1;
	mKeyDown = 2;
	mKeyLeft = 4;
	mKeyRight = 8;
	mKeyCounterClockwise = 16;
	mKeyClockwise = 32;

	//input
	mKeyCurrent = 0;
	mKeyLast = 0;
	mMillisecondsCurrent = 0;
	mMillisecondsLast = 0;

	//sequence
        mOutgoingSequence               = 1;

	//time
    mFrameTime = 0.0f;
    mRunNetworkTime = 0.0f;


	mStateMachine = new StateMachine();
	mGameGlobal = new GameGlobal(this);
	mGameInitialize = new GameInitialize(this);
	mGamePlay = new GamePlay(this);
	mGamePause = new GamePause(this);

	mStateMachine.setGlobalState(mGameGlobal);
	mStateMachine.changeState(mGamePlay);

	//set Camera
	// Position it at 500 in Z direction
	Vector3f startCamPosition = new Vector3f(0, 20, 20);
    Vector3f lookAtVector     = new Vector3f(0,0,0);
    Vector3f worldDirection   = new Vector3f(0,1,0);
    mApplicationBreslin.getCamera().setLocation(startCamPosition);
    mApplicationBreslin.getCamera().lookAt(lookAtVector,worldDirection);

}

/***************************************
*   		MEMBER VARIABLES
***************************************/

//states
StateMachine mStateMachine;

State mGameGlobal;
State mGameInitialize;
State mGamePlay;
State mGamePause;

public static final byte mCommandKey          = 1;
public static final byte mCommandMilliseconds = 2;
public static final byte mMessageFrame = 1;
public static final byte mMessageAddShape    = -103;
public static final byte mMessageRemoveShape = -104;


//applicationBreslin
public ApplicationBreslin mApplicationBreslin;

//Shapes
public ArrayList<Shape> mShapeVector = new ArrayList<Shape>(); //all shapes in the client world
public ArrayList<Shape> mShapeGhostVector = new ArrayList<Shape>(); //all shapes in the client world's ghost


//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;

//key input
int mKeyCurrent;
int mKeyLast;
int mMillisecondsCurrent;
int mMillisecondsLast;

//sequences
short	mOutgoingSequence;

//time
float mFrameTime;
float mRunNetworkTime;



/***************************************
*   		METHODS
***************************************/


/***************************************
*   		Update
***************************************/


public void processUpdate()
{
	mStateMachine.update();

	for (int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.get(i).interpolateTick(mApplicationBreslin.getRenderTime());
	}
}


/***************************************
*   		Shapes
***************************************/

public void addShape(boolean b, ByteBuffer byteBuffer)
{
	System.out.println("addShape");
	Shape shape = new Shape(mApplicationBreslin,byteBuffer,false);  //you should just need to call this...

	//ability
	shape.addAbility(new AbilityRotation(shape));
	shape.addAbility(new AbilityMove    (shape));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector.add(shape);
	mShapeGhostVector.add(shape.mGhost);
}

public Shape getShape(int id)
{
	Shape shape = null;

	for (int i = 0; i < mShapeVector.size(); i++)
	{
		Shape curShape = mShapeVector.get(i);
		if (curShape.mIndex == id)
		{
			shape = curShape;
		}
	}

	if(shape == null)
	{
		return null;
	}
	else
	{
		return shape;
	}
}

public void removeShape(ByteBuffer byteBuffer)
{

}

/*********************************
		Network
**********************************/

public void checkForByteBuffer()
{

	int type = 0;

	ByteBuffer byteBuffer = ByteBuffer.allocate(1400);

	while(mApplicationBreslin.mNetwork.checkForByteBuffer(byteBuffer))
    {
		byteBuffer.position(0); //BeginReading() c++ equivalent

		type = byteBuffer.get();

		if (mMessageAddShape == type)
		{
			addShape(true,byteBuffer);
		}

		if (mMessageRemoveShape == type)
		{
			removeShape(byteBuffer);
		}

		if (mMessageFrame == type)
		{
			readServerTick(byteBuffer);
		}

		byteBuffer.clear();
	}
}



private void readServerTick(ByteBuffer byteBuffer)
{

	// Skip sequences
	byte one = byteBuffer.get(1);
	byte two = byteBuffer.get(2);
	byteBuffer.put(1,two);
	byteBuffer.put(2,one);
	byteBuffer.position(1);
	short sequence = byteBuffer.getShort();

	boolean validShape = true;

	while (byteBuffer.hasRemaining() && validShape)
	{

		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

		int id = byteBuffer.get();

		Shape shape = null;
		shape = getShape(id);

		if (shape != null)
		{
			shape.processDeltaByteBuffer(byteBuffer);
		}
		else
		{
			validShape = false;
		}
	}
}

public void sendByteBuffer()
{
        //bools
        boolean sendKey          = false;
        boolean sendMilliseconds = false;

        //create byteBuffer
        byte[] mCharArray = new byte[1400];
        ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);

        //WRITE: type
        byteBuffer.put(mMessageFrame);  //type

        //WRITE: sequence
        byteBuffer.putShort(mOutgoingSequence);  //sequence
        mOutgoingSequence++; //increase for next time...

        byte one = byteBuffer.get(1);
        byte two = byteBuffer.get(2);
        byteBuffer.put(1,two);
        byteBuffer.put(2,one);

        // Build delta-compressed move command
        int flags = 0;

        // Check what needs to be updated
        if(mKeyLast != mKeyCurrent)
        {
                sendKey = true;
                flags |= mCommandKey;
        }


        if(mMillisecondsLast != mMillisecondsCurrent)
        {
                sendMilliseconds = true;

                flags |= mCommandMilliseconds;
        }


        // Add to the message
        byteBuffer.put((byte)flags);

        if (sendKey)
        {
                byteBuffer.put((byte)mKeyCurrent);
        }

        if (sendMilliseconds)
        {

                byteBuffer.put((byte)mMillisecondsCurrent);
        }

        //set 'last' commands for diff
        mKeyLast = mKeyCurrent;
        mMillisecondsLast = mMillisecondsCurrent;

        // Send the packet
        mApplicationBreslin.mNetwork.send(byteBuffer);
}

/***************************************
*			INPUT
******************************************/
public void processInput()
{
	mKeyCurrent = 0;

	//move
	if (Keyboard.isKeyDown(Keyboard.KEY_I))
	{
		mKeyCurrent |= mKeyUp;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_K))
	{
		mKeyCurrent |= mKeyDown;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_J))
	{
		mKeyCurrent |= mKeyLeft;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_L))
	{
		mKeyCurrent |= mKeyRight;
	}

	//rotation
	if (Keyboard.isKeyDown(Keyboard.KEY_G))
	{
		mKeyCurrent |= mKeyCounterClockwise;
	}

	if (Keyboard.isKeyDown(Keyboard.KEY_H))
	{
		mKeyCurrent |= mKeyClockwise;
	}

	mMillisecondsCurrent = (byte) (mFrameTime * 1000);
}


}
