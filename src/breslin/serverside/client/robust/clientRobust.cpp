//parent
#include "clientRobust.h"

//log
#include "../../tdreamsock/dreamSockLog.h"


ClientRobust::ClientRobust(Server* server, struct sockaddr *address, int clientID, bool permanence) : Client(server,address,clientID,permanence)
{
}

ClientRobust::~ClientRobust()
{
}

void ClientRobust::update()
{
        mStateMachine->update();
}

bool ClientRobust::handleLetter(Letter* letter)
{
	return mStateMachine->handleLetter(letter);
}


