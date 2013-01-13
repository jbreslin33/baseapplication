#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/server.h"

//network
#include "../network/network.h"

//client
#include "../client/client.h"

//shape
#include "../shape/shape.h"

//math
#include "../../math/vector3D.h"

//bounds
#include "../bounds/bounds.h"

//postgresql
#include <stdio.h>
//#include <postgresql/libpq-fe.h>


Game::Game()
{
	StartLog();

#ifdef _DEBUG
	mRoot = new Ogre::Root("plugins_d.cfg");
#else
	mRoot = new Ogre::Root("plugins.cfg");
#endif
	mTickLength = 32;	
	mFrameTime  = 0;
	mGameTime   = 0;
	mFrameTimeLast  = 0;

	//sequence
	mOutgoingSequence = 1;

	mBounds = new Bounds();

	mDBConnection = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");	
	
	sqlQuery("delete from shapes");
	sqlQuery("update client set client_id = 1");
	sqlQuery("update client set client_id = 1");
	sqlQuery("insert into shapes (id) values (0)");

}

Game::~Game()
{
        PQfinish(mDBConnection);
	StopLog();
	delete mServer;
}

void Game::createServer()
{
	mServer = new Server(this,"", 30004);
}

void Game::createWorld()
{
  	for(int i = 0; i < 0; i++)
        {
                Vector3D* position = new Vector3D();
                position->x = 1.5f * i;
                position->y = 0.0f;
                position->z = 1.5f * i;

                Shape* shape = new Shape(getOpenIndex(),this,0,position,new Vector3D(),new Vector3D(),
                        mRoot,true,true,.66f,1,true);

	}
}

PGresult* Game::sqlQuery(const char* query)
{
        PGresult        *res;
        res = PQexec(mDBConnection,query);
	return res;
}

//extra stuff...
/*
        int             rec_count;
        int             col_count;
        int             row;
        int             col;
*/
/*
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
	col_count = PQnfields(res);

        printf("We received %d records.\n", rec_count);
        printf("We received %d columns.\n", col_count);
        puts("==========================");
        for (row=0; row<rec_count; row++)
        {
                for (col=0; col<col_count; col++)
                {
                        printf("%s\t", PQgetvalue(res, row, col));
                }
                puts("");
        }
        puts("==========================");
*/

void Game::runSqlQuery(const char* query)
{
  	PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,query);
        
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
        printf("We received %d records.\n", rec_count);
        puts("==========================");
        for (row=0; row<rec_count; row++)
        {
                for (col=0; col<3; col++)
                {
                        printf("%s\t", PQgetvalue(res, row, col));
                }
                puts("");
        }

        puts("==========================");

        PQclear(res);

       	PQfinish(conn);
}
/*


*/
void Game::dbTest()
{
	PGconn          *conn;
 	PGresult        *res;
 	int             rec_count;
 	int             row;
	int             col;
	conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
	res = PQexec(conn,
       "select * from users");
	if (PQresultStatus(res) != PGRES_TUPLES_OK) 
	{
		puts("We did not get any data!");
                //exit(0);
      	}
	rec_count = PQntuples(res);
	printf("We received %d records.\n", rec_count);
        puts("==========================");
        for (row=0; row<rec_count; row++)
	{
        	for (col=0; col<3; col++)
		{
              		printf("%s\t", PQgetvalue(res, row, col));
              	}
        	puts("");
      	}
 
        puts("==========================");
 
        PQclear(res);
 
        PQfinish(conn);
}

void Game::purgeShapeTable()
{
  	PGconn          *conn;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        PQexec(conn, "delete * from shapes");

        puts("=============================");
	puts("delete * from shapes");
        puts("=============================");

        PQfinish(conn);
	
}

