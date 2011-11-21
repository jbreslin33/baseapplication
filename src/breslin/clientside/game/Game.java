package breslin.clientside.game;

/***************************************
*           INCLUDES
***************************************/
//application
import breslin.clientside.game.Application;

//shape
import breslin.clientside.shape.Shape;

//ability
import breslin.clientside.ability.rotation.AbilityRotation;
import breslin.clientside.ability.move.AbilityMove;

//standard library
import java.io.*;
import java.util.ArrayList;
import java.nio.ByteBuffer;


/***************************************
*           CLASS
***************************************/
public class Game
{


public Game(Application application)
{
	mApplication = application;
}

/***************************************
*   		MEMBER VARIABLES
***************************************/
//application
Application mApplication;

//Shapes
public ArrayList<Shape> mShapeVector = new ArrayList<Shape>(); //all shapes in the client world
public ArrayList<Shape> mShapeGhostVector = new ArrayList<Shape>(); //all shapes in the client world's ghost


/***************************************
*   		METHODS
***************************************/
public void run()
{
	for (int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.get(i).interpolateTick(mApplication.getRenderTime());
	}
}

public void addShape(boolean b, ByteBuffer byteBuffer)
{
	Shape shape = new Shape(this,byteBuffer,false);  //you should just need to call this...

	//ability
	shapeMonkey.addAbility(new AbilityRotation(shapeMonkey));
	shapeMonkey.addAbility(new AbilityMove    (shapeMonkey));
}

public void removeShape(ByteBuffer byteBuffer)
{

}

Shape getShape(int id)
{
	Shape shape = null;

	for (int i = 0; i < mShapeVector.size(); i++)
	{
		Shape curShape = mShapeVector.get(i);
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
