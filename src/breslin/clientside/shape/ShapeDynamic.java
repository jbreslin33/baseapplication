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

}

/************************************************
*                VARIABLES
*************************************************/

//game
Game mGame;

//parser
Parser mParser;

//speed
float mSpeed;
float mSpeedMax;

//abilitys
ArrayList<Ability> mAbilityVector = new ArrayList<Ability>();

//this is used to rotate to and for debugging. it goes right to lates serverFrame from net.
ShapeDynamic mGhost;

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
void   yaw                  (float amountToYaw, boolean converToDegree   )
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

//dispatch
void parseDispatch(ByteBuffer byteBuffer)
{

}

//ghost
void moveGhostShape()
{

}


}


