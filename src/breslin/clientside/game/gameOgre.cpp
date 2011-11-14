//header
#include "gameOgre.h"

//shape
#include "../shape/shapeOgre.h"

//ability
#include "../ability/ability.h"



//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GameOgre::GameOgre(ApplicationOgre* applicationOgre, const char* serverIP, int serverPort) : 
Game((Application*)applicationOgre,serverIP,serverPort)
{
	mApplicationOgre = applicationOgre;
}

GameOgre::~GameOgre()
{

}




