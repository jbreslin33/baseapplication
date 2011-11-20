package breslin.clientside.game;

/***************************************
*           INCLUDES
***************************************/
//standard library
import java.io.*;
import java.util.ArrayList;
import java.nio.ByteBuffer;

//shape
import breslin.clientside.shape.Shape;

/***************************************
*           CLASS
***************************************/
public class Game
{


public Game(Application application, byte[] serverIP, int serverPort)
{
	mApplication = application;
}

/***************************************
*   		MEMBER VARIABLES
***************************************/
//Shapes
public ArrayList<ShapeDynamic> mShapeVector = new ArrayList<ShapeDynamic>(); //all shapes in the client world
public ArrayList<ShapeDynamic> mShapeGhostVector = new ArrayList<ShapeDynamic>(); //all shapes in the client world's ghost


/***************************************
*   		METHODS
***************************************/
public void run()
{
	for (int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.get(i).interpolateTick(getRenderTime());
	}
}

public void addShape(boolean b, ByteBuffer byteBuffer)
{
	ShapeDynamic shapeDynamicMonkey = new ShapeDynamicMonkey(this,byteBuffer,false);  //you should just need to call this...

	//ability
	shapeDynamicMonkey.addAbility(new AbilityRotation(shapeDynamicMonkey));
	shapeDynamicMonkey.addAbility(new AbilityMove    (shapeDynamicMonkey));
}

public void removeShape(ByteBuffer byteBuffer)
{

}

ShapeDynamic getShapeDynamic(int id)
{
	ShapeDynamic shape = null;

	for (int i = 0; i < mShapeVector.size(); i++)
	{
		ShapeDynamic curShape = mShapeVector.get(i);
		if (curShape.mIndex == id)
		{
			shape = curShape;
		}
	}

	if(shape == null)
	{
		return null;
	}
	else
	{
		return shape;
	}
}



}
