#include "clientPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

#include "../server/serverPartido.h"
#include "../network/network.h"
#include "../game/gamePartido.h"
#include "../shape/shapePartido.h"

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
	mFirstUnmasteredQuestionID = 0;
	mQuestionID = 0;
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
                		LogString("ClientPartido::sendQuestion:%d",db_id);	
				sendQuestion();
                		mWaitingForAnswer = true;
        		}
		}
	}
}

void ClientPartido::initializeBattle()
{
	getQuestionLevelID();
	LogString("after");
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
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServerPartido->mMessageAskQuestion); // add type

        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); // add mClientID for browsers
        }
        int length = mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).length();  // get length of string containing school
        mMessage.WriteByte(length); //send length

        //loop thru length and write it
        for (int b=0; b < length; b++)
        {
                mMessage.WriteByte(mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).at(b));
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
	LogString("ClientPartido::sendBattleStart");
}

void ClientPartido::readAnswer(Message* mes)
{
        //clear answer string
        mStringAnswer.clear();

        mAnswerTime = mes->ReadByte();
        LogString("mAnswerTime:%d",mAnswerTime);

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
	//question_id	
	std::string question_id_string;	
	ostringstream convert_question_id_string;
	convert_question_id_string << mQuestionID;
	question_id_string = convert_question_id_string.str();
	query.append(question_id_string);

	//answer
	std::string a = ",'";
	query.append(a);
	query.append(mStringAnswer);	
	std::string b = "',";	
	query.append(b);

	//answer_time
 	std::string answer_time_string;
        ostringstream convert_answer_time_string;
        convert_answer_time_string << mAnswerTime;
        answer_time_string = convert_answer_time_string.str();
        query.append(answer_time_string);
	std::string c = ",";

	//user_id
 	std::string user_id_string;
        ostringstream convert_user_id_string;
        convert_user_id_string << db_id;
        user_id_string = convert_user_id_string.str();
        query.append(user_id_string);


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
        bool foundFirstUnmasteredID = false;

        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	//check all questions... to find the earliest non-mastered and all mastered ones...
        for (int i = 0; i < mServerPartido->mQuestionCount; i++)
        {
                std::string query = "select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, questions_attempts.answer_time  from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=";

                mQuestionID = i;
                ostringstream convertA;
                convertA << mQuestionID;
                std::string a = convertA.str();

                std::string b = " and questions_attempts.user_id =";

                ostringstream convertC;
                convertC << db_id;
                std::string c = convertC.str();

                std::string d = " order by questions_attempts.question_attempt_time_start DESC limit ";
                ostringstream convertE;
                convertE << mLimit;
                std::string e = convertE.str();

                query.append(a);
                query.append(b);
                query.append(c);
                query.append(d);
                query.append(e);

                const char * q = query.c_str();
                res = PQexec(conn,q);
                if (PQresultStatus(res) != PGRES_TUPLES_OK)
                {
                        puts("We did not get any data!");
                }
                rec_count = PQntuples(res);

                //right off the bat we can check if user has even attepted mLimit questions...
                if (rec_count < mLimit)
                {
                        if (!foundFirstUnmasteredID)
                        {
                                mFirstUnmasteredQuestionID = i;
                                foundFirstUnmasteredID = true;
                        }
                        continue;
                }
                else
                {
                }

                for (row=0; row<rec_count; row++)
                {
                        //checking that question is correct..
                        const char* question_char = PQgetvalue(res, row, 1);
                        const char* answer_char = PQgetvalue(res, row, 2);
                        const char* answer_time_char = PQgetvalue(res, row, 4);

                        int question    = atoi (question_char);
                        int answer      = atoi (answer_char);
                        int answer_time = atoi (answer_time_char);

                        if (question == answer)
                        {
                        }
                        else
                        {
                                if (!foundFirstUnmasteredID)
                                {
                                        mFirstUnmasteredQuestionID = i;
                                        foundFirstUnmasteredID = true;
                                }
                                continue;
                        }

                        if (answer_time < 2000)
                        {

                        }
                        else
                        {
                                if (!foundFirstUnmasteredID)
                                {
                                        mFirstUnmasteredQuestionID = i;
                                        foundFirstUnmasteredID = true;
                                }
                                continue;
                        }

                        //made it???? mastered??
                        //add to mastered
                        mMasteredQuestionIDVector.push_back(i);

                }
                PQclear(res);
        }
        PQfinish(conn);
}

