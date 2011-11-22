package breslin.clientside.shape;


/**********************************
*          INCLUDES
**********************************/
//game
import breslin.clientside.game.Application;

//math
import breslin.math.Vector3D;

//ability
import breslin.clientside.ability.Ability;

//parser
import breslin.clientside.parser.Parser;

//command
import breslin.clientside.command.Command;


//culling
import com.jme3.scene.Spatial.CullHint;

//standard library
import java.util.ArrayList;
import java.nio.ByteBuffer;
import java.lang.String;
import com.jme3.math.Vector3f;


// geometry
import com.jme3.scene.Spatial;
import com.jme3.material.Material;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.shape.Box;
import com.jme3.scene.shape.Sphere;
import com.jme3.scene.shape.Quad;
import com.jme3.math.ColorRGBA;
import com.jme3.scene.Node;
import com.jme3.math.Quaternion;
import com.jme3.math.Transform;
import com.jme3.texture.Texture;
import com.jme3.asset.TextureKey;

//billboards
import com.jme3.font.BitmapFont;
import com.jme3.font.BitmapText;
import com.jme3.renderer.queue.RenderQueue.Bucket;

/**********************************
*          CLASS
**********************************/

public class Shape
{

public Shape(Application application, ByteBuffer byteBuffer, boolean isGhost)
{
	//application
	mApplication = application;

	//parser
	mParser = new Parser();

	//commands
	mServerFrame         = new Command();
	mCommandToRunOnShape = new Command();

	//speed
	mSpeed     = 0;
	mSpeedMax  = 1.66f;

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

	//JMONKEY
System.out.println("creating a monkey shape in constructor.");
	//we use this to name shape. as ogre is picky about same names. it also serves as a counter of sorts.

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
		mGhost = new Shape(mApplication,byteBuffer,true);
		//mGhost.setVisible(false);

		mGhost.setVisible(true);
	}

}

/************************************************
*                VARIABLES
*************************************************/
//application
public Application mApplication;

//scale
public float mScale;
public int   mIndex;

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
public Shape mGhost;

//basic
Vector3D mPosition;
Vector3D mVelocity;
Vector3D mRotation;
int mLocal;

//commands
public Command mServerFrame;					// the latest frame from server
public Command mCommandToRunOnShape;

//JONKEY

//ghost
boolean mIsGhost;

//ogre scene stuff
String        mMeshName;
String         mName;
//Entity*             mEntity;

//this is your pointer to move shape, really all you need.
Spatial          mSceneNode;

//billboard
BitmapFont mBitmapFont;
BitmapText mBitmapText;

/*************************************************
*				METHODS
**************************************************/

//conversion
float convertIntToFloat(ByteBuffer byteBuffer)
{
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
		return b;
}

//abilitys
public void     addAbility(Ability ability)
{
	mAbilityVector.add(ability);
}

Ability getAbility(Ability ability)
{

	return new Ability();
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
	//Shape* shape = NULL;

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

		mServerFrame.mPosition.x = convertIntToFloat(byteBuffer);
	}
	else
	{
		moveXChanged = false;
	}

	i = flags & mParser.mCommandOriginY;
	if(i == 8)
	{
		mServerFrame.mPositionOld.y = mServerFrame.mPosition.y;

		mServerFrame.mPosition.y = convertIntToFloat(byteBuffer);
	}
	else
	{
		moveYChanged = false;
	}

	i = flags & mParser.mCommandOriginZ;
	if(i == 16)
	{
		mServerFrame.mPositionOld.z = mServerFrame.mPosition.z;

		mServerFrame.mPosition.z = convertIntToFloat(byteBuffer);
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

		mServerFrame.mRot.x = convertIntToFloat(byteBuffer);
	}

	i = flags & mParser.mCommandRotationZ;
	if(i == 64)
	{
		mServerFrame.mRotOld.z = mServerFrame.mRot.z;

		mServerFrame.mRot.z = convertIntToFloat(byteBuffer);
	}

	i = flags & mParser.mCommandMilliseconds;
	//milliseconds
	if (i == 2)
	{
		mServerFrame.mMilliseconds = byteBuffer.get();
		mCommandToRunOnShape.mMilliseconds = mServerFrame.mMilliseconds;
	}

//set rotation direct from here using yaw....
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

	mPosition.x = convertIntToFloat(byteBuffer);
	mPosition.y = convertIntToFloat(byteBuffer);
	mPosition.z = convertIntToFloat(byteBuffer);

	mVelocity.x = convertIntToFloat(byteBuffer);
	mVelocity.y = convertIntToFloat(byteBuffer);
	mVelocity.z = convertIntToFloat(byteBuffer);
	mRotation.x = convertIntToFloat(byteBuffer);
	mRotation.z = convertIntToFloat(byteBuffer);


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


