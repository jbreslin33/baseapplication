//header
#include "applicationOgre.h"

//standard library
#include <string>

//log
#include "../tdreamsock/dreamSockLog.h"

//network
#include "../network/network.h"

//game
#include "gameOgre.h"

//shape
#include "../shape/shapeOgre.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"


/*********************************
*		CONSTRUCTORS
**********************************/
ApplicationOgre::ApplicationOgre(const char* serverIP, int serverPort) : Application(serverIP, serverPort) 

{

}

ApplicationOgre::~ApplicationOgre()
{
}
