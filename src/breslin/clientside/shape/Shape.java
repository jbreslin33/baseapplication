package breslin.clientside.shape;


/**********************************
*          INCLUDES
**********************************/
//game
import breslin.clientside.game.Game;

//math
import breslin.math.Vector3D;

public class Shape
{

public Shape()
{
	//scale
	mScale = 0;
}
/**************************************************
*			VARIABLES
**************************************************/
public int   mIndex;
public Game mGame;

//scale
public float mScale;

/**************************************************
*			METHODS
**************************************************/

//setting position
public void     setPosition          (Vector3D vector3D         ) { }
public void     setPosition          (float x, float y, float z ) { }

//getting position
public Vector3D getPosition          (                          ) { return new Vector3D(); }

//size
public void     scale                (Vector3D vector3D         ) { }

//visibility
public void     setVisible           (boolean b                    ) { }


//title
public void     drawTitle            (                          ) { }
public void     appendToTitle        (String appendage     ) { }
public void     appendToTitle        (int appendage             ) { }
public void     clearTitle           (                          ) { }

}