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
	mQuestionID = 0;
	mBattleScore = 0;
	mWins = 0;
	mLosses = 0;
	mTies = 0;	
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
	if (mConnectionState == DREAMSOCK_CONNECTED)
	{
        	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        	mMessage.WriteByte(mServerPartido->mMessageAskQuestion); // add type

        	if (mClientID > 0)
        	{
                	mMessage.WriteByte(mClientID); // add mClientID for browsers
        	}
       		int length = mServerPartido->mQuestionVector.at(questionID).length();  
        	mMessage.WriteByte(length); 

        	//loop thru length and write it
        	for (int i=0; i < length; i++)
        	{
                	mMessage.WriteByte(mServerPartido->mQuestionVector.at(questionID).at(i));
        	}

        	//send it
        	mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
	}
}
void ClientPartido::battleStart(ShapePartido* whoToBattle)
{
	LogString("ClientPartido::battleStart:%s",db_first_name.c_str());
        mShapePartido->mKey = 0;
        mShapePartido->mOpponent = whoToBattle;

	mBattleScore = 0;	
	mWaitingForAnswer = false;
        mQuestionString = "";
	mShapePartido->mCollidable = false;
	if (mConnectionState == DREAMSOCK_CONNECTED)
        {
       		sendBattleStart();
	}
}

void ClientPartido::sendBattleStart()
{
	LogString("ClientPartido::sendBattleStart:%s",db_first_name.c_str());
	if (mConnectionState == DREAMSOCK_CONNECTED)
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
}

void ClientPartido::scoreBattle(int result)
{
	if (result == WIN)
	{
		mWins++;
	}

	if (result == LOSS)
	{
		mLosses++;
	}
}

void ClientPartido::sendBattleRecord()
{
  	//setText
        std::string record;
        record.append(db_first_name);
        record.append(":");
        record.append(utility->intToString(mWins));
        record.append("-");
        record.append(utility->intToString(mLosses));
        mShapePartido->setText(record);
}

void ClientPartido::resetOpponents()
{
	//set your last opponent
        mShapePartido->mOpponentLast = NULL;

        //clear you opponent
        mShapePartido->mOpponent = NULL;
}

void ClientPartido::resetRecords()
{
 	mWins   = 0;
       	mLosses = 0;
        mTies   = 0;
}

void ClientPartido::resetBattle()
{
 	//reset opponent pointers and vars for answers...
        mBattleScore      = 0;
        mWaitingForAnswer = false;
        mQuestionString   = "";

        //relieve your last opponents last opponent if it was you
        if (mShapePartido->mOpponentLast)
        {
                if (mShapePartido->mOpponentLast->mOpponentLast == mShapePartido)
                {
                        mShapePartido->mOpponentLast->mOpponentLast = NULL;
                }
        }

        //set your last opponent
        mShapePartido->mOpponentLast = mShapePartido->mOpponent;

        //clear you opponent
        mShapePartido->mOpponent = NULL;

        mShapePartido->mCollidable = true;
}

void ClientPartido::sendBattleEnd()
{
	LogString("ClientPartido::sendBattleEnd:%s",db_first_name.c_str());
	if (mConnectionState == DREAMSOCK_CONNECTED)
	{
       		mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
       		mMessage.WriteByte(mServerPartido->mMessageBattleEnd); // add type

       		if (mClientID > 0)
       		{
               		mMessage.WriteByte(mClientID); // add mClientID for browsers
       		}

       		//send it
       		mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
	}
}

void ClientPartido::readAnswer(Message* mes)
{
	LogString("ClientPartido::readAnswer:%s",db_first_name.c_str());
        //clear answer string
        mStringAnswer.clear();

        mAnswerTime = mes->ReadShort();

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
	insertAnswerAttempt();

	//after you insert can i do some live battle stuff here????
	//if you get one wrong or not in time then battle over????
	//or first one to 10....for now...

        //if (real_answer.compare(client_answer) != 0)
//mServerPartido->mQuestionVector.at(questionID)
        if (mStringAnswer.compare(mServerPartido->mQuestionVector.at(mQuestionID)) != 0)  
	{
		ShapePartido* opponent  = mShapePartido->mOpponent;

		//score battle
		scoreBattle(LOSS);
		opponent->mClientPartido->scoreBattle(WIN);

		//send battle record to clients
		sendBattleRecord();	
		opponent->mClientPartido->sendBattleRecord();	

		//reset battle
		resetBattle();	
		opponent->mClientPartido->resetBattle();	

		//send battle end to client	
		sendBattleEnd();
		opponent->mClientPartido->sendBattleEnd();
	}
	else
	{
		mBattleScore++;
	}	

	if (mBattleScore > 9)
	{
		ShapePartido* opponent  = mShapePartido->mOpponent;
		
		//score battle
		scoreBattle(WIN);
		opponent->mClientPartido->scoreBattle(LOSS);

   		//send battle record to clients
                sendBattleRecord();
                opponent->mClientPartido->sendBattleRecord();

                //reset battle
                resetBattle();
                opponent->mClientPartido->resetBattle();

                //send battle end to client
                sendBattleEnd();
                opponent->mClientPartido->sendBattleEnd();
	} 	
	
	//set vars for new question and answer combo....
        mWaitingForAnswer = false;
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
        PQexec(conn,q);
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
		return false;
        }
        rec_count = PQntuples(res);


	//quick check...	
	if (rec_count != 10)
	{
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
				PQclear(res);
        			PQfinish(conn);
                        	return false;
                       	} 

                        if (real_answer.compare(client_answer) != 0)
                        {
				PQclear(res);
        			PQfinish(conn);
                               	return false;
                        }
		}
		//if you got here it means you have 10 records and they survived the pass checks so return true
		PQclear(res);
        	PQfinish(conn);
		return true;
	}
}

int ClientPartido::getNewQuestionID()
{
	int maxLevel            = getMaxLevelAskedID();

	if (rand() % 2 == 1)
	{
		//you could advance here if you passed maxLevel and all before it...
		for (int i = 1; i <= maxLevel; i++)
		{
			if (checkLevel(i))
			{
				if (i == maxLevel)
				{
					//advance level
					mQuestionID = maxLevel + 1;
					return mQuestionID;
				}
			}
			else
			{
				mQuestionID = i;
				return mQuestionID;	
			}
		}
	}
	else
	{
		//do it random based on maxLevel, you cannot advance a level here.
		mQuestionID  = rand() % maxLevel + 1;
		return mQuestionID;
	}
}
