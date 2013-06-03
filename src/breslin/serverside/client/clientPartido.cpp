#include "clientPartido.h"
//log
#include "../tdreamsock/dreamSockLog.h"

#include "../server/serverPartido.h"
#include "../network/network.h"
#include "../game/gamePartido.h"
#include "../shape/shapePartido.h"

//utility
#include "../../utility/utility.h"


ClientPartido::ClientPartido(ServerPartido* serverPartido, struct sockaddr *address, int clientID) : Client(serverPartido, address, clientID) 
{
	//server
	mServerPartido = serverPartido;

	//game
	mGamePartido = NULL;

        if (mClientID >= 0)
        {
                sendSchools();
        }
        else
        {
                //your the node for web sockets
        }
 	
	//battle
        mWaitingForAnswer = false;
        mLimit = 1;
	mQuestionID = 1;
}

ClientPartido::~ClientPartido()
{
}

//game
void ClientPartido::addGame(GamePartido* gamePartido)
{
	Client::addGame(gamePartido);
        mGamePartidoVector.push_back(gamePartido);
}

GamePartido* ClientPartido::getGame()
{
	return mGamePartido;
}

void ClientPartido::setGame(int gameID)
{
        for (int i = 0; i < mGamePartidoVector.size(); i++)
        {
                if (mGamePartidoVector.at(i)->mID == gameID)
                {
                        mGamePartido = mGamePartidoVector.at(i);
                        mGamePartido->sendShapes(this);
                }
        }
}

//updates
void ClientPartido::processUpdate()
{
	Client::processUpdate();
	if (mConnectionState == DREAMSOCK_CONNECTED)
	{
		if (mShapePartido)
		{
 			if (mShapePartido->mOpponent && mWaitingForAnswer == false)
        		{
				sendQuestion(getNewQuestionID());
                		mWaitingForAnswer = true;
        		}
		}
	}
}

void ClientPartido::initializeBattle()
{
	mWaitingForAnswer = false;
        mAnswer = 0;
        mQuestionString = "";
        sendBattleStart();
}

void ClientPartido::setShape(ShapePartido* shapePartido)
{
	Client::setShape(shapePartido);
	mShapePartido = shapePartido;
}

//this gets you question_attempts from a particular questions and particular user_id
//select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=1 and questions_attempts.user_id = 2 order by questions_attempts.question_attempt_time_start;


//you need to send all schools at once and all questions..
void ClientPartido::sendSchools()
{
        //loop thru each char... 
        for (unsigned int i = 0; i < mServerPartido->mSchoolVector.size(); i++)
        {
                mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
                mMessage.WriteByte(mServerPartido->mMessageAddSchool); // add type
                if (mClientID > 0)
                {
                        mMessage.WriteByte(mClientID); // add mClientID for browsers 
                }
                int length = mServerPartido->mSchoolVector.at(i).length();  // get length of string containing school 
                mMessage.WriteByte(length); //send length 

                //loop thru length and write it 
                for (int b=0; b < length; b++)
                {
                        mMessage.WriteByte(mServerPartido->mSchoolVector.at(i).at(b));         
                }
                
                //send it
                mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
        }
}

void ClientPartido::sendQuestion(int questionID)
{
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServerPartido->mMessageAskQuestion); // add type

        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); // add mClientID for browsers
        }
       	//int length = mQuestionString.length(); 
       	int length = mServerPartido->mQuestionVector.at(questionID).length();  
        mMessage.WriteByte(length); 

        //loop thru length and write it
        for (int i=0; i < length; i++)
        {
                mMessage.WriteByte(mServerPartido->mQuestionVector.at(questionID).at(i));
                //mMessage.WriteByte(mQuestionString.at(i));
        }

        //send it
        mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
}

void ClientPartido::sendBattleStart()
{
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServerPartido->mMessageBattleStart); // add type

        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); // add mClientID for browsers
        }

        //send it
        mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
}

void ClientPartido::readAnswer(Message* mes)
{
        //clear answer string
        mStringAnswer.clear();

        mAnswerTime = mes->ReadByte();

        int sizeOfAnswer = mes->ReadByte();
        //loop thru and set mStringAnswer from client
        for (int i = 0; i < sizeOfAnswer; i++)
        {
                if (mClientID > 0)
                {
                        char c = mes->ReadByte();
                        mStringAnswer.append(1,c);
                }
                else
                {
                        int numeric = mes->ReadByte();
                        char ascii = (char)numeric;
                        mStringAnswer.append(1,ascii);
                }
        }
        //mGame->sendAnswer(this,mAnswerTime,mStringAnswer);
	//insert into answer attempts....
	insertAnswerAttempt();

	//set vars for new question and answer combo....
        mWaitingForAnswer = false;
        mAnswer = 0;
        mQuestionString = "";

}

