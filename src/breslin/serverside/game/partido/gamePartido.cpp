#include "gamePartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//server
#include "../../server/partido/serverPartido.h"

//shape
#include "../../shape/partido/shapePartido.h"

//client
#include "../../client/robust/partido/clientPartido.h"

//vector3d
#include "../../../math/vector3D.h"

//battle
#include "../../battle/battle.h"
#include "../../battle/states/battleStates.h"

//combatant
#include "../../combatant/combatant.h"

//test
#include "../../test/test.h"

//questionAttempts
#include "../../question/questionAttempts.h"

//utility
#include "../../../utility/utility.h"

#include <stdio.h>

GamePartido::GamePartido(ServerPartido* serverPartido, int id) : Game(serverPartido,id)
{
	mServerPartido = serverPartido;
	mUtility = new Utility();
	
	mDataDumpThreshold = 10000;
	mDataDumpCounter   = 0;
}

GamePartido::~GamePartido()
{
}

//you should call this from server update
void GamePartido::update()
{
	Game::update();

	//let's reset for a turn	
/*
	if (checkForEndOfGame())
	{
		reset();		
	}
*/
	mDataDumpCounter++;
	LogString("mDataDumpCounter:%d",mDataDumpCounter);
	if (mDataDumpCounter > mDataDumpThreshold)
	{
		dataDump();
	}
        
	for (unsigned int i = 0; i < mBattleVector.size(); i++)
	{
		mBattleVector.at(i)->update();
	}
}

void GamePartido::sendShapes(ClientPartido* clientPartido)
{
	Game::sendShapes(clientPartido);
}

void GamePartido::dataDump()
{
	//make a multi-insert to questions_attempts 
	massiveQuestionsAttemptsInsert();

	//battles  inserts....
	massiveBattleInsert();
}

void GamePartido::reset()
{
	LogString("GamePartido::reset");

	//let's end battles gracefully
        for (unsigned int i = 0; i < mBattleVector.size(); i++)
	{
		mBattleVector.at(i)->mStateMachine->changeState(OVER_BATTLE::Instance());
	}
	
	//maybe send all clients a message to freeze for db?????
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
		mServerPartido->mClientPartidoVector.at(i)->sendSimpleMessage(mServerPartido->mMessageGameEnd);
	}
	
	//make a multi-insert to questions_attempts 
	massiveQuestionsAttemptsInsert();

	//battles  inserts....
	massiveBattleInsert();

	//reset clients
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
		mServerPartido->mClientPartidoVector.at(i)->reset();
	}

	//start game
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
		mServerPartido->mClientPartidoVector.at(i)->sendSimpleMessage(mServerPartido->mMessageGameStart);
	}

	mServerPartido->mGameTime = 0;	

}


void GamePartido::massiveQuestionsAttemptsInsert()
{
	mMassiveInsert.clear();
	PGconn* conn;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	QuestionAttempts* questionAttempt = NULL;	
	ClientPartido* clientPartido = NULL;
	Test* test = NULL;

        mMassiveInsert = "insert into questions_attempts (question_id, answer, answer_time, user_id) values ";

        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
 		if (mServerPartido->mClientPartidoVector.at(i)->mClientID == -1) //browser bridge
                {
                        continue;
                }

		test = mServerPartido->mClientPartidoVector.at(i)->mTest;

		if (test)
		{	
 			for (int z = 0; z < test->mQuestionAttemptsVector.size(); z++)
        		{
                		questionAttempt = test->mQuestionAttemptsVector.at(z);

				if (!questionAttempt->mWrittenToDisk)
				{
					mMassiveInsert.append("(");
                			mMassiveInsert.append(mUtility->intToString(questionAttempt->question_id));
                			mMassiveInsert.append(",'");
                			mMassiveInsert.append(questionAttempt->answer);
                			mMassiveInsert.append("',");
                			mMassiveInsert.append(mUtility->intToString(questionAttempt->answer_time));
                			mMassiveInsert.append(",");
                			mMassiveInsert.append(mUtility->intToString(questionAttempt->user_id));
                			mMassiveInsert.append(")");
                			mMassiveInsert.append(", ");
					LogString("writing");
					questionAttempt->mWrittenToDisk = true;
				}
				else	
				{
				}
			}
       		}
	}
	mMassiveInsert.resize(mMassiveInsert.size() - 2); //to get rid of last comma
        const char * q = mMassiveInsert.c_str();
       	LogString("questionAttempt:%s",q); 
	PQexec(conn,q);
        PQfinish(conn);
}

