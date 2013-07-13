//parent
#include "clientRobust.h"

//log
#include "../../tdreamsock/dreamSockLog.h"


ClientRobust::ClientRobust(Server* server, struct sockaddr *address, int clientID, bool permanence) : Client(server,address,clientID,permanence)
{
        //keys
        mKeyUp = 1;
        mKeyDown = 2;
        mKeyLeft = 4;
        mKeyRight = 8;
        mKeyCounterClockwise = 16;
        mKeyClockwise = 32;

        mKey = 0;
        mKeyLast = 0;

        //db
        db_id = 0;
        db_school_id = 0;
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


