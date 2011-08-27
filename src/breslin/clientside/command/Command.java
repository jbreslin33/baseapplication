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
	mKey = 0;
	mMilliseconds = 0;
	mMillisecondsTotal = 0;
	mClientFrametime = 0.0f;
}

/**************************************************
*			VARIABLES
**************************************************/
Vector3D mOrigin;      //finish origin of frame/tick
Vector3D mOriginOld;   //origin of last frame/tick
Vector3D mVelocity;	//velocity during frame/tick
Vector3D mRot;         //rotation during frame/tick
Vector3D mRotOld;	    //velocity during last frame/tick

float mRotSpeed;

int mKey;               //key pressed
int mMilliseconds;      //not used
int mMillisecondsTotal;      //not used

float mClientFrametime;
/**************************************************
*			METHODS
**************************************************/

}