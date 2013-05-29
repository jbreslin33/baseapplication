/*
select min(questions.level_id), questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, questions_attempts.answer_time from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions_attempts.answer_time > 2000 AND questions.answer != questions_attempts.answer GROUP BY questions.id,questions_attempts.answer,questions_attempts.user_id,questions_attempts.answer_time;


select min(questions.level_id), questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, questions_attempts.answer_time from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions_attempts.answer_time > 2000 or questions.answer != questions_attempts.answer GROUP BY questions.id,questions_attempts.answer,questions_attempts.user_id,questions_attempts.answer_time;

select min(questions.level_id), max(questions.id), questions.question, questions_attempts.answer, questions_attempts.user_id, questions_attempts.answer_time from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions_attempts.answer_time > 2000 AND questions.answer != questions_attempts.answer GROUP BY questions.id,questions_attempts.answer,questions_attempts.user_id,questions_attempts.answer_time LIMIT 1 OFFSET 2;


//getting everyting...
 select min(questions.level_id), questions_attempts.answer_attempt_time, questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, questions_attempts.answer_time from questions_attempts inner join questions on questions_attempts.question_id=questions.id GROUP BY questions.id,questions_attempts.answer,questions_attempts.user_id,questions_attempts.answer_time, questions_attempts.answer_attempt_time order by questions.level_id, questions_attempts.answer_attempt_time DESC;

//without min
select questions.level_id, questions_attempts.answer_attempt_time, questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, questions_attempts.answer_time from questions_attempts inner join questions on questions_attempts.question_id=questions.id GROUP BY questions.id,questions_attempts.answer,questions_attempts.user_id,questions_attempts.answer_time, questions_attempts.answer_attempt_time order by questions.level_id, questions_attempts.answer_attempt_time DESC;


SELECT questions.level_id FROM questions_attempts INNER JOIN questions ON questions_attempts.question_id=questions.id WHERE questions_attempts.answer_time > 2000 AND questions.answer != questions_attempts.answer AND 1 = (SELECT COUNT(*) FROM questions);


 ; WITH cte AS ( SELECT *, ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts) SELECT * FROM cte WHERE rn = 1;

; WITH cte AS ( SELECT *, ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts) SELECT * FROM cte WHERE rn = 1;



; WITH cte AS ( SELECT *, ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000;


//using join and partion by
; WITH cte AS ( SELECT *, ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts inner join questions on questions_attempts.question_id=questions.id) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000;




//closer...
 ; WITH cte AS ( SELECT questions.id, questions_attempts.answer_time, questions.answer as "real_answer", questions_attempts.answer as "client_answer", ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts inner join questions on questions_attempts.question_id=questions.id) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000;


//is this it?
 ; WITH cte AS ( SELECT questions.id, questions_attempts.answer_time, questions.answer as "real_answer", questions_attempts.answer as "client_answer", ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts inner join questions on questions_attempts.question_id=questions.id) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000 AND real_answer != client_answer;


//this is with a limit
; WITH cte AS ( SELECT questions.id, questions_attempts.answer_time, questions.answer as "real_answer", questions_attempts.answer as "client_answer", ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts inner join questions on questions_attempts.question_id=questions.id) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000 AND real_answer != client_answer LIMIT 1;




//with limit and user id also it will return nothing if user has answered all correct thus far so then you would simply querey again
getting distinct level_id...
 ; WITH cte AS ( SELECT questions.id, questions_attempts.user_id as "userid", questions_attempts.answer_time, questions.answer as "real_answer", questions_attempts.answer as "client_answer", ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts inner join questions on questions_attempts.question_id=questions.id) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000 AND real_answer != client_answer AND userid = 2 LIMIT 1;

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
				getQuestionLevelID();
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
        mQuestion = "";
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
        int length = mServerPartido->mQuestionVector.at(mQuestionID).length();  // get length of string containing school
        mMessage.WriteByte(length); //send length

        //loop thru length and write it
        for (int b=0; b < length; b++)
        {
                mMessage.WriteByte(mServerPartido->mQuestionVector.at(mQuestionID).at(b));
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
}

void ClientPartido::insertAnswerAttempt()
{
	bool foundFirstUnmasteredID = false;

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
void ClientPartido::getQuestionLevelID()
{
   	LogString("ClientPartido::getQuestionLevelID");	
        bool foundFirstUnmasteredID = false;

        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	std::string query = "; WITH cte AS ( SELECT questions.id, questions_attempts.user_id as userid, questions_attempts.answer_time, questions.answer as real_answer, questions_attempts.answer as client_answer, ROW_NUMBER() OVER (PARTITION BY question_id ORDER BY answer_attempt_time DESC) AS rn FROM questions_attempts inner join questions on questions_attempts.question_id=questions.id) SELECT * FROM cte WHERE rn = 1 AND answer_time > 2000 AND real_answer != client_answer AND userid = ";

	std::string a = utility->intToString(db_id);       
	query.append(a);
	std::string b = " LIMIT 1"; 
	query.append(b);

        const char * q = query.c_str();
	LogString("q:%s",q);
        res = PQexec(conn,q);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
		LogString("No result set, put user at questions.id = 1");
        	mQuestionID = 1;
        }
        rec_count = PQntuples(res);

        //right off the bat we can check if user has even attepted mLimit questions...
        if (rec_count < mLimit)
        {
		LogString("result set is empty, put user at questions.id = 1");
        	mQuestionID = 1;
        }
        else
        {
                const char* question_id_char = PQgetvalue(res, 0, 0);
                mQuestionID = atoi (question_id_char);
		LogString("mQuestionID=%d",mQuestionID);
        }
       	PQclear(res);
        PQfinish(conn);
}

