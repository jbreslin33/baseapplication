#include "serverPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

#include "../game/gamePartido.h"
#include "../client/clientPartido.h"

ServerPartido::ServerPartido(Ogre::Root* root, const char *localIP, int serverPort) 
:
 Server(root, localIP, serverPort)
{
	//questionCount
	mQuestionCount = 0;

	//get schools
	getSchools();

	//get questions
        getQuestions();

	//create game partido!
 	mGameVector.push_back(new GamePartido(this,2));
}

ServerPartido::~ServerPartido()
{
}

void ServerPartido::createClientsFromDB()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,
        "select * from users ORDER BY id");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
        }
        rec_count = PQntuples(res);
        printf("We received %d records from user table.\n", rec_count);
        for (row=0; row<rec_count; row++)
        {
                //client
                Client* client = new ClientPartido(this, NULL, -2, true, true);

                //id
                const char* a = PQgetvalue(res, row, 0);
                stringstream a_str;
                a_str << a;
                unsigned int a_int;
                a_str >> a_int;
                client->db_id = a_int;

                //username
                const char* b = PQgetvalue(res, row, 1);
                client->db_username.assign(b);

                //password
                const char* c = PQgetvalue(res, row, 2);
                client->db_password.assign(c);

                //first_name
                const char* d = PQgetvalue(res, row, 3);
                client->db_first_name.assign(d);

                //last_name
                const char* e = PQgetvalue(res, row, 7);
                client->db_last_name.assign(e);

                //school_id
                const char* f = PQgetvalue(res, row, 8);
                stringstream f_str;
                f_str << f;
                unsigned int f_int;
                f_str >> f_int;
                client->db_school_id = f_int;

                LogString("created a client with db id of:%d",client->db_id);
        }
        PQclear(res);
        PQfinish(conn);
}


void ServerPartido::parsePacket(Message *mes, struct sockaddr *address)
{
        ClientPartido* client;
        mes->BeginReading();

        int type = mes->ReadByte();

        /***CONNECT********/
        //this should just create a client then client should do what need be done.
        
	if (type == mMessageConnect || type == mMessageConnectBrowser || type == mMessageConnectNode)
	{
		if (type == mMessageConnect)
        	{
                	ClientPartido* client = new ClientPartido(this, address, 0, false, false);
        	}

        	else if (type == mMessageConnectBrowser)
        	{
                	int clientID = mes->ReadByte();
                	ClientPartido* client = new ClientPartido(this, address, clientID, false, false);
        	}

        	else if (type == mMessageConnectNode)
        	{

                	int clientID = mes->ReadByte();
                	ClientPartido* client = new ClientPartido(this, address, -1, false, false);

			createClientsFromDB();	

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
       "select * from questions ORDER BY id");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
	mQuestionCount = rec_count;
        printf("We received %d records.\n", rec_count);
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
        printf("We received %d records.\n", rec_count);
        for (row=0; row<rec_count; row++)
        {
                const char* c = PQgetvalue(res, row, 1);
                std::string school(c);

                mSchoolVector.push_back(school);
		LogString("adding school..");
        }

        PQclear(res);

        PQfinish(conn);
}

