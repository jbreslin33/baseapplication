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

	insertAnswerAttempt();

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

int ClientPartido::getMaxLevelAskedID()
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

bool ClientPartido::checkLevel(int level)
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
		//LogString("size is small: %d", mQuestionAttemptsVectorTemp.size());
	}
	else
	{
		//LogString("size is good: %d", mQuestionAttemptsVectorTemp.size());
	}

	return false;
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
	//LogString("q:%s",q);
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

void ClientPartido::insertAnswerAttempt()
{
        QuestionAttempts* questionAttempts = new QuestionAttempts(0,mQuestionID,mStringAnswer,mServer->mNetwork->getCurrentSystemTime(),mAnswerTime,id);
	mQuestionAttemptsVector.push_back(questionAttempts);
}
