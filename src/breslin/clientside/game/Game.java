package breslin.clientside.game;

/***************************************
*           INCLUDES
***************************************/
//applicationBreslin
import breslin.clientside.application.ApplicationBreslin;

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


public Game(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

/***************************************
*   		MEMBER VARIABLES
***************************************/
//applicationBreslin
ApplicationBreslin mApplicationBreslin;

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
		mShapeVector.get(i).interpolateTick(mApplicationBreslin.getRenderTime());
	}
}

public void addShape(boolean b, ByteBuffer byteBuffer)
{
	Shape shape = new Shape(mApplicationBreslin,byteBuffer,false);  //you should just need to call this...

	//ability
	shape.addAbility(new AbilityRotation(shape));
	shape.addAbility(new AbilityMove    (shape));

	//put shape and ghost in game vectors so they can be looped and game now knows of them.
	mShapeVector.add(shape);
	mShapeGhostVector.add(shape.mGhost);
}

public void removeShape(ByteBuffer byteBuffer)
{

}

public Shape getShape(int id)
{
	Shape shape = null;

	for (int i = 0; i < mShapeVector.size(); i++)
	{
		System.out.println("index in getshape:" + mShapeVector.get(i).mIndex);
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
