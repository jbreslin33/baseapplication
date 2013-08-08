#include "clientPartido.h"
//log
#include "../../../tdreamsock/dreamSockLog.h"

#include "../../../server/partido/serverPartido.h"
#include "../../../network/network.h"
#include "../../../game/partido/gamePartido.h"
#include "../../../shape/partido/shapePartido.h"

//utility
#include "../../../../utility/utility.h"

//states
#include "states/clientPartidoStates.h"

//question
#include "../../../question/question.h"
#include "../../../question/questionAttempts.h"

ClientPartido::ClientPartido(ServerPartido* serverPartido, struct sockaddr *address, int clientID, bool permanence,int i, std::string u, std::string p, std::string f, std::string m1, std::string m2, std::string m3, std::string l,int s) : ClientRobust(serverPartido, address, clientID, permanence,i, u,p,f,m1,m2,m3,l,s) 
{
	//server
	mServerPartido = serverPartido;

	//game
	mGamePartido = NULL;

	//battle
        mWaitingForAnswer = false;
	mQuestionID = 0;
	mBattleScore = 0;
	mWins = 0;
	mLosses = 0;
	mTies = 0;	
	mComputerAskedTime = 0;
	mComputerAnswerTime = 0;

        //states
        mClientPartidoStateMachine =  new StateMachine<ClientPartido>(this);
	if (clientID == -1)
	{
        	mClientPartidoStateMachine->setCurrentState      (NULL);
	}
	else
	{
        	mClientPartidoStateMachine->setCurrentState      (Game_Partido_Mode::Instance());
	}
        mClientPartidoStateMachine->setPreviousState     (NULL);
        mClientPartidoStateMachine->setGlobalState       (GlobalClientPartido::Instance());

        //states
        mBattleStateMachine =  new StateMachine<ClientPartido>(this);
	if (clientID == -1)
	{
        	mBattleStateMachine->setCurrentState      (NULL);
	}
	else
	{
        	mBattleStateMachine->setCurrentState      (BATTLE_OFF::Instance());
	}
        mBattleStateMachine->setPreviousState     (NULL);
        mBattleStateMachine->setGlobalState       (NULL);

	getQuestionAttempts();
}

ClientPartido::~ClientPartido()
{
	delete mClientPartidoStateMachine;
	delete mBattleStateMachine;
}

//game
void ClientPartido::addGame(GamePartido* gamePartido)
{
	ClientRobust::addGame(gamePartido);
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

bool ClientPartido::handleLetter(Letter* letter)
{
	return ClientRobust::handleLetter(letter);
}

//updates
void ClientPartido::update()
{
	ClientRobust::update();
	mClientPartidoStateMachine->update();
	mBattleStateMachine->update();
}

void ClientPartido::setShape(ShapePartido* shapePartido)
{
	ClientRobust::setShape(shapePartido);
	mShapePartido = shapePartido;
}

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
       		int length = mServerPartido->mQuestionVector.at(questionID)->question.length();  
        	mMessage.WriteByte(length); 

        	//loop thru length and write it
        	for (int i=0; i < length; i++)
        	{
                	mMessage.WriteByte(mServerPartido->mQuestionVector.at(questionID)->question.at(i));
        	}

        	//send it
        	mServerPartido->mNetwork->sendPacketTo(this,&mMessage);
	}
}

