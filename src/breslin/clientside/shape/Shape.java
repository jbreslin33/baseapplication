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
int   mIndex;
Game mGame;

//scale
float mScale;

/**************************************************
*			METHODS
**************************************************/

//setting position
 void     setPosition          (Vector3D vector3D         ) { }
 void     setPosition          (float x, float y, float z ) { }

//getting position
 Vector3D getPosition          (                          ) { return new Vector3D(); }

//size
 void     scale                (Vector3D vector3D         ) { }

//visibility
 void     setVisible           (boolean b                    ) { }


//title
 void     drawTitle            (                          ) { }
 void     appendToTitle        (String appendage     ) { }
 void     appendToTitle        (int appendage             ) { }
 void     clearTitle           (                          ) { }

}