package breslin.clientside.shape;

/**********************************
*          INCLUDES
**********************************/
//parent
import breslin.clientside.shape.ShapeDynamic;

//standard library
import java.util.ArrayList;

//shape
import breslin.clientside.shape.Shape;

//game
import breslin.clientside.game.GameMonkey;

//math
import breslin.math.Vector3D;

//dispatch
import breslin.clientside.bytebuffer.Dispatch;

//ability
import breslin.clientside.ability.Ability;

//parser
import breslin.clientside.parser.Parser;

//command
import breslin.clientside.command.Command;



/**********************************
*          CLASS
**********************************/
class ShapeDynamicMonkey extends ShapeDynamic //, public OgreAnimation
{


public ShapeDynamicMonkey(GameMonkey gameMonkey, Dispatch dispatch, boolean isGhost)
{
	super(gameMonkey,dispatch);
}

/**********************************
*          VARIABLES
**********************************/

//game
GameMonkey mGameMonkey;

//ghost
boolean mIsGhost;

//ogre scene stuff
String        mMeshName;
String         mName;
//Entity*             mEntity;

//this is your pointer to move shape, really all you need.
//SceneNode*          mSceneNode;

//billboard
//ObjectTitle* mObjectTitle;
//std::string  mObjectTitleString;

//ability

/**********************************
*          METHODS
**********************************/
//shape
void createShape()
{

}

//debugging
void checkExtents(Vector3D min)
{

}

//size
void scale(Vector3D scaleVector)
{

}

//movement
void yaw        (float amountToYaw, boolean converToDegree   )
{

}

void translate  (Vector3D translateVector, int perspective)
{

}
void setPosition(Vector3D position                        )
{

}
void setPosition(float x, float y, float z                )
{

}
void setVisible (boolean visible                             )
{

}

//check position
float    getDegreesToSomething(Vector3D something                       )
{
	return 0;
}
Vector3D getPosition          (                                         )
{
	return new Vector3D();
}

//title
void drawTitle    ()
{

}

void appendToTitle(String appendage)
{

}
void appendToTitle(int appendage)
{

}

void clearTitle   ()
{

}

void setupTitle()
{

}


//name
String getName()
{
	return mName;
}

//ogre scene node
//SceneNode*  getSceneNode() { return mSceneNode; }

//utility
//Ogre::Vector3 converToVector3(Vector3D vector3d);

}



