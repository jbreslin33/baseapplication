#include "battler.h"

//battle
#include "../battle/battle.h"

//gamePartido
#include "../game/gamePartido.h"

//serverPartido
#include "../server/serverPartido.h"

//clientPartido
#include "../client/clientPartido.h"


//log
#include "../tdreamsock/dreamSockLog.h"

//network
#include "../network/network.h"

//shape
#include "../shape/shapePartido.h"

//client
#include "../client/client.h"

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>

Battler::Battler(Battle* battle, ShapePartido* shapePartido)
{
	mBattle = battle;
	mShapePartido = shapePartido;

	//let's tell client about this if we have one...
	if (shapePartido->mClientPartido)
	{
		shapePartido->mClientPartido->setBattler(this);
	}

	getQuestionLevelID();
	LogString("first unmastered question id:%d",mFirstUnmasteredQuestionID);

	mWaitingForAnswer = false;
	//should we make a state machine?
	mAnswer = 0; 
	mQuestion = "";
		
	sendBattleStart(); 
}  

Battler::~Battler()
{
}

void Battler::processUpdate()
{
	//this is where you should send questions....
	//select * from questions_attempts limit 10;

	if (mWaitingForAnswer == false)
	{
		sendQuestion();
		LogString("sendQuestion!!!");
		mWaitingForAnswer = true;
	}

}

//this should also send first question to get you started
void Battler::sendBattleStart()
{
        if (!mShapePartido->mClientPartido)
        {
                return;
        }
	LogString("sendBattleStart");
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mBattle->mGamePartido->mServerPartido->mMessageBattleStart); // add type

        if (mShapePartido->mClientPartido->mClientID > 0)
        {
                mMessage.WriteByte(mShapePartido->mClientPartido->mClientID); // add mClientID for browsers
        }

        //send it
        mBattle->mGamePartido->mServerPartido->mNetwork->sendPacketTo(mShapePartido->mClientPartido,&mMessage);
}

void Battler::sendBattleEnd()
{

}
/*
 just send question...
*/
void Battler::sendQuestion()
{
	if (!mShapePartido->mClientPartido)
	{
		return;
	}	
	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mBattle->mGamePartido->mServerPartido->mMessageAskQuestion); // add type

        if (mShapePartido->mClientPartido->mClientID > 0)
        {
                mMessage.WriteByte(mShapePartido->mClientPartido->mClientID); // add mClientID for browsers
        }
        int length = mBattle->mGamePartido->mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).length();  // get length of string containing school
        mMessage.WriteByte(length); //send length
                
	//loop thru length and write it
       	for (int b=0; b < length; b++)
        {
                mMessage.WriteByte(mBattle->mGamePartido->mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).at(b));
        }

        //send it
        mBattle->mGamePartido->mServerPartido->mNetwork->sendPacketTo(mShapePartido->mClientPartido,&mMessage);
}

///mMasteredQuestionIDVector
//find lowest level unmastered but also fill up an array of possible questions made up of all mastered ones......
void Battler::getQuestionLevelID()
{
	bool foundFirstUnmasteredID = false;

        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

//check all questions... to find the earliest non-mastered and all mastered ones...
        for (int i = 1; i < mBattle->mGamePartido->mServerPartido->mQuestionCount; i++)
        {
                std::string query = "select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, extract(epoch from questions_attempts.question_attempt_time_end - questions_attempts.question_attempt_time_start) * 1000 as seconds_per_problem  from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=";

                int question_id = i;
                ostringstream convertA;
                convertA << question_id;
                std::string a = convertA.str();

                std::string b = " and questions_attempts.user_id =";

                ostringstream convertC;
                convertC << mShapePartido->mClientPartido->mUserID;
                std::string c = convertC.str();

                std::string d = " order by questions_attempts.question_attempt_time_start DESC limit ";
                ostringstream convertE;
                convertE << mBattle->mLimit;
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
                if (rec_count < mBattle->mLimit)
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

