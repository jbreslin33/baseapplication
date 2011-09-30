package breslin.clientside.shape;

/***************************************
*           INCLUDES
***************************************/
//standard library
import java.util.ArrayList;
import java.nio.ByteBuffer;

//shape
import breslin.clientside.shape.Shape;

//game
import breslin.clientside.game.Game;

//math
import breslin.math.Vector3D;

//ability
import breslin.clientside.ability.Ability;

//parser
import breslin.clientside.parser.Parser;

//command
import breslin.clientside.command.Command;


/***************************************
*           FORWARD DECLARATIONS
***************************************/


/**********************************
*          CLASS
**********************************/

public class ShapeDynamic extends Shape
{

public ShapeDynamic(Game game, ByteBuffer byteBuffer)
{
	super();

	//game
	mGame = game;

	//parser
	mParser = new Parser();

	//commands
	mServerFrame         = new Command();
	mCommandToRunOnShape = new Command();

	//speed
	mSpeed     = 0;
	mSpeedMax  = 200;

	//orientation
	mPosition = new Vector3D();
	mVelocity = new Vector3D();
	mRotation = new Vector3D();

	//mesh
	mMeshCode = 0;

	//animate
	mAnimate = false;

	//byteBuffer
	parseByteBuffer(byteBuffer);

	//ghost
	mGhost = null;

}

/************************************************
*                VARIABLES
*************************************************/

//game
public Game mGame;

//mesh
int mMeshCode;

//animate
boolean mAnimate;

//parser
Parser mParser;

//speed
public float mSpeed;
public float mSpeedMax;

//abilitys
ArrayList<Ability> mAbilityVector = new ArrayList<Ability>();

//this is used to rotate to and for debugging. it goes right to lates serverFrame from net.
public ShapeDynamic mGhost;

//basic
Vector3D mPosition;
Vector3D mVelocity;
Vector3D mRotation;
int mLocal;

//commands
public Command mServerFrame;					// the latest frame from server
public Command mCommandToRunOnShape;

/*************************************************
*				METHODS
**************************************************/

//abilitys
public void     addAbility(Ability ability)
{
	mAbilityVector.add(ability);
}

Ability getAbility(Ability ability)
{

	return new Ability();
}

//movement
public void   yaw                  (float amountToYaw, boolean converToDegree   )
{

}
public float  getDegreesToSomething(Vector3D something                       )
{
	return 0;
}
void   translate            (Vector3D translateVector, int perspective)
{

}
String getName()
{
	return new String();

}
float  getSpeed()
{
	return 0;
}

//ticks
public void processTick()
{
	clearTitle(); //empty title string so it can be filled anew
	//process ticks on abilitys
	for (int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.get(i).processTick();
	}

	//run billboard here for now.
	drawTitle();
}

public void interpolateTick(float renderTime)
{
	//interpolate ticks on abilitys
	for (int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.get(i).interpolateTick(renderTime);
	}
}

//messaging
public void readDeltaMoveCommand(ByteBuffer byteBuffer)
{
	//ShapeDynamic* shape = NULL;

	int flags = 0;

	boolean moveXChanged = true;
	boolean moveYChanged = true;
	boolean moveZChanged = true;

	// Flags
	flags = byteBuffer.get();

	// Origin
	int i = flags & mParser.mCommandOriginX;
	if(i == 4)
	{
		mServerFrame.mPositionOld.x = mServerFrame.mPosition.x;


		int p = byteBuffer.position();  //set current position to p

		//get the next 4 bytes
		byte one = byteBuffer.get(p);
		byte two = byteBuffer.get(p + 1);
		byte three = byteBuffer.get(p +2);
		byte four = byteBuffer.get(p + 3);

		//flip them
		byteBuffer.put(p,four);
		byteBuffer.put(p + 1,three);
		byteBuffer.put(p + 2,two);
		byteBuffer.put(p + 3,one);

		//set position back to original
		byteBuffer.position(p);

		//get 4 bytes put them into a java int
		int a = byteBuffer.getInt();

		//covert java int to float
		float b = Float.intBitsToFloat(a);
		mServerFrame.mPosition.x = b;
	}
	else
	{
		moveXChanged = false;
	}

	i = flags & mParser.mCommandOriginY;
	if(i == 8)
	{
		mServerFrame.mPositionOld.y = mServerFrame.mPosition.y;


		int p = byteBuffer.position();  //set current position to p

		//get the next 4 bytes
		byte one = byteBuffer.get(p);
		byte two = byteBuffer.get(p + 1);
		byte three = byteBuffer.get(p +2);
		byte four = byteBuffer.get(p + 3);

		//flip them
		byteBuffer.put(p,four);
		byteBuffer.put(p + 1,three);
		byteBuffer.put(p + 2,two);
		byteBuffer.put(p + 3,one);

		//set position back to original
		byteBuffer.position(p);

		//get 4 bytes put them into a java int
		int a = byteBuffer.getInt();

		//covert java int to float
		float b = Float.intBitsToFloat(a);
		mServerFrame.mPosition.y = b;
	}
	else
	{
		moveYChanged = false;
	}

	i = flags & mParser.mCommandOriginZ;
	if(i == 16)
	{
		mServerFrame.mPositionOld.z = mServerFrame.mPosition.z;


		int p = byteBuffer.position();  //set current position to p

		//get the next 4 bytes
		byte one = byteBuffer.get(p);
		byte two = byteBuffer.get(p + 1);
		byte three = byteBuffer.get(p +2);
		byte four = byteBuffer.get(p + 3);

		//flip them
		byteBuffer.put(p,four);
		byteBuffer.put(p + 1,three);
		byteBuffer.put(p + 2,two);
		byteBuffer.put(p + 3,one);

		//set position back to original
		byteBuffer.position(p);

		//get 4 bytes put them into a java int
		int a = byteBuffer.getInt();

		//covert java int to float
		float b = Float.intBitsToFloat(a);
		mServerFrame.mPosition.z = b;
	}
	else
	{
		moveZChanged = false;
	}


	//rotation
	i = flags & mParser.mCommandRotationX;
	if(i == 32)
	{
		mServerFrame.mRotOld.x = mServerFrame.mRot.x;

		int p = byteBuffer.position();  //set current position to p

		//get the next 4 bytes
		byte one = byteBuffer.get(p);
		byte two = byteBuffer.get(p + 1);
		byte three = byteBuffer.get(p +2);
		byte four = byteBuffer.get(p + 3);

		//flip them
		byteBuffer.put(p,four);
		byteBuffer.put(p + 1,three);
		byteBuffer.put(p + 2,two);
		byteBuffer.put(p + 3,one);

		//set position back to original
		byteBuffer.position(p);

		//get 4 bytes put them into a java int
		int a = byteBuffer.getInt();

		//covert java int to float
		float b = Float.intBitsToFloat(a);
		mServerFrame.mRot.x = b;
	}

	i = flags & mParser.mCommandRotationZ;
	if(i == 64)
	{
		mServerFrame.mRotOld.z = mServerFrame.mRot.z;

		int p = byteBuffer.position();  //set current position to p

		//get the next 4 bytes
		byte one = byteBuffer.get(p);
		byte two = byteBuffer.get(p + 1);
		byte three = byteBuffer.get(p +2);
		byte four = byteBuffer.get(p + 3);

		//flip them
		byteBuffer.put(p,four);
		byteBuffer.put(p + 1,three);
		byteBuffer.put(p + 2,two);
		byteBuffer.put(p + 3,one);

		//set position back to original
		byteBuffer.position(p);

		//get 4 bytes put them into a java int
		int a = byteBuffer.getInt();

		//covert java int to float
		float b = Float.intBitsToFloat(a);
		mServerFrame.mRot.z = b;
	}

	i = flags & mParser.mCommandMilliseconds;
	//milliseconds
	if (i == 2)
	{
		mServerFrame.mMilliseconds = byteBuffer.get();
		mCommandToRunOnShape.mMilliseconds = mServerFrame.mMilliseconds;
	}


	if (mServerFrame.mMilliseconds != 0)
	{
		//position
		if (moveXChanged)
		{
			mServerFrame.mMoveVelocity.x = mServerFrame.mPosition.x - mServerFrame.mPositionOld.x;
		}
		else
		{
			mServerFrame.mMoveVelocity.x = 0.0f;
		}

		if (moveYChanged)
		{
			mServerFrame.mMoveVelocity.y = mServerFrame.mPosition.y - mServerFrame.mPositionOld.y;
		}
		else
		{
			mServerFrame.mMoveVelocity.y = 0.0f;
		}

		if (moveZChanged)
		{
			mServerFrame.mMoveVelocity.z = mServerFrame.mPosition.z - mServerFrame.mPositionOld.z;
		}
		else
		{
			mServerFrame.mMoveVelocity.z = 0.0f;
		}
	}
	processTick();
}

void parseByteBuffer(ByteBuffer byteBuffer)
{
	byteBuffer.position(0);

	byteBuffer.get(); //type should be -103

	mLocal	    = byteBuffer.get(); //error
	mIndex		= byteBuffer.get();

	mPosition.x = byteBuffer.getFloat();
	mPosition.y = byteBuffer.getFloat();
	mPosition.z = byteBuffer.getFloat();

	mVelocity.x = byteBuffer.getFloat();
	mVelocity.y = byteBuffer.getFloat();
	mVelocity.z = byteBuffer.getFloat();
	mRotation.x = byteBuffer.getFloat();
	mRotation.z = byteBuffer.getFloat();

	//mesh
	mMeshCode    = byteBuffer.get();

	//animate
	int animate = byteBuffer.get();
	if (animate == 1)
	{
		mAnimate = true;
	}
	else
	{
		mAnimate = false;
	}

}

//ghost
public void moveGhostShape()
{
	Vector3D transVector = new Vector3D();

	transVector.x = mServerFrame.mPosition.x;
	transVector.y = 0;
	transVector.z = mServerFrame.mPosition.z;

	if (mGhost != null)
	{
		mGhost.setPosition(transVector);
	}
}


}


