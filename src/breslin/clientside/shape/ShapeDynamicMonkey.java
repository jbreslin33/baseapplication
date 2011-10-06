package breslin.clientside.shape;

/**********************************
*          INCLUDES
**********************************/
//parent
import breslin.clientside.shape.ShapeDynamic;

//culling
import com.jme3.scene.Spatial.CullHint;

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
  import com.jme3.scene.Node;
  import com.jme3.math.Quaternion;
  import com.jme3.math.Transform;


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
		//mGhost.setVisible(false);

		//put shape and ghost in game vectors so they can be looped and game now knows of them.
		mGame.mShapeVector.add(this);
		mGame.mShapeGhostVector.add(mGhost);
				//mGhost.setVisible(false);
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
Node          mSceneNode;

//billboard
//ObjectTitle* mObjectTitle;
//std::string  mObjectTitleString;

//ability

/**********************************
*          METHODS
**********************************/
//shape
public void createShape()
{
	//actually create the shape and attach to node.
	mSceneNode = (Node) mGameMonkey.mGraphicsMonkey.getAssetManager().loadModel(getMeshString(mMeshCode));
	mGameMonkey.mGraphicsMonkey.getRootNode().attachChild(mSceneNode);

	//scale
	mSceneNode.scale(mScale,mScale,mScale);

	//move
	setPosition((float)mPosition.x,(float)mPosition.y,(float)mPosition.z);

	if (mIsGhost)
	{
		//mSceneNode.setCullHint(CullHint.Always);
	}



}

//debugging
public void checkExtents(Vector3D min)
{

}

//size
public void scale(Vector3D scaleVector)
{

}

//movement
public void yaw        (float amountToYaw, boolean converToDegree   )
{
		double rads = Math.toRadians(amountToYaw);

/* This quaternion stores a 180 degree rolling rotation */
Quaternion yawQuat = new Quaternion();
yawQuat.fromAngleAxis( (float)rads , new Vector3f(0,1,0) );
/* The rotation is applied: The object rolls by 180 degrees. */
getSceneNode().setLocalRotation( yawQuat );

	//System.out.println("a:" + amountToYaw);
	//double degs = Math.toRadians(amountToYaw);
//	getSceneNode().rotate(0,(float)degs,0);
//	System.out.println("yaw:" + degs);
	//getSceneNode().rotate(0,.1f,0);

//Ogre::Quaternion orientation = getSceneNode()->getOrientation();
//	Ogre::Vector3 vector = orientation * -Vector3::UNIT_Z;

 //Quaternion rot = localTransform.getRotation();
// Transform worldTransform = mSceneNode.getWorldTransform();
// Quaternion rotation = worldTransform.getRotation();
// Vector3f vector = rotation.getRotationColumn(0);


}

public void translate  (Vector3D translateVector, int perspective)
{
	if (perspective == 1)
	{
		//getSceneNode()->translate(converToVector3(translateVector), Ogre::Node::TS_WORLD);
		getSceneNode().move((float)translateVector.x,(float)translateVector.y,(float)translateVector.z);
	}
	if (perspective == 2)
	{
		//getSceneNode()->translate(converToVector3(translateVector), Ogre::Node::TS_LOCAL);
		getSceneNode().move((float)translateVector.x,(float)translateVector.y,(float)translateVector.z);
	}
}
public void setPosition(Vector3D position                        )
{
	getSceneNode().setLocalTranslation((float)position.x,(float)position.y,(float)position.z);
}
public void setPosition(float x, float y, float z                )
{
	//in ogre setPosition is absolute so for jmonkey i could just take the difference?
	//mSceneNode.getPosition();
	getSceneNode().setLocalTranslation(x,y,z);
}
public void setVisible (boolean visible                             )
{
	if (visible)
	{

		getSceneNode().setCullHint(CullHint.Always);
	}
	else
	{
		getSceneNode().setCullHint(CullHint.Never);
	}
}

//calculate how far off we are from some vector
public float getDegreesToSomething(Vector3D something                       )
{

	//fallback
	Vector3D fallback = new Vector3D();
	fallback.x = 0;
	fallback.y = 1;
	fallback.z = 0;

	Transform worldTransform = mSceneNode.getWorldTransform();
	Quaternion quaternion = worldTransform.getRotation();
 	Vector3f vector3f = quaternion.getRotationColumn(0);
 	Vector3D orientation = new Vector3D();
 	orientation.x = vector3f.x;
 	orientation.y = vector3f.y;
 	orientation.z = vector3f.z;

 	System.out.println("x:" + orientation.x);
  	System.out.println("y:" + orientation.y);
 	System.out.println("z:" + orientation.z);

	Quaternion toSomething = orientation.getRotationTo(something,fallback);
	//System.out.println("y:" + toSomething.getY());


	double rads = toSomething.toAngleAxis(vector3f);
//	System.out.println("rads:" + rads);
	double degs = Math.toDegrees(rads);

//	System.out.println("D:" + degs);
	return (float)degs;
/*

   Vector3f axis = new Vector3f();
        float angle = toSomething.toAngleAxis(axis);
        System.out.println("angle:" + angle);
        double degs = Math.toDegrees(angle);
        System.out.println("degs:" + degs);
return (float)degs;
*/
/*
Transform worldTransform = mSceneNode.getWorldTransform();
	Quaternion quaternion = worldTransform.getRotation();
 	Vector3f thisVector = quaternion.getRotationColumn(0);
 	//Vector3D orientation = new Vector3D();

something.normalise();

Vector3f v1 = new Vector3f();
v1.x = something.x;
v1.y = something.y;
v1.z = something.z;
//http://www.justin.tv/bravescast4#/w/1857247760/7


Vector3f v2 = new  Vector3f();

v2 = thisVector.normalize();

float f = v2.angleBetween(v1);
 System.out.println("f:" + f);
 double degs = Math.toDegrees(f);
 return (float)degs;
 //return 0.0f;
*/
}

public Vector3D getPosition          (                                         )
{
	Vector3f vector3f = getSceneNode().getWorldTranslation();
	Vector3D vector3D = new Vector3D();
	vector3D.x = vector3f.x;
	vector3D.y = vector3f.y;
	vector3D.z = vector3f.z;

	return vector3D;
}

//title
public void drawTitle    ()
{

}

public void appendToTitle(String appendage)
{

}
public void appendToTitle(int appendage)
{

}

public void clearTitle   ()
{

}

public void setupTitle()
{

}


//name
public String getName()
{
	return mName;
}

//scene node
public Node  getSceneNode() { return mSceneNode; }

//utility
//Ogre::Vector3 converToVector3(Vector3D vector3d);



public String getMeshString(int meshCode)
{

	if (meshCode == 0)
	{
		mScale = .25f;
		return "cube.mesh";
	}
	if (meshCode == 1)
	{
		mScale = .25f;
		return "art/models/sinbad/Sinbad.mesh.xml";
	}
	return "cube.mesh";
}

}
