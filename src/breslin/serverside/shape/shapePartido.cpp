#include "shapePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../network/network.h"

//game
#include "../server/serverPartido.h"

//game
#include "../game/gamePartido.h"

//client
#include "../client/clientPartido.h"

//math
#include "../../math/vector3D.h"

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>

ShapePartido::ShapePartido(unsigned int index, GamePartido* gamePartido, ClientPartido* clientPartido, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		Shape(index, gamePartido,clientPartido,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	mGamePartido   = gamePartido;
	mClientPartido = clientPartido;
	mOpponent      = NULL;

        //register with shapePartido vector
        mGamePartido->mShapePartidoVector.push_back(this);

       	//battle 
	mWaitingForAnswer = false;
	mLimit = 1;
}
	
ShapePartido::~ShapePartido()
{
}

void ShapePartido::processTick()
{
	Shape::processTick();
 
	if (mWaitingForAnswer == false)
        {
                sendQuestion();
                LogString("sendQuestion!!!");
                mWaitingForAnswer = true;
        }

}
void ShapePartido::sendQuestion()
{
        if (mClientPartido)
        {
                return;
        }
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mGamePartido->mServerPartido->mMessageAskQuestion); // add type

        if (mClientPartido->mClientID > 0)
        {
                mMessage.WriteByte(mClientPartido->mClientID); // add mClientID for browsers
        }
        int length = mGamePartido->mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).length();  // get length of string containing school
        mMessage.WriteByte(length); //send length

        //loop thru length and write it
        for (int b=0; b < length; b++)
        {
                mMessage.WriteByte(mGamePartido->mServerPartido->mQuestionVector.at(mFirstUnmasteredQuestionID).at(b));
        }

        //send it
        mGamePartido->mServerPartido->mNetwork->sendPacketTo(mClientPartido,&mMessage);
}

void ShapePartido::sendBattleStart()
{
        if (!mClientPartido)
        {
                return;
        }
        LogString("sendBattleStart");
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mGamePartido->mServerPartido->mMessageBattleStart); // add type

        if (mClientPartido->mClientID > 0)
        {
                mMessage.WriteByte(mClientPartido->mClientID); // add mClientID for browsers
        }

        //send it
        mGamePartido->mServerPartido->mNetwork->sendPacketTo(mClientPartido,&mMessage);
}

void ShapePartido::collision(Shape* shape)
{
	Shape::collision(shape);	

	if (mOpponent == NULL)
	{
		mOpponent = shape;
	  	getQuestionLevelID();

        	mWaitingForAnswer = false;
        	mAnswer = 0;
        	mQuestion = "";
		sendBattleStart();	
	}
}
//find lowest level unmastered but also fill up an array of possible questions made up of all mastered ones......
void ShapePartido::getQuestionLevelID()
{
        bool foundFirstUnmasteredID = false;

        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

//check all questions... to find the earliest non-mastered and all mastered ones...
        for (int i = 1; i < mGamePartido->mServerPartido->mQuestionCount; i++)
        {
                std::string query = "select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id, extract(epoch from questions_attempts.question_attempt_time_end - questions_attempts.question_attempt_time_start) * 1000 as seconds_per_problem  from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=";

                int question_id = i;
                ostringstream convertA;
                convertA << question_id;
                std::string a = convertA.str();

                std::string b = " and questions_attempts.user_id =";

                ostringstream convertC;
                convertC << mClientPartido->mUserID;
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

