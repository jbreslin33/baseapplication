package breslin.clientside.command;


/**********************************
*          INCLUDES
**********************************/
//math
import breslin.math.Vector3D;

public class Command
{

public Command()
{
	mPosition     = new Vector3D();
	mPositionOld  = new Vector3D();
	mMoveVelocity = new Vector3D();

	mRot          = new Vector3D();
	mRotOld       = new Vector3D();

	mKey = 0;
	mMilliseconds = 0;
	mMillisecondsTotal = 0;
	mClientFrametime = 0.0f;
}

/**************************************************
*			VARIABLES
**************************************************/
public Vector3D mPosition;      //finish origin of frame/tick
public Vector3D mPositionOld;   //origin of last frame/tick
public Vector3D mMoveVelocity;	//velocity during frame/tick
public Vector3D mRot;         //rotation during frame/tick
public Vector3D mRotOld;	    //velocity during last frame/tick

public float mRotSpeed;

public int mKey;               //key pressed
public int mMilliseconds;      //not used
public int mMillisecondsTotal;      //not used

public float mClientFrametime;
/**************************************************
*			METHODS
**************************************************/

}