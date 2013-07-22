//parent
#include "clientRobust.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//mailman
#include "../../mailman/mailMan.h"

//letter
#include "../../letter/letter.h"

//network
#include "../../network/network.h"

//states
#include "states/clientRobustStates.h"


ClientRobust::ClientRobust(Server* server, struct sockaddr *address, int clientID, bool permanence) : Client(server,address,clientID,permanence)
{

	//temp client
	mClient = NULL;

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

	//game
	mInGame = false;
	mGame = NULL;

        //shape
        mShape = NULL;

	//states
        mClientRobustStateMachine =  new StateMachine<ClientRobust>(this);
        mClientRobustStateMachine->setCurrentState      (Logged_Out::Instance());
        mClientRobustStateMachine->setPreviousState     (NULL);
        mClientRobustStateMachine->setGlobalState       (GlobalClientRobust::Instance());

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
	bool b = Client::handleLetter(letter);
	if (b)
	{
		return b;	
	}
	return mClientRobustStateMachine->handleLetter(letter);
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

void ClientRobust::login()
{

        //send letter
	LogString("ClientRobust::login");
        Message message;
        message.Init(message.outgoingData, sizeof(message.outgoingData));
        message.WriteByte(mServer->mMessageLogin); // add type
        Letter* letter = new Letter(this,&message);
        mServer->mMailMan->deliver(this,letter);

        //set last messageTime
        mLastMessageTime = mServer->mNetwork->getCurrentSystemTime();

        mLoggedIn = true;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedIn); // add type
        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); //client id for browsers
        }
        mServer->mNetwork->sendPacketTo(this,&mMessage);
}

void ClientRobust::logout()
{
        //send letter
        Message message;
        message.Init(message.outgoingData, sizeof(message.outgoingData));
        message.WriteByte(mServer->mMessageLogout); // add type
        Letter* letter = new Letter(this,&message);
        mServer->mMailMan->deliver(this,letter);

        mLoggedIn = false;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); //client id for browsers
        }
        mServer->mNetwork->sendPacketTo(this,&mMessage);
}
/*
 			//send logout letter to clientRobust....
                        mServer->mClientVector.at(i)->logout();
                        mConnectionState = DREAMSOCK_DISCONNECTED;
                        mServer->mClientVector.at(i)->setSocketAddress(&mSocketAddress);
                        mServer->mClientVector.at(i)->mConnectionState = DREAMSOCK_CONNECTED;
                        mServer->mClientVector.at(i)->mClientID = mClientID;
                        //send login letter
                        mServer->mClientVector.at(i)->login();

*/
bool ClientRobust::checkLogin(Message* mes)
{
        LogString("ClientRobust::checkLogin");
        readLoginMessage(mes);

        for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                if (mStringUsername.compare(mServer->mClientVector.at(i)->db_username) == 0 && mStringPassword.compare(mServer->mClientVector.at(i)->db_password) == 0)
                {
 			//send logout letter to clientRobust....
                        mServer->mClientVector.at(i)->logout();
                        mConnectionState = DREAMSOCK_DISCONNECTED;
                        mServer->mClientVector.at(i)->setSocketAddress(&mSocketAddress);
                        mServer->mClientVector.at(i)->mConnectionState = DREAMSOCK_CONNECTED;
                        mServer->mClientVector.at(i)->mClientID = mClientID;
                        //send login letter
                        mServer->mClientVector.at(i)->login();
                	//login();
                }
        }
}

