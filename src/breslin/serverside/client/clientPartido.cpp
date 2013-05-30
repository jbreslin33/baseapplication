/*
//this should return 10 records if so you are on next level, if not then you are on that level....
SELECT * FROM (SELECT questions.id, questions.answer AS real_answer, questions_attempts.answer as client_answer, questions_attempts.answer_attempt_time, questions_attempts.answer_time AS time_in_msec, questions_attempts.user_id FROM questions INNER JOIN questions_attempts ON questions.id = questions_attempts.question_id WHERE questions.id = (SELECT max(question_id) FROM questions_attempts) ORDER BY questions_attempts.answer_attempt_time DESC LIMIT 10) AS A WHERE time_in_msec < 2000 AND real_answer = client_answer;
*/

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
			LogString("ClientPartido::setGame:%d",gameID);
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
				getQuestion();
				sendQuestion();
                		mWaitingForAnswer = true;
        		}
		}
	}
}

void ClientPartido::initializeBattle()
{
	LogString("ClientPartido::initializeBattle");        
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

void ClientPartido::sendQuestion()
{
	LogString("ClientPartido::sendQuestion id:%d",mQuestionID);
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServerPartido->mMessageAskQuestion); // add type

        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); // add mClientID for browsers
        }
        int length = mQuestionString.length();  // get length of string containing school
        mMessage.WriteByte(length); //send length

        //loop thru length and write it
        for (int i=0; i < length; i++)
        {
                mMessage.WriteByte(mQuestionString.at(i));
        }

        //send it
        mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
}

void ClientPartido::sendBattleStart()
{
	LogString("ClientPartido::sendBattleStart");
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
	LogString("q:%s",q);
        res = PQexec(conn,q);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
	}
       	rec_count = PQntuples(res);
}

//find lowest level unmastered but also fill up an array of possible questions made up of all mastered ones......
void ClientPartido::getQuestion()
{
   	LogString("ClientPartido::getQuestion");	
        bool foundFirstUnmasteredID = false;

        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	std::string query = "SELECT questions.id, questions.answer AS real_answer, questions_attempts.answer as client_answer, questions_attempts.answer_attempt_time, questions_attempts.answer_time AS time_in_msec, questions_attempts.user_id FROM questions INNER JOIN questions_attempts ON questions.id = questions_attempts.question_id WHERE questions.id = (SELECT max(question_id) FROM questions_attempts) AND questions_attempts.user_id = ";

	//user_id
	std::string a = utility->intToString(db_id);       
	query.append(a);
	
	std::string b = " ORDER BY questions_attempts.answer_attempt_time DESC LIMIT 10";
	query.append(b);

        const char * q = query.c_str();
	LogString("q:%s",q);
        res = PQexec(conn,q);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
		LogString("SQL ERROR OUTER:%s",q);
        	mQuestionID = 1;
        }
        rec_count = PQntuples(res);

       	//empty result means new user... 
	if (rec_count == 0)
	{
		mQuestionID = 1;	
		mQuestionString = "0";
	
	}

	//same level as result set id just go there
	if (rec_count > 0 && rec_count < 10)
	{
                const char* question_id_char = PQgetvalue(res, 0, 0);
                mQuestionID = atoi (question_id_char);

                mQuestionString = mServerPartido->mQuestionVector.at(mQuestionID - 1);
	}
	//we have a contender to check further.....
	bool wrong = false;
	if (rec_count == 10)
        {
		//let's get id right off bat....
		//id
               	const char* question_id_char = PQgetvalue(res, 0, 0);
               	mQuestionID = atoi (question_id_char);

		for (row=0; row<rec_count && wrong == false; row++)
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
				wrong = true;
			}
	
			if (real_answer.compare(client_answer) != 0)	
			{
				wrong = true;
			}
		}
			
		//ok we are done loop one way or another let's use id to set stuff
		if (wrong)
		{
			mQuestionString = mServerPartido->mQuestionVector.at(mQuestionID - 1);
		}
		else
		{
			mQuestionString = mServerPartido->mQuestionVector.at(mQuestionID);
		}
        }
       	
	PQclear(res);
        PQfinish(conn);
}
/*
id | real_answer | client_answer | answer_attempt_time | time_in_msec | user_id 
mQuestionString = mServerPartido->mQuestionVector.at(mQuestionID - 1);
*/
