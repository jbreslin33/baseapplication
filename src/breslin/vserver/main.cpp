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

int main(int argc, char **argv)
{
	StartLog();

	Server* server = new Server("",30004);
	Game* game = new Game();
	
	server->addGame(game);

	game->mServer = server;

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
