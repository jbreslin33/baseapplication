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


ClientRobust::ClientRobust(Server* server, struct sockaddr *address, int clientID, bool permanence, int i, std::string u, std::string p, std::string f, std::string m1, std::string m2, std::string m3, std::string l, int s) : Client(server,address,clientID,permanence)
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

	//user table
	id = i;
	username = u;
	password = p;
	first_name = f; 
	middle_name1 = m1; 
	middle_name2 = m2;
	middle_name3 = m3;
	last_name = l; 
 	school_id = s;

	//game
	mInGame = false;
	mGame = NULL;

        //shape
        mShape = NULL;

	//states
        mClientRobustStateMachine =  new StateMachine<ClientRobust>(this);
        mClientRobustStateMachine->setCurrentState      (LOGGED_OUT::Instance());
        mClientRobustStateMachine->setPreviousState     (NULL);
        mClientRobustStateMachine->setGlobalState       (GLOBAL_ROBUST::Instance());

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
	delete letter;

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
	delete letter;
        mLoggedIn = false;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); //client id for browsers
        }
        mServer->mNetwork->sendPacketTo(this,&mMessage);
}

bool ClientRobust::checkLogin(Message* mes)
{
        LogString("ClientRobust::checkLogin");
        readLoginMessage(mes);

        for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                if (mStringUsername.compare(mServer->mClientVector.at(i)->username) == 0 && mStringPassword.compare(mServer->mClientVector.at(i)->password) == 0)
                {
                	login();
                }
        }
}

