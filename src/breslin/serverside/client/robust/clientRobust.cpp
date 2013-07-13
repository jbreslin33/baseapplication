//parent
#include "clientRobust.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../../game/game.h"

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

	mGame = NULL;

        //shape
        mShape = NULL;

	//states
        mClientRobustStateMachine =  new StateMachine<ClientRobust>(this);
        mClientRobustStateMachine->setCurrentState      (NULL);
        mClientRobustStateMachine->setPreviousState     (NULL);
        mClientRobustStateMachine->setGlobalState       (NULL);

}

ClientRobust::~ClientRobust()
{
}

void ClientRobust::update()
{
	Client::update();
        mClientRobustStateMachine->update();
}

bool ClientRobust::handleLetter(Letter* letter)
{
	return mStateMachine->handleLetter(letter);
}


void ClientRobust::addGame(Game* game)
{
        mGameVector.push_back(game);
}

void ClientRobust::setGame(int gameID)
{
        for (int i = 0; i < mGameVector.size(); i++)
        {
                if (mGameVector.at(i)->mID == gameID)
                {
                        mGame = mGameVector.at(i);
                        mGame->sendShapes(this);
                }
        }
}

//shape
void ClientRobust::setShape(Shape* shape)
{
        mShape = shape;
}

