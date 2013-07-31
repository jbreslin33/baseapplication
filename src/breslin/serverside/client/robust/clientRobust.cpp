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

//shape
#include "../../shape/shape.h"

/*
ClientRobust always exists and always has a shape. 
We will make as many as we can....
it's shape, db_id and address can change though 
*/

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
        mClientRobustStateMachine->setCurrentState      (LOGGED_OUT::Instance());
        mClientRobustStateMachine->setPreviousState     (NULL);
        mClientRobustStateMachine->setGlobalState       (GLOBAL_CLIENT_ROBUST::Instance());
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
        //set last messageTime
        mLastMessageTime = mServer->mNetwork->getCurrentSystemTime();

        mLoggedIn = true;

        mMessage->Init(mMessage->outgoingData, sizeof(mMessage->outgoingData));
        mMessage->WriteByte(mServer->mMessageLoggedIn); // add type
        if (mClientID > 0)
        {
                mMessage->WriteByte(mClientID); //client id for browsers
        }
        mServer->mNetwork->sendPacketTo(this,mMessage);
}

void ClientRobust::logout()
{
        mLoggedIn = false;

        mMessage->Init(mMessage->outgoingData, sizeof(mMessage->outgoingData));
        mMessage->WriteByte(mServer->mMessageLoggedOut); // add type
        if (mClientID > 0)
        {
                mMessage->WriteByte(mClientID); //client id for browsers
        }
        mServer->mNetwork->sendPacketTo(this,mMessage);
}

bool ClientRobust::checkLogin(Message* mes)
{
        readLoginMessage(mes);

        for (unsigned int i = 0; i < mServer->mClientVector->size(); i++)
        {
                if (mStringUsername.compare(mServer->mClientVector->at(i)->db_username) == 0 && mStringPassword.compare(mServer->mClientVector->at(i)->db_password) == 0)
                {
 			//send logout letter to clientRobust....
                        mServer->mClientVector->at(i)->logout();
                        mConnectionState = DREAMSOCK_DISCONNECTED;
                        mServer->mClientVector->at(i)->setSocketAddress(&mSocketAddress);
                        mServer->mClientVector->at(i)->mConnectionState = DREAMSOCK_CONNECTED;
                        mServer->mClientVector->at(i)->mClientID = mClientID;
                        //send login letter
                        mServer->mClientVector->at(i)->login();
               
			return true; 
		}
        }
	getPasswordMatch(mStringUsername,mStringPassword);
}

bool ClientRobust::getPasswordMatch(std::string username,std::string password)
{
	int id = 0;
        std::string firstName = "";
        std::string LastName = "";
	int schoolID = 0;

        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        bool match = false;
        std::string query = "select * from users where username = '";
        std::string a = "' ";
        std::string b = "and password = '";
        std::string c = "'";

        query.append(username);
        query.append(a);
        query.append(b);
        query.append(password);
        query.append(c);

        const char * q = query.c_str();

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

        res = PQexec(conn,q);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                LogString("Incorrect Username and or password");
        }
        rec_count = PQntuples(res);
        if (rec_count > 0)
        {
		//set address
                setSocketAddress(&mSocketAddress);
		
		//set connection State
                mConnectionState = DREAMSOCK_CONNECTED;

    		//id
                const char* a = PQgetvalue(res, 0, 0);
                stringstream a_str;
                a_str << a;
                unsigned int a_int;
                a_str >> a_int;
                db_id = a_int;

		db_username = mStringUsername;
		db_password = mStringPassword;

                //first_name
                const char* d = PQgetvalue(res, row, 3);
                db_first_name.assign(d);

                //last_name
                const char* e = PQgetvalue(res, row, 7);
                db_last_name.assign(e);

                //school_id
                const char* f = PQgetvalue(res, row, 8);
                stringstream f_str;
                f_str << f;
                unsigned int f_int;
                f_str >> f_int;
                db_school_id = f_int;

                //send login letter
                login();
	
		mShape->sendText();	
			
		LogString("swapped a robustClient");
        }
        PQclear(res);
        PQfinish(conn);
        return match;
}