void Game::frame(int msec)
{
	mFrameTime += msec;
	mGameTime += msec;
	
	// is this where i should interject for browser clients?
	//if so should i read db or a file to communicate
	//mServer->readDB();
	
	// Read packets from clients, this should just for now add bits to mKey representing any keys that have 
	// been hit we don't care about client time or exact order of keystrokes just how many were recieve in
	//the time it takes to run a 32ms frame on the server....the client get's what it can in and then the
	//server runs it and sends it.
	mServer->readPackets();

	//ok now that the 32ms have elapsed with have our client commands let's process the last tick and
	// then send the update to clients.
	//this is where they want to move
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->processTick();
	
		checkBounds(mShapeVector.at(i));
	}
	
	//this is where they can move..	
	checkCollisions();
	
	// Wait full 32 ms before allowing to send
	if(mFrameTime < mTickLength)
	{
		return;
	}
	
	//send positions and exact frame time the calcs where done on which is mFrameTime 
	sendCommand();
	//updateShapeTable();

	mFrameTimeLast = mFrameTime;
	mFrameTime = 0;

	//check for end of game
	checkEndOfGame();

	//checkForTimeouts
        //mServer->checkForTimeout();
}
/*
game is tag but what should i do here i think this is where we need to extend classes.

*/
void Game::checkCollisions()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
	  
		if (mShapeVector.at(i)->mCollidable == true)
		{
			for (unsigned int j = i+1; j < mShapeVector.size(); j++) 
			{
				if (mShapeVector.at(j)->mCollidable == true)
				{
					float x1 = mShapeVector.at(i)->mSceneNode->getPosition().x;
					float z1 = mShapeVector.at(i)->mSceneNode->getPosition().z;
					float x2 = mShapeVector.at(j)->mSceneNode->getPosition().x;
					float z2 = mShapeVector.at(j)->mSceneNode->getPosition().z;

					float distSq = pow((x1-x2),2) + pow((z1-z2),2);
					
					//i am simply adding the 2 collisionradius's of the 2 objects in question then comparing
					//to distSQ between them. IS this right or is it working by chance?
					if(distSq < mShapeVector.at(i)->mCollisionRadius + mShapeVector.at(j)->mCollisionRadius)
					{
						collision(mShapeVector.at(i),mShapeVector.at(j));
					}
				}
			}
		}
	}
}
void Game::checkBounds(Shape* shape)
{

}
void Game::collision(Shape* shape1, Shape* shape2)
{
	float x3 = shape1->mPositionBeforeCollision->x;
	float z3 = shape1->mPositionBeforeCollision->z;
	float x4 = shape2->mPositionBeforeCollision->x;
	float z4 = shape2->mPositionBeforeCollision->z;

	shape1->mSceneNode->setPosition(x3,0.0,z3);
	shape2->mSceneNode->setPosition(x4,0.0,z4);
}

