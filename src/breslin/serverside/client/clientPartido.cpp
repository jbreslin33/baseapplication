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
			LogString("ClientPartido::ControlGame:%d",gameID);
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
			//	sendQuestion();
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
        mMessage.WriteByte(mGamePartido->mServerPartido->mMessageAskQuestion); // add type

        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); // add mClientID for browsers
        }
        int length = mGamePartido->mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).length();  // get length of string containing school
        mMessage.WriteByte(length); //send length

        //loop thru length and write it
        for (int b=0; b < length; b++)
        {
                mMessage.WriteByte(mGamePartido->mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).at(b));
        }

        //send it
        mGamePartido->mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
}

void ClientPartido::sendBattleStart()
{
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mGamePartido->mServerPartido->mMessageBattleStart); // add type

        if (mClientID > 0)
        {
                mMessage.WriteByte(mClientID); // add mClientID for browsers
        }

        //send it
        mGamePartido->mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
	LogString("ClientPartido::sendBattleStart");
}

void ClientPartido::readAnswer(Message* mes)
{
        LogString("ClientPartido::parseAnswer");

        //clear answer string
        mStringAnswer.clear();

        mAnswerTime = mes->ReadByte();
        LogString("mAnswerTime:%d",mAnswerTime);

        int sizeOfAnswer = mes->ReadByte();
        LogString("sizeOfAnswer:%d",sizeOfAnswer);

        //loop thru and set mStringAnswer from client
        for (int i = 0; i < sizeOfAnswer; i++)
        {
                LogString("hel");
                if (mClientID > 0)
                {
                        LogString("here 1");
                        char c = mes->ReadByte();
                        mStringAnswer.append(1,c);
                }
                else
                {
                        LogString("here");
                        int numeric = mes->ReadByte();
                        LogString("here 2");
                        char ascii = (char)numeric;
                        LogString("here 3");
                        mStringAnswer.append(1,ascii);
                        LogString("here 4");
                }
        }
        LogString("ClientPartido::about to sendAnswer");
        //mGame->sendAnswer(this,mAnswerTime,mStringAnswer);
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
	LogString("getQuestionLevelID");

//check all questions... to find the earliest non-mastered and all mastered ones...
        for (int i = 1; i < mGamePartido->mServerPartido->mQuestionCount; i++)
        {
		LogString("getQuestionLevelID in loop");
                std::string query = "select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, extract(epoch from questions_attempts.question_attempt_time_end - questions_attempts.question_attempt_time_start) * 1000 as seconds_per_problem  from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=";

                int question_id = i;
                ostringstream convertA;
                convertA << question_id;
                std::string a = convertA.str();

                std::string b = " and questions_attempts.user_id =";

                ostringstream convertC;
                convertC << mUserID;
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
                        const char* seconds_per_problem_char = PQgetvalue(res, row, 4);

                        int question = atoi (question_char);
                        int answer   = atoi (answer_char);
                        int seconds_per_problem = atoi (seconds_per_problem_char);

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

                        if (seconds_per_problem < 2000)
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