void GamePartido::massiveBattleInsert()
{
	LogString("GamePartido::massiveBattleInsert");
	mMassiveInsert.clear();
	PGconn* conn;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

	Battle* battle = NULL;

        mMassiveInsert = "insert into battles (battle_start_time,battle_end_time,home_score,away_score,home_user_id,away_user_id) values ";

        for (unsigned int i = 0; i < mBattleVector.size(); i++)
	{
		battle = mBattleVector.at(i);

		//mBattleVector.at(i)->mStateMachine->changeState(OVER_BATTLE::Instance());
		if (!battle->mWrittenToDisk && mBattleVector.at(i)->mStateMachine->currentState() == OVER_BATTLE::Instance())
		{
			mMassiveInsert.append("(to_timestamp(");
                	mMassiveInsert.append(mUtility->intToString(battle->mBattleStartTime));
                	mMassiveInsert.append("),to_timestamp(");
                	mMassiveInsert.append(mUtility->intToString(battle->mBattleEndTime));
                	mMassiveInsert.append("),");
                	mMassiveInsert.append(mUtility->intToString(battle->mHomeCombatant->mScore));
                	mMassiveInsert.append(",");
                	mMassiveInsert.append(mUtility->intToString(battle->mAwayCombatant->mScore));
                	mMassiveInsert.append(",");
                	mMassiveInsert.append(mUtility->intToString(battle->mHomeCombatant->mClientPartido->id));
                	mMassiveInsert.append(",");
                	mMassiveInsert.append(mUtility->intToString(battle->mAwayCombatant->mClientPartido->id));
                	mMassiveInsert.append(")");
                	mMassiveInsert.append(", ");
			battle->mWrittenToDisk = true;
		}
	}
	mMassiveInsert.resize(mMassiveInsert.size() - 2); //to get rid of last comma
        const char * q = mMassiveInsert.c_str();
	LogString("q:%s",q);
        PQexec(conn,q);
        PQfinish(conn);
}

bool GamePartido::checkForEndOfGame()
{
	if (mServerPartido->mGameTime > 99000)
	{
		return true;
	}
	else
	{
		return false;
	}
/*
	//check for end of game
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
		if (mServerPartido->mClientPartidoVector.at(i)->mClientID == -1) //browser bridge
		{
			continue;
		}

		if (mServerPartido->mClientPartidoVector.at(i)->mLosses == 0)	
		{
			return false;
		}
		else
		{
		}
	}
	
	return true;
*/
	//return false;
}

void GamePartido::createShapes()
{
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
        {
                mServerPartido->mClientPartidoVector.at(i)->setShape( new ShapePartido(getOpenIndex(),this,mServerPartido->mClientPartidoVector.at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServerPartido->mRoot,false,true,30.0f,2,true) );

        }
}

void GamePartido::checkCollisions()
{
        for (unsigned int i = 0; i < mShapePartidoVector.size(); i++)
        {
                if (mShapePartidoVector.at(i)->mCollidable == true)
                {
                        for (unsigned int j = i+1; j < mShapePartidoVector.size(); j++)
                        {
                                if (mShapePartidoVector.at(j)->mCollidable == true && mShapePartidoVector.at(j) != mShapePartidoVector.at(i)->mTimeoutShape)
                                {
                                        float x1 = mShapePartidoVector.at(i)->mSceneNode->getPosition().x;
                                        float z1 = mShapePartidoVector.at(i)->mSceneNode->getPosition().z;
                                        float x2 = mShapePartidoVector.at(j)->mSceneNode->getPosition().x;
                                        float z2 = mShapePartidoVector.at(j)->mSceneNode->getPosition().z;

                                        float distSq = pow((x1-x2),2) + pow((z1-z2),2);

                                        //i am simply adding the 2 collisionradius's of the 2 objects in question then comparing
                                        //to distSQ between them. IS this right or is it working by chance?
                                        if(distSq < mShapePartidoVector.at(i)->mCollisionRadius + mShapePartidoVector.at(j)->mCollisionRadius)
                                        {
						Battle* battle = new Battle(this,mShapePartidoVector.at(i)->mClientPartido,mShapePartidoVector.at(j)->mClientPartido);
						//call collision on shape...				
						mShapePartidoVector.at(i)->collision(mShapePartidoVector.at(j));
						mShapePartidoVector.at(j)->collision(mShapePartidoVector.at(i));
	
						mBattleVector.push_back(battle);
                                        }
                                }
                        }
                }
        }
}

