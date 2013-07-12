//parent
#include "clientStable.h"

#include "../../server/server.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

ClientStable::ClientStable(Server* server, struct sockaddr *address, int clientID, bool permanence) : Client(server,address,clientID,permanence)
{
}

ClientStable::~ClientStable()
{
}

bool ClientStable::handleLetter(Letter* letter)
{
        return mStateMachine->handleLetter(letter);
}

void ClientStable::update()
{
	Client::update();
}


