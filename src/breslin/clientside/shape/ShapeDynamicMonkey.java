package breslin.clientside.shape;

/**********************************
*          INCLUDES
**********************************/
//parent
import breslin.clientside.shape.ShapeDynamic;

//standard library
import java.util.ArrayList;
import java.nio.ByteBuffer;
import java.lang.String;

  // geometry
  import com.jme3.material.Material;
  import com.jme3.math.Vector3f;
  import com.jme3.scene.Geometry;
  import com.jme3.scene.shape.Box;
  import com.jme3.math.ColorRGBA;

//shape
import breslin.clientside.shape.Shape;

//game
import breslin.clientside.game.GameMonkey;

//math
import breslin.math.Vector3D;

//ability
import breslin.clientside.ability.Ability;

//parser
import breslin.clientside.parser.Parser;

//command
import breslin.clientside.command.Command;



/**********************************
*          CLASS
**********************************/
public class ShapeDynamicMonkey extends ShapeDynamic //, public OgreAnimation
{


public ShapeDynamicMonkey(GameMonkey gameMonkey, ByteBuffer byteBuffer, boolean isGhost)
{
	super(gameMonkey,byteBuffer);

	System.out.println("creating a monkey shape in constructor.");
	//we use this to name shape. as ogre is picky about same names. it also serves as a counter of sorts.

	mGameMonkey = gameMonkey;

	mIsGhost = isGhost;

	if (mIsGhost)
	{
		mIndex = mIndex * -1;
	}

	//figure out mesh based on code passed in byteBuffer
	mMeshName = getMeshString(mMeshCode);


	createShape();

	//animation
	//if (mAnimate)
	//{
	//	addAbility(new AbilityAnimationOgre(this));
	//}

	//setupTitle();

	//call create ghost here..
	if (!mIsGhost)
	{
		//create a ghost for this shape
		mGhost = new ShapeDynamicMonkey(mGameMonkey,byteBuffer,true);
		//mGhost->setVisible(false);

		//put shape and ghost in game vectors so they can be looped and game now knows of them.
		mGame.mShapeVector.add(this);
		mGame.mShapeGhostVector.add(mGhost);
	}


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

 	Box b = new Box(Vector3f.ZERO, 1, 1, 1);
    Geometry geom = new Geometry("Box", b);
    Material mat = new Material(mGameMonkey.mGraphicsMonkey.getAssetManager(), "Common/MatDefs/Misc/Unshaded.j3md");
    mat.setColor("Color", ColorRGBA.Blue);
    geom.setMaterial(mat);
    mGameMonkey.mGraphicsMonkey.getRootNode().attachChild(geom);

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
public void yaw        (float amountToYaw, boolean converToDegree   )
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



String getMeshString(int meshCode)
{

	if (meshCode == 0)
	{
		mScale = 1;
		return "cube.mesh";
	}
	if (meshCode == 1)
	{
		mScale = 30;
		return "sinbad.mesh";
	}
	return "cube.mesh";
}

}
