package breslin.clientside.shape;

/**********************************
*          INCLUDES
**********************************/
//parent
import breslin.clientside.shape.Shape;

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
public class ShapeMonkey extends Shape //, public OgreAnimation
{


public ShapeMonkey(GameMonkey gameMonkey, ByteBuffer byteBuffer, boolean isGhost)
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
		mGhost = new ShapeMonkey(mGameMonkey,byteBuffer,true);
		//mGhost.setVisible(false);

		//put shape and ghost in game vectors so they can be looped and game now knows of them.
		mGame.mShapeVector.add(this);
		mGame.mShapeGhostVector.add(mGhost);
		mGhost.setVisible(true);
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
Spatial          mSceneNode;

//billboard
BitmapFont mBitmapFont;
BitmapText mBitmapText;
//ObjectTitle* mObjectTitle;
//std::string  mObjectTitleString;

//ability

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

		Material mat = new Material(mGameMonkey.mApplication.getAssetManager(),"generic/pictures/ShowNormals.j3md");
		mSceneNode.setMaterial(mat);
		//mGameMonkey.mApplication.getRootNode().attachChild(geom);

	}

	if (mMeshCode == 1)
	{
		mSceneNode = mGameMonkey.mApplication.getAssetManager().loadModel(getMeshString(mMeshCode));
		//scale
		mSceneNode.scale(mScale,mScale,mScale);
	}

	mGameMonkey.mApplication.getRootNode().attachChild(mSceneNode);


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
		mBitmapFont = mGameMonkey.mApplication.getAssetManager().loadFont("Interface/Fonts/Default.fnt");
		mBitmapText = new BitmapText(mBitmapFont, false);
		mBitmapText.setSize(mBitmapFont.getCharSet().getRenderedSize());
		mBitmapText.setText("Hello World");
		mBitmapText.setQueueBucket(Bucket.Inherit);
		mBitmapText.scale(.02f);
		mGameMonkey.mApplication.getRootNode().attachChild(mBitmapText);
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
		mBitmapText.lookAt(mGameMonkey.mApplication.getCameraLocation(),upVector);
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