//JMONKEY
/**********************************
*          METHODS
**********************************/
//shape
public void createShape()
{

	if (mMeshCode == 0)
	{

		Box mesh = new Box(Vector3f.ZERO, 1, 1, 1);
		Geometry geom = new Geometry("A shape", mesh);

		mSceneNode = geom;

		Material mat = new Material(mApplication.getAssetManager(),"generic/pictures/ShowNormals.j3md");
		mSceneNode.setMaterial(mat);
		//mGameMonkey.mApplication.getRootNode().attachChild(geom);

	}

	if (mMeshCode == 1)
	{
		mSceneNode = mApplication.getAssetManager().loadModel(getMeshString(mMeshCode));
		//scale
		mSceneNode.scale(mScale,mScale,mScale);
	}

	mApplication.getRootNode().attachChild(mSceneNode);


	//move
	setPosition((float)mPosition.x,(float)mPosition.y,(float)mPosition.z);
	System.out.println("y:" + (float)mPosition.y);

	if (mIsGhost)
	{
		//mSceneNode.setCullHint(CullHint.Always);
	}


	//billboard
	if (mIsGhost)
	{
		mBitmapFont = null;
		mBitmapText = null;
	}
	else
	{
		mBitmapFont = mApplication.getAssetManager().loadFont("Interface/Fonts/Default.fnt");
		mBitmapText = new BitmapText(mBitmapFont, false);
		mBitmapText.setSize(mBitmapFont.getCharSet().getRenderedSize());
		mBitmapText.setText("Hello World");
		mBitmapText.setQueueBucket(Bucket.Inherit);
		mBitmapText.scale(.02f);
		mApplication.getRootNode().attachChild(mBitmapText);
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
public void yaw        (float amount, boolean converToDegree   )
{
	double rads = Math.toRadians(amount);

	getSceneNode().rotate(0f,(float)rads,0f);
}

public void translate  (Vector3D translateVector, int perspective)
{
	if (perspective == 1)
	{
		getSceneNode().move((float)translateVector.x,(float)translateVector.y,(float)translateVector.z);
	}
	if (perspective == 2)
	{
		getSceneNode().move((float)translateVector.x,(float)translateVector.y,(float)translateVector.z);
	}
}
public void setPosition(Vector3D position                        )
{
	getSceneNode().setLocalTranslation((float)position.x,(float)position.y,(float)position.z);

	if (!mIsGhost)
	{
		mBitmapText.setLocalTranslation((float)position.x -1.0f,(float)position.y + 2.0f,(float)position.z);

		//System.out.println("setPostion");
	//	Vector3f setPosition = new Vector3f(0.0f,0.0f,0.0f);
		Vector3f upVector = new Vector3f(0.0f,1.0f,0.0f);
		mBitmapText.lookAt(mApplication.getCameraLocation(),upVector);
	}
}
public void setPosition(float x, float y, float z                )
{
	getSceneNode().setLocalTranslation(x,y,z);
}
public void setVisible (boolean visible                             )
{
	if (visible)
	{

		getSceneNode().setCullHint(CullHint.Never);
	}
	else
	{
		getSceneNode().setCullHint(CullHint.Always);
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
 	Vector3f vector3f = quaternion.getRotationColumn(2);
 	Vector3D orientation = new Vector3D();
 	orientation.x = vector3f.x;
 	orientation.y = vector3f.y;
 	orientation.z = vector3f.z;

 	//Quaternion toSomething = orientation.getRotationTo(something,fallback);
	Quaternion toSomething = getRotationTo(orientation, something);

	double d = getYaw(toSomething);

	double d2 = java.lang.Math.toDegrees(d);

	float f = (float)d2;

	return f;
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
public Spatial  getSceneNode() { return mSceneNode; }

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
		return "jmonkey/models/sinbad/Sinbad.mesh.xml";
	}
	return "cube.mesh";
}


Quaternion getRotationTo(Vector3D source, Vector3D dest)
{
	Quaternion quaternion = new Quaternion();

	Vector3D fallbackAxis = new Vector3D(0.0f,1.0f,0.0f);

	Vector3D v0 = new Vector3D();
	Vector3D v1 = new Vector3D();
	v0.copyValuesFrom(source);
	v1.copyValuesFrom(dest);

	v0.normalise();
	v1.normalise();

	//Real d = v0.dotProduct(v1);
	float d = v0.dot(v1);

    // If dot == 1, vectors are the same
    if (d >= 1.0f)
    {
		Quaternion quaternionIdentity = new Quaternion(0.0f,0.0f,0.0f,1.0f);
		return quaternionIdentity;
    }

	if (d < (1e-6f - 1.0f))
	{
		// rotate 180 degrees about the fallback axis
		//Vector3 fb;
	//	fb.x = fallbackAxis.x;
	//	fb.y = fallbackAxis.y;
	//	fb.z = fallbackAxis.z;
		//quaternion.FromAngleAxis(Radian(Math::PI), fb);
	}
	else
	{
		float s = (float)java.lang.Math.sqrt( (1+d)*2 );
        float invs = 1 / s;

		Vector3D c = v0.crossProduct(v1);

   	    float x = c.x * invs;
        float y = c.y * invs;
        float z = c.z * invs;
        float w = s * 0.5f;
		quaternion.set(x,y,z,w);
		quaternion.normalize();
	}
return quaternion;
}

double getYaw(Quaternion q)
{

	float x = q.getX();
	float y = q.getY();
	float z = q.getZ();
	float w = q.getW();
		// yaw = atan2(localz.x, localz.z)
			// pick parts of zAxis() implementation that we need
			float fTx  = 2.0f*x;
			float fTy  = 2.0f*y;
			float fTz  = 2.0f*z;
			float fTwy = fTy*w;
			float fTxx = fTx*x;
			float fTxz = fTz*x;
			float fTyy = fTy*y;

			//return Radian(Math::ATan2(fTxz+fTwy, 1.0f-(fTxx+fTyy)));
		double theta = java.lang.Math.atan2(fTxz+fTwy, 1.0f-(fTxx+fTyy));
		return theta;
}

}


