#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//possible games
#include "../serverside/game/game.h"

#include "../serverside/server/server.h"
#include "../serverside/server/serverPartido.h"
#include "../serverside/network/network.h"
#include "../serverside/tdreamsock/dreamSockLog.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

int main(int argc, char **argv)
{
	StartLog();
	Ogre::Root* root;

#ifdef _DEBUG
        root = new Ogre::Root("plugins_d.cfg");
#else
        root = new Ogre::Root("plugins.cfg");
#endif

	Server* server;

	const char* aServer = "1";	
	const char* aServerPartido = "2";	

	stringstream strValue;
	strValue << argv[2];

	unsigned int intValue;
	strValue >> intValue;

	if (strcmp (argv[1],aServer) == 0)
	{
		server = new Server(root,"",intValue);	
	}

	if (strcmp (argv[1],aServerPartido) == 0)
	{
		server = new ServerPartido(root,"",intValue);	
	}

	server->createGames();
	server->createClients();

	// Ignore the SIGPIPE signal, so the program does not terminate if the pipe gets broken
	signal(SIGPIPE, SIG_IGN);

	int time, oldTime, newTime;

	oldTime = server->mNetwork->getCurrentSystemTime();

	// App main loop
	try
	{
		// Keep server alive (wait for keypress to kill it)
		while(true)
		{
			do
			{
				newTime = server->mNetwork->getCurrentSystemTime();
				time = newTime - oldTime;
			} while (time < 1);
			server->processUpdate(time);

			oldTime = newTime;
		}
	}
	catch(...)
	{
		server->mNetwork->shutdown();
		LogString("Unknown Exception caught in main loop");
		return -1;
	}
	LogString("Shutting down everything");
	server->mNetwork->shutdown();
	return 0;
}
