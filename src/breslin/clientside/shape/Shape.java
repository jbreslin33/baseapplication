package breslin.clientside.shape;


/**********************************
*          INCLUDES
**********************************/
//math
import breslin.math.Vector3D;

class Shape
{


public Shape(int ind, Vector3D position, Vector3D rotation)
{

}

/**************************************************
*			VARIABLES
**************************************************/
int   mIndex;
//Game* mGame;

//Parser* mParser;

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