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
float  getDegreesToSomething(Vector3D something                       )
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
//	System.out.println("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
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
	if(i == 1)
	{
		mServerFrame.mPositionOld.x = mServerFrame.mPosition.x;
		mServerFrame.mPosition.x = byteBuffer.getFloat();
	}
	else
	{
		moveXChanged = false;
	}

	i = flags & mParser.mCommandOriginY;
	if(i == 1)
	{
		mServerFrame.mPositionOld.y = mServerFrame.mPosition.y;
		mServerFrame.mPosition.y = byteBuffer.getFloat();
	}
	else
	{
		moveYChanged = false;
	}

	i = flags & mParser.mCommandOriginZ;
	if(i == 1)
	{
		mServerFrame.mPositionOld.z = mServerFrame.mPosition.z;
		mServerFrame.mPosition.z = byteBuffer.getFloat();
	}
	else
	{
		moveZChanged = false;
	}

	//set old rot



	//rotation
	i = flags & mParser.mCommandRotationX;
	if(i == 1)
	{
		mServerFrame.mRotOld.x = mServerFrame.mRot.x;
		mServerFrame.mRot.x = byteBuffer.getFloat();
	}

	i = flags & mParser.mCommandRotationZ;
	if(i == 1)
	{
		mServerFrame.mRotOld.z = mServerFrame.mRot.z;
		mServerFrame.mRot.z = byteBuffer.getFloat();
	}

	i = flags & mParser.mCommandMilliseconds;
	//milliseconds
	if (i == 1)
	{
		System.out.println("dfdf");
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

}


}