void ClientPartido::battleStart(ShapePartido* whoToBattle)
{
        mShapePartido->mOpponent = whoToBattle;
        mKey = 0;

	mBattleScore = 0;	
	mWaitingForAnswer = false;
        mQuestionString = "";
	mShapePartido->mCollidable = false;
	if (mConnectionState == DREAMSOCK_CONNECTED)
        {
       		sendBattleStart();
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

void ClientPartido::setBattleRecordText()
{
        mBattleRecordText.clear();
        mBattleRecordText.append(first_name);
        mBattleRecordText.append(":");
        mBattleRecordText.append(utility->intToString(mWins));
        mBattleRecordText.append("-");
        mBattleRecordText.append(utility->intToString(mLosses));
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

void ClientPartido::sendBattleStart()
{
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

void ClientPartido::sendBattleEnd()
{
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

void ClientPartido::parseAnswer(Message* mes)
{
	int answerTime = mes->ReadShort();
        int sizeOfAnswer = mes->ReadByte();

	std::string answer;

        //loop thru and set stringAnswer   
        for (int i = 0; i < sizeOfAnswer; i++)
        {
                if (mClientID > 0)
                {
                        char c = mes->ReadByte();
                        answer.append(1,c);
                }
                else
                {
                        int numeric = mes->ReadByte();
                        char ascii = (char)numeric;
                        answer.append(1,ascii);
                }
	}
	
	readAnswer(answerTime,answer);

}

void ClientPartido::readAnswer(int answerTime, std::string answer)
{
        //clear answer string
        mStringAnswer.clear();

        mAnswerTime = answerTime;
	mStringAnswer = answer;	

	insertAnswerAttempt(false);

        if (mStringAnswer.compare(mServerPartido->mQuestionVector.at(mQuestionID)->answer) != 0 || mAnswerTime > 2000)  
	{
		ShapePartido* opponent  = mShapePartido->mOpponent;
		
		if (opponent)
		{

			//score battle
			scoreBattle(LOSS);
			opponent->mClientPartido->scoreBattle(WIN);
		
			//set battle record text .. mBattleRecordText 
			setBattleRecordText();	
			opponent->mClientPartido->setBattleRecordText();	

			//set Text of shape .. mText
	       		mShapePartido->setText(mBattleRecordText); 	
			opponent->mClientPartido->mShapePartido->setText(opponent->mClientPartido->mBattleRecordText);	
		
			//reset battle
			resetBattle();	
			opponent->mClientPartido->resetBattle();	

			//send battle end to client	
			sendBattleEnd();
			opponent->mClientPartido->sendBattleEnd();
		}
		else //opponent took care of loss....
		{
			// do nothing...

		}
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

                //set battle record text .. mBattleRecordText
                setBattleRecordText();
                opponent->mClientPartido->setBattleRecordText();

                //set Text of shape .. mText
                mShapePartido->setText(mBattleRecordText);
                opponent->mClientPartido->mShapePartido->setText(opponent->mClientPartido->mBattleRecordText);

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


int ClientPartido::getNewQuestionID()
{
	int maxLevel            = getMaxLevelAskedID(false);

	if (rand() % 2 == 1)
	{
		//you could advance here if you passed maxLevel and all before it...
		for (int i = 1; i <= maxLevel; i++)
		{
			if (checkLevel(i,false))
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

int ClientPartido::getMaxLevelAskedID(bool db)
{
	if (db)
	{
 		PGconn          *conn;
        	PGresult        *res;
        	int             rec_count = 0;;
        	int             row = 0;
        	int             col = 0;
	
        	conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

		std::string query = "SELECT question_id FROM questions_attempts WHERE user_id = ";
		query.append(utility->intToString(id));       
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
	else
	{
		int highestQuestionID = 1;

		for (int i = 0; i < mQuestionAttemptsVector.size(); i++)
		{
			if (mQuestionAttemptsVector.at(i)->question_id > highestQuestionID)
			{
				highestQuestionID = mQuestionAttemptsVector.at(i)->question_id;
			} 	
	
		}
		return highestQuestionID;	
	}
}

bool ClientPartido::checkLevel(int level, bool db)
{
	if (db)
	{
 		PGconn          *conn;
        	PGresult        *res;
        	int             rec_count = 0;;
        	int             row = 0;
        	int             col = 0;
	
        	conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

		std::string query = "SELECT questions.id, questions.answer AS real_answer, questions_attempts.answer as client_answer, questions_attempts.answer_attempt_time, questions_attempts.answer_time AS time_in_msec, questions_attempts.user_id FROM questions INNER JOIN questions_attempts ON questions.id = questions_attempts.question_id WHERE questions_attempts.user_id = ";

		query.append(utility->intToString(id));       

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
	else
	{
		int total = 0;
		int index = mQuestionAttemptsVector.size() - 1;
		//clear the vector...
		mQuestionAttemptsVectorTemp.clear();

		while (total < 10 && index > -1)     
		{
			if (mQuestionAttemptsVector.at(index)->question_id == level)	
			{
				mQuestionAttemptsVectorTemp.push_back(mQuestionAttemptsVector.at(index));	
				total++;
			}
			index--;
		}

		if (mQuestionAttemptsVectorTemp.size() < 10)
		{
			LogString("size is small: %d", mQuestionAttemptsVectorTemp.size());
		}
		else
		{
			LogString("size is good: %d", mQuestionAttemptsVectorTemp.size());
		}

		return false;
	}
}

//new stuff
void ClientPartido::getQuestionAttempts()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
//extract(epoch from timestamp with time zone '2011-01-02 03:04:05+06')	
	std::string query = "select id, question_id, answer, extract(epoch from answer_attempt_time), answer_time, user_id from questions_attempts WHERE user_id = ";
	query.append(utility->intToString(id)); 
	query.append(" ORDER BY answer_attempt_time"); 
	const char * q = query.c_str();
	LogString("q:%s",q);
        res = PQexec(conn,q);

        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
        }
        else
        {
        }
        rec_count = PQntuples(res);

        for (row=0; row<rec_count; row++)
        {
		LogString("getting record:%d",row);
                const char* a = PQgetvalue(res, row, 0);
                std::string aString(a);
		int aInt = mUtility->stringToInt(aString);

                const char* b = PQgetvalue(res, row, 1);
                std::string bString(b);
		int bInt = mUtility->stringToInt(bString);

                const char* c = PQgetvalue(res, row, 2);
                std::string cString(c);

                const char* d = PQgetvalue(res, row, 3);
                std::string dString(d);
		double dDouble = atof(dString.c_str());

                const char* e = PQgetvalue(res, row, 4);
                std::string eString(e);
		int eInt = mUtility->stringToInt(eString);

                const char* f = PQgetvalue(res, row, 5);
                std::string fString(f);
		int fInt = mUtility->stringToInt(fString);

                QuestionAttempts* questionAttempts = new QuestionAttempts(aInt,bInt,cString,dDouble,eInt,fInt);
                mQuestionAttemptsVector.push_back(questionAttempts);
        }
        PQclear(res);
        PQfinish(conn);
}

void ClientPartido::insertAnswerAttempt(bool db)
{
	if (db)
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
        	query.append(utility->intToString(id));

		std::string d = ")";	
		query.append(d);

    		const char * q = query.c_str();
        	PQexec(conn,q);
        	PQfinish(conn);
	}
	else
	{
                QuestionAttempts* questionAttempts = new QuestionAttempts(0,mQuestionID,mStringAnswer,mServer->mNetwork->getCurrentSystemTime(),mAnswerTime,id);
		mQuestionAttemptsVector.push_back(questionAttempts);
	}
}
