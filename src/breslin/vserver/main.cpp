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
#include "../serverside/network/network.h"
#include "../serverside/tdreamsock/dreamSockLog.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Game* game;
//Server* server;

int main(int argc, char **argv)
{
	game = new Game();

	Server* server = new Server("",30004);
	server->mGame = game;
	game->mServer = server;

	//world
	game->createWorld();

	// Ignore the SIGPIPE signal, so the program does not terminate if the pipe gets broken
	signal(SIGPIPE, SIG_IGN);

	int time, oldTime, newTime;

	oldTime = game->mServer->mNetwork->dreamSock_GetCurrentSystemTime();

	// App main loop
	try
	{
		// Keep server alive (wait for keypress to kill it)
		while(true)
		{
			do
			{
				newTime = game->mServer->mNetwork->dreamSock_GetCurrentSystemTime();
				time = newTime - oldTime;
			} while (time < 1);
			game->frame(time);

			oldTime = newTime;
		}
	}
	catch(...)
	{
		game->mServer->mNetwork->dreamSock_Shutdown();
		LogString("Unknown Exception caught in main loop");
		return -1;
	}
	LogString("Shutting down everything");
	game->mServer->mNetwork->dreamSock_Shutdown();
	return 0;
}
