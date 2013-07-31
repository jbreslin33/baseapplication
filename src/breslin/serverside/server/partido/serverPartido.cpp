#include "serverPartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

#include "../../game/partido/gamePartido.h"
#include "../../client/robust/partido/clientPartido.h"
#include "../../../math/vector3D.h"
#include "../../shape/shape.h"

ServerPartido::ServerPartido(Ogre::Root* root, const char *localIP, int serverPort) 
:
 Server(root, localIP, serverPort)
{

	mGamePartidoVector = new std::vector<GamePartido*>();

	//questionCount
	mQuestionCount = 0;

	//get schools
	getSchools();

	//get questions
        getQuestions();
}

ServerPartido::~ServerPartido()
{
	for (int i = 0; i < mGamePartidoVector->size(); i++)
        {
                delete mGamePartidoVector->at(i);
        }
        delete mGamePartidoVector;
}

void ServerPartido::processClients()
{
        //update clients
        for (unsigned int i = 0; i < mClientPartidoVector.size(); i++)
        {
                mClientPartidoVector.at(i)->update();
        }
        for (unsigned int i = 0; i < mClientPartidoVectorTemp.size(); i++)
        {
                mClientPartidoVectorTemp.at(i)->update();
        }
}

void ServerPartido::processGames()
{
        //update games
        for (unsigned int i = 0; i < mGamePartidoVector->size(); i++)
        {
                mGamePartidoVector->at(i)->update();
        }
}

void ServerPartido::sendCommands()
{
        //send positions and exact frame time the calcs where done on which is mFrameTime
        for (unsigned int i = 0; i < mGamePartidoVector->size(); i++)
        {
                sendCommand(mGamePartidoVector->at(i));
        }
}

void ServerPartido::addGame(GamePartido* gamePartido)
{
	Server::addGame(gamePartido);
        mGamePartidoVector->push_back(gamePartido);
}
void ServerPartido::createClients()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,"select * from users WHERE username != 'root' ORDER BY id LIMIT 30");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
        }
        rec_count = PQntuples(res);
        //printf("We received %d records from user table.\n", rec_count);
        for (row=0; row<rec_count; row++)
        {
                //client
                ClientPartido* clientPartido = new ClientPartido(this, NULL, -2, true);

                //add Games
                for (unsigned int i = 0; i < mGameVector->size(); i++)
                {
                        clientPartido->addGame(mGamePartidoVector->at(i));
                }

                //id
                const char* a = PQgetvalue(res, row, 0);
                stringstream a_str;
                a_str << a;
                unsigned int a_int;
                a_str >> a_int;
                clientPartido->db_id = a_int;

                //username
                const char* b = PQgetvalue(res, row, 1);
                clientPartido->db_username.assign(b);

                //password
                const char* c = PQgetvalue(res, row, 2);
                clientPartido->db_password.assign(c);

                //first_name
                const char* d = PQgetvalue(res, row, 3);
                clientPartido->db_first_name.assign(d);

                //last_name
                const char* e = PQgetvalue(res, row, 7);
                clientPartido->db_last_name.assign(e);

                //school_id
                const char* f = PQgetvalue(res, row, 8);
                stringstream f_str;
                f_str << f;
                unsigned int f_int;
                f_str >> f_int;
                clientPartido->db_school_id = f_int;
        }
        PQclear(res);
        PQfinish(conn);
}

void ServerPartido::addClient(Client* client, bool permanent)
{
	Server::addClient(client, permanent);
	ClientPartido* clientPartido = (ClientPartido*)client;
        if (permanent)
        {
                mClientPartidoVector.push_back(clientPartido);
        }
        else
        {
                mClientPartidoVectorTemp.push_back(clientPartido);
        }
}

void ServerPartido::parsePacket(Message *mes, struct sockaddr *address)
{
        ClientPartido* client;
        mes->BeginReading();

        int type = mes->ReadByte();

        /***CONNECT********/
        //this should just create a client then client should do what need be done.
        
	if (type == mMessageConnect || type == mMessageConnectBrowser || type == mMessageConnectNode
		|| type == mMessageAnswerQuestion || type == mMessageAnswerQuestionBrowser)
	{
		if (type == mMessageConnect)
        	{
                	Client* client = new Client(this, address, 0, false);

        	}

        	else if (type == mMessageConnectBrowser)
        	{
                	int clientID = mes->ReadByte();
                	Client* client = new Client(this, address, clientID, false);
        	}

        	else if (type == mMessageConnectNode)
        	{
                	int clientID = mes->ReadByte();
                	ClientPartido* client = new ClientPartido(this, address, -1, true);
        	}     	 
       		else if (type == mMessageAnswerQuestion)
                {
      			// Find the correct client by comparing addresses
                	for (unsigned int i = 0; i < mClientPartidoVector.size(); i++)
                	{
                        	if( memcmp(mClientPartidoVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
                        	{
                                	ClientPartido* clientPartido = mClientPartidoVector.at(i);
  					if (DREAMSOCK_DISCONNECTED == clientPartido->mConnectionState)
                        		{
                        			continue;
                        		}
					clientPartido->parseAnswer(mes);
				}
			}
                }
    		else if (type == mMessageAnswerQuestionBrowser)
                {
 			int clientID = mes->ReadByte();
                	for (unsigned int i = 0; i < mClientPartidoVector.size(); i++)
                	{
                                ClientPartido* clientPartido = mClientPartidoVector.at(i);
                        	if (mClientPartidoVector.at(i)->mClientID == clientID)
                        	{
  					if (DREAMSOCK_DISCONNECTED == clientPartido->mConnectionState)
					{
						continue;
					}
					else
					{
                       	         		clientPartido->parseAnswer(mes);
					}
				}	
			}
                }
	}
	else
	{
		Server::parsePacket(mes,address);
	}
}

void ServerPartido::getQuestions()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,
       "select * from questions ORDER BY level_id");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
	else
	{
	}
        rec_count = PQntuples(res);
	mQuestionCount = rec_count;
        //printf("We received %d records.\n", rec_count);
       
	//make first elements x so they coincide with db id's 
        mQuestionIDVector.push_back("x");
        mQuestionVector.push_back("x");
	mAnswerVector.push_back("x");
        mLevelVector.push_back("x");

        for (row=0; row<rec_count; row++)
        {
                const char* a = PQgetvalue(res, row, 0);
                std::string aString(a);
                mQuestionIDVector.push_back(aString);

                const char* b = PQgetvalue(res, row, 1);
                std::string bString(b);
                mQuestionVector.push_back(bString);
		

                const char* c = PQgetvalue(res, row, 2);
                std::string cString(c);
                mAnswerVector.push_back(cString);

                const char* d = PQgetvalue(res, row, 3);
                std::string dString(d);
                mLevelVector.push_back(dString);
        }
        PQclear(res);
        PQfinish(conn);
}

void ServerPartido::getSchools()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,
       "select * from schools");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
        //printf("We received %d records.\n", rec_count);
        for (row=0; row<rec_count; row++)
        {
                const char* c = PQgetvalue(res, row, 1);
                std::string school(c);

                mSchoolVector.push_back(school);
        }

        PQclear(res);

        PQfinish(conn);
}

