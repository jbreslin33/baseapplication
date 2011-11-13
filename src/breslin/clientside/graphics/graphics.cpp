//header
#include "graphicsOgre.h"

//game
#include "../game/applicationOgre.h"

//network
#include "../network/network.h"

//command
#include "../command/command.h"

//shape
#include "../shape/shapeDynamic.h" //only need this to tes Yaw you can pull it out later.

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

Graphics::Graphics(Application* application)
{

}

Graphics::~Graphics()
{

}

/*********************************
		GUI
**********************************/
void Graphics::initializeGui()
{
	if (mInitializeGui == true)
	{
		return;
	}
	else
	{
		loadJoinScreen();
		mInitializeGui = true;
	}
}



