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
//	parseByteBuffer(byteBuffer);

	//ghost
	mGhost = null;

}

/************************************************
*                VARIABLES
*************************************************/

//game
Game mGame;

//mesh
int mMeshCode;

//animate
boolean mAnimate;

//parser
Parser mParser;

//speed
float mSpeed;
float mSpeedMax;

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
Command mServerFrame;					// the latest frame from server
Command mCommandToRunOnShape;

/*************************************************
*				METHODS
**************************************************/

//abilitys
void     addAbility(Ability ability)
{

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
void processTick()
{

}
void interpolateTick(float renderTime)
{

}

//messaging
void readDeltaMoveCommand(ByteBuffer byteBuffer)
{

}

void parseByteBuffer(ByteBuffer byteBuffer)
{

	//byteBuffer->BeginReading();
	System.out.println("before");
	byteBuffer.flip();
	System.out.println("type:" + byteBuffer.get()); //should read -103 to add a shape..

	mLocal	=    byteBuffer.get(); //error
				System.out.println("after2");
	mIndex		=    byteBuffer.get();

	mPosition.x =   byteBuffer.getFloat();
	mPosition.y =   byteBuffer.getFloat();
	mPosition.z =   byteBuffer.getFloat();

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
void moveGhostShape()
{

}


}


