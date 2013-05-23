#include "clientPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

#include "../server/serverPartido.h"
#include "../network/network.h"
#include "../game/gamePartido.h"

ClientPartido::ClientPartido(ServerPartido* server, struct sockaddr *address, int clientID) : Client(server, address, clientID) 
{
	//server
	mServer = server;

        if (mClientID >= 0)
        {
                sendSchools();
        }
        else
        {
                //your the node for web sockets
        }
}

ClientPartido::~ClientPartido()
{
}

//this gets you question_attempts from a particular questions and particular user_id
//select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=1 and questions_attempts.user_id = 2 order by questions_attempts.question_attempt_time_start;


//you need to send all schools at once and all questions..
void ClientPartido::sendSchools()
{
        //loop thru each char... 
        for (unsigned int i = 0; i < mServer->mSchoolVector.size(); i++)
        {
                mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
                mMessage.WriteByte(mServer->mMessageAddSchool); // add type
                if (mClientID > 0)
                {
                        mMessage.WriteByte(mClientID); // add mClientID for browsers 
                }
                int length = mServer->mSchoolVector.at(i).length();  // get length of string containing school 
                mMessage.WriteByte(length); //send length 

                //loop thru length and write it 
                for (int b=0; b < length; b++)
                {
                        mMessage.WriteByte(mServer->mSchoolVector.at(i).at(b));         
                }
                
                //send it
                mServer->mNetwork->sendPacketTo(this,&mMessage);
        }
}