bool Game::checkScope(Client* client, Shape* shape)
{
	//let's check scop here...
	float x1 = client->mShape->mSceneNode->getPosition().x;  //clientshape
	float z1 = client->mShape->mSceneNode->getPosition().z;
	float x2 = shape->mSceneNode->getPosition().x;  //build shape
	float z2 = shape->mSceneNode->getPosition().z;

	float distSq = pow((x1-x2),2) + pow((z1-z2),2);
			
	if(distSq < 10000000.0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
/*
sqlQuery("UPDATE shapes SET position_x = CASE id WHEN 1 THEN 10 WHEN 2 THEN 20 END, position_z = CASE id WHEN 1 THEN 30 WHEN 2 THEN 40 END");
 std::string one = "update shapes set position_x=";

        stringstream ss_pX;
        ss_pX << mSceneNode->getPosition().x;
        std::string two = ss_pX.str();

        std::string three = ", position_y=";

        stringstream ss_pZ;
        ss_pZ << mSceneNode->getPosition().z;
        std::string four = ss_pZ.str();

        std::string five = ", frame_time=";
        stringstream ss_ft;
        ss_ft << mGame->mFrameTime;
        std::string six = ss_ft.str();

        std::string seven = " where id=";

        stringstream ss;
        ss << mIndex;
        std::string eight = ss.str();

        std::string str;
        str.append(one);
        str.append(two);
        str.append(three);
        str.append(four);
        str.append(five);
        str.append(six);
        str.append(seven);
        str.append(eight);

        const char * c = str.c_str();
        mGame->sqlQuery(c);
*/
void Game::updateShapeTable()
{
	std::string query     = "UPDATE shapes SET position_x = CASE id";
	for (int i = 0; i < mShapeVector.size() + 1; i++)
	{
		if (i == 0)
		{
			std::string w = " WHEN ";	
			std::string id  = toString(i);
			std::string t   = " THEN ";
			std::string x    = toString(mFrameTime);
			query.append(w);
			query.append(id);
			query.append(t);
			query.append(x);
		}
		else
		{
			std::string w = " WHEN ";	
			std::string id  = toString(mShapeVector.at(i-1)->mIndex);
			std::string t   = " THEN ";
			std::string x    = toString(mShapeVector.at(i-1)->mSceneNode->getPosition().x);
			query.append(w);
			query.append(id);
			query.append(t);
			query.append(x);
		}
		
	}
	std::string e1 = " END, position_z = CASE id";
	query.append(e1);
	for (int i = 0; i < mShapeVector.size() + 1; i++)
	{
		if (i == 0)
		{
			std::string w = " WHEN ";	
			std::string id  = toString(i);
			std::string t   = " THEN ";
			std::string z    = toString(mGameTime);
			query.append(w);
			query.append(id);
			query.append(t);
			query.append(z);

		}
		else
		{
			std::string w = " WHEN ";	
			std::string id  = toString(mShapeVector.at(i-1)->mIndex);
			std::string t   = " THEN ";
			std::string z    = toString(mShapeVector.at(i-1)->mSceneNode->getPosition().z);
			query.append(w);
			query.append(id);
			query.append(t);
			query.append(z);
		}
	}
	std::string e2 = " END";
	query.append(e2);

        const char * c = query.c_str();
	sqlQuery(c);	

}

std::string Game::toString(float f)
{
        stringstream ss;
        ss << f;
        std::string str = ss.str();
	return str;
}

std::string Game::toString(int i)
{
        stringstream ss;
        ss << i;
        std::string str = ss.str();
	return str;
}


//send to updates to all clients about all shapes
void Game::sendCommand(void)
{
	// Fill messages..for all clients
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{

		//standard initialize of mMessage for client in this case
		mServer->mClientVector.at(i)->mMessage.Init(mServer->mClientVector.at(i)->mMessage.outgoingData,
			sizeof(mServer->mClientVector.at(i)->mMessage.outgoingData));

		//start filling said mMessage that belongs to client
		mServer->mClientVector.at(i)->mMessage.WriteByte(mServer->mMessageFrame);			// type
		
		mServer->mClientVector.at(i)->mMessage.WriteShort(mServer->mClientVector.at(i)->mOutgoingSequence);
	
		//frame time	
		mServer->mClientVector.at(i)->mMessage.WriteByte(mFrameTime);

		//this is where you need to actually loop thru the shapes not the clients but put write to client mMessage
		for (unsigned int j = 0; j < mShapeVector.size(); j++)
		{                         //the client to send to's message        //the shape command it's about
			mShapeVector.at(j)->addToMoveMessage(&mServer->mClientVector.at(i)->mMessage);
		}
	}

/*
	//randomly don't send command packets.... 
	short randomNumber = 0;	
	srand ( (short)time(NULL) + mOutgoingSequence);
      	randomNumber = rand() % 16;  

	mOutgoingSequence++;

	if (randomNumber == 2)
	{
		//LogString("skip send command packet");
	}
	else
	{
		mServer->sendPackets();
	}
*/
	mServer->sendPackets();
	
	// Store the sent command in 
	for (unsigned int i = 0; i < mServer->mGame->mShapeVector.size(); i++)
	{
		storeCommands(mServer->mGame->mShapeVector.at(i));
	}
}

void Game::storeCommands(Shape* shape)
{
	shape->mKeyLast = shape->mKey;

	shape->mPositionLast->convertFromVector3(shape->mSceneNode->getPosition());

	shape->mRotationLast->copyValuesFrom(shape->mRotation);
}

//this is the whole shabang server exit not a player or shape exit
void Game::sendExitNotification()
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{

		mServer->mClientVector.at(i)->mMessage.Init(mServer->mClientVector.at(i)->mMessage.outgoingData,
			sizeof(mServer->mClientVector.at(i)->mMessage.outgoingData));

		mServer->mClientVector.at(i)->mMessage.WriteByte(mMessageServerExit);	// type
		mServer->mClientVector.at(i)->mMessage.WriteShort(mServer->mClientVector.at(i)->mOutgoingSequence);
	}

	mServer->sendPackets();
}

//this is just for clients right now, should i make another or hijack this function??
void Game::readDeltaMoveCommand(Message *mes, Client *client)
{
	int flags = 0;

	// Flags
	flags = mes->ReadByte();

	// Key
	if(flags & mCommandKey)
	{
		client->mShape->mKey = mes->ReadByte();
	}
}


unsigned int Game::getOpenIndex()
{
	bool proposedIndexOpen = false;
	for (unsigned int proposedIndex = 1; !proposedIndexOpen; proposedIndex++) //keep going till you get an index
	{
		bool someoneHasThisIndex = false;
		for (unsigned int i = 0; i < mShapeVector.size(); i++)
		{
			if (mShapeVector.at(i)->mIndex == proposedIndex)
			{
				someoneHasThisIndex = true;
			}
		}
		if (someoneHasThisIndex == false)
		{
			return  proposedIndex;
		}
	}
	return 0;
}