void ClientPartido::insertAnswerAttempt()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
	std::string query = "insert into questions_attempts (question_id,answer,answer_time,user_id) VALUES (";
	query.append(utility->intToString(mQuestionID));

	//answer
	std::string a = ",'";
	query.append(a);
	query.append(mStringAnswer);	
	std::string b = "',";	
	query.append(b);

	//answer_time
        query.append(utility->intToString(mAnswerTime));
	std::string c = ",";
	query.append(c);

	//user_id
        query.append(utility->intToString(db_id));

	std::string d = ")";	
	query.append(d);

    	const char * q = query.c_str();
        PQfinish(conn);
}

int ClientPartido::getMaxLevelAskedID()
{
 	PGconn          *conn;
        PGresult        *res;
        int             rec_count = 0;;
        int             row = 0;
        int             col = 0;
	
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	std::string query = "SELECT question_id FROM questions_attempts WHERE user_id = ";
	query.append(utility->intToString(db_id));       
	query.append(" ORDER BY question_id DESC LIMIT 1");

	const char * q = query.c_str();

        res = PQexec(conn,q);

        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                LogString("SQL ERROR OUTER:%s",q);
        }

        rec_count  = PQntuples(res);
	int num_fields = PQnfields(res);
	
	int i = 0;
	int j = 0;

    	for (i = 0; i < rec_count; i++)
    	{
        	for (j = 0; j < num_fields; j++)
		{
                	const char* question_id_char = PQgetvalue(res, i, j);
        		int ret =  atoi (question_id_char);

			PQclear(res);
        		PQfinish(conn);
			return ret;
		}
	}

        //empty result means new user...
        if (rec_count == 0)
        {
		LogString("this should not be called");
		PQclear(res);
        	PQfinish(conn);
                return 1;
        }
        else
        {
                const char* question_id_char = PQgetvalue(res, 0, 0);
		PQclear(res);
        	PQfinish(conn);
		
        	int ret =  atoi (question_id_char);
		return ret;
	}
	PQclear(res);
        PQfinish(conn);
}

bool ClientPartido::checkLevel(int level)
{
 	PGconn          *conn;
        PGresult        *res;
        int             rec_count = 0;;
        int             row = 0;
        int             col = 0;
	
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	std::string query = "SELECT questions.id, questions.answer AS real_answer, questions_attempts.answer as client_answer, questions_attempts.answer_attempt_time, questions_attempts.answer_time AS time_in_msec, questions_attempts.user_id FROM questions INNER JOIN questions_attempts ON questions.id = questions_attempts.question_id WHERE questions_attempts.user_id = ";

	query.append(utility->intToString(db_id));       

	query.append(" AND questions.id = "); 
	
	query.append(utility->intToString(level));       

	query.append(" ORDER BY questions_attempts.answer_attempt_time DESC LIMIT 10");

	const char * q = query.c_str();
        res = PQexec(conn,q);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                LogString("SQL ERROR OUTER:%s",q);
                mQuestionID = 1;
        }
        rec_count = PQntuples(res);


	//quick check...	
	if (rec_count != 10)
	{
		LogString("should not be here if you then goto 0");
		PQclear(res);
        	PQfinish(conn);
		return false;
	}
	else
	{
                for (row=0; row<rec_count; row++)
                {
                	//real_answer
                        const char* real_answer_char = PQgetvalue(res, row, 1);
                        std::string real_answer(real_answer_char);

                        //client_answer
                        const char* client_answer_char = PQgetvalue(res, row, 2);
                        std::string client_answer(client_answer_char);

                        //time_in_msec
                        const char* time_in_msec_char = PQgetvalue(res, 0, 4);
                        int time_in_msec = atoi (time_in_msec_char);

                        if (time_in_msec > 2000)
                        {
				LogString("should not be here msc");
				PQclear(res);
        			PQfinish(conn);
                        	return false;
                       	} 

                        if (real_answer.compare(client_answer) != 0)
                        {
				LogString("wrong answer level :%d",level);
				PQclear(res);
        			PQfinish(conn);
                               	return false;
                        }
		}
		LogString("passed level:%d",level);
		//if you got here it means you have 10 records and they survived the pass checks so return true
		PQclear(res);
        	PQfinish(conn);
		return true;
	}
}

int ClientPartido::getNewQuestionID()
{
	int maxLevel            = getMaxLevelAskedID();
	LogString("maxLevel:%d",maxLevel);
	return mQuestionID  = utility->getRandomNumber(9,0) + 1;
}
