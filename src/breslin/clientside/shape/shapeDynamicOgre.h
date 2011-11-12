#ifndef SHAPEDYNAMICOGRE_H
#define SHAPEDYNAMICOGRE_H

/**********************************
*          INCLUDES
**********************************/
//parent
#include "shapeDynamic.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/**********************************
*          FORWARD DECLARATIONS
**********************************/

//game
class ApplicationOgre;

//title
class ObjectTitle;

//ability

#include <string>

/**********************************
*          CLASS
**********************************/
class ShapeDynamicOgre : public ShapeDynamic //, public OgreAnimation
{

public:
ShapeDynamicOgre(ApplicationOgre* applicationOgre, ByteBuffer* byteBuffer, bool isGhost);
~ShapeDynamicOgre();

/**********************************
*          VARIABLES
**********************************/

//game
ApplicationOgre* mApplicationOgre;

//ghost
bool mIsGhost;

//ogre scene stuff
std::string         mMeshName;
std::string         mName;
Entity*             mEntity;

//this is your pointer to move shape, really all you need.
SceneNode*          mSceneNode;

//billboard
ObjectTitle* mObjectTitle;
std::string  mObjectTitleString;



//ability

/**********************************
*          METHODS
**********************************/
//shape
void createShape();
std::string getMeshString(int meshCode);

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

//name
std::string getName() { return mName; } 

//ogre scene node
SceneNode*  getSceneNode() { return mSceneNode; }

//utility
Ogre::Vector3 converToVector3(Vector3D* vector3d);



};

#endif

