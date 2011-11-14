#ifndef SHAPEOGRE_H
#define SHAPEOGRE_H

/**********************************
*          INCLUDES
**********************************/

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/**********************************
*          FORWARD DECLARATIONS
**********************************/

//Application
class ApplicationOgre;

//title
class ObjectTitle;

//bytebuffer
class ByteBuffer;

//Vector
class Vector3D;

//shape
class Shape;

#include <string>

/**********************************
*          CLASS
**********************************/
class ShapeOgre
{

public:
ShapeOgre(Shape* shape);
~ShapeOgre();

/**********************************
*          VARIABLES
**********************************/

//application
ApplicationOgre* mApplicationOgre;

//ghost
bool mIsGhost;

//ogre scene stuff
Entity*             mEntity;

//this is your pointer to move shape, really all you need.
SceneNode*          mSceneNode;

//billboard
ObjectTitle* mObjectTitle;
std::string  mObjectTitleString;

//scale
float mScale;

Shape* mShape;
//ability

/**********************************
*          METHODS
**********************************/
//shape
void createShape();

//debugging
void checkExtents(Vector3D min);

//size
void scale(Vector3D scaleVector);

//movement
float getDegreesToSomething(Vector3D* vectorOfSomething);
void yaw        (float amountToYaw, bool converToDegree   );
void translate  (Vector3D* translateVector, int perspective);
void setPosition(Vector3D* position                        );
void setPosition(float x, float y, float z                );
void setVisible (bool visible                             );
void setRotation(Vector3D* vector3D);

//check position
Vector3D* getPosition          (                                         );

//check rotation
Vector3D* getRotation();
Quaternion* getRotationTo(Vector3D* source, Vector3D* dest);

//title
void drawTitle    ();
void appendToTitle(std::string appendage);
void appendToTitle(int appendage);
void clearTitle   ();
void setupTitle();

//ogre scene node
SceneNode*  getSceneNode() { return mSceneNode; }

//utility
Ogre::Vector3 converToVector3(Vector3D* vector3d);

//mesh
std::string getMeshString(int meshCode);


};

#endif

