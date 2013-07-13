//parent
#include "clientRobust.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//message
#include "../../message/message.h"

//network
#include "../../network/network.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//rotation
#include "../../rotation/rotation.h"

//move
#include "../../move/move.h"

//math
#include "../../../math/vector3D.h"

//states
#include "../states/clientStates.h"

//mailman
#include "../../mailman/mailMan.h"

#ifdef WIN32
//
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>


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


