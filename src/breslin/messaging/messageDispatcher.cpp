#include "messageDispatcher.h"
#include "../baseentity/baseEntity.h"
#include "../serverside/server/server.h"

//log
#include "../serverside/tdreamsock/dreamSockLog.h"

//message
#include "../serverside/message/message.h"

using std::set;

MessageDispatcher::MessageDispatcher(Server* server)
{
        mServer = server;
}

MessageDispatcher::~MessageDispatcher()
{
}

void MessageDispatcher::discharge(BaseEntity* receiver, const Telegram& telegram)
{
	if (!receiver->handleMessage(telegram))
  	{
		LogString("telegram could not be handled");
  	}
}

void MessageDispatcher::dispatchMessage(double       delay,
                                    int          sender,
                                    int          receiverID,
                                    int          msg,
                                    void*        AdditionalInfo = NULL, Message* message = NULL)

{

	//get a pointer to the receiver
  	BaseEntity* receiver = mServer->getBaseEntityFromID(receiverID);

  	//make sure the receiver is valid
  	if (receiver == NULL)
  	{
		LogString("WARNING: Receiver not found with id:%d",receiver);
    		return;
  	}
  
  	//create the telegram
  	Telegram telegram(0, sender, receiverID, msg, AdditionalInfo, message);
  
  	//if there is no delay, route telegram immediately                       
  	if (delay <= 0.0)                                                        
  	{
    		//send the telegram to the recipient
    		discharge(receiver, telegram);
  	}

  	//else calculate the time when the telegram should be dispatched
  	else
  	{
    		double currentTime = mServer->mGameTime; 

    		telegram.mDispatchTime = currentTime + delay;

    		//and put it in the queue
    		mPriorityQ.insert(telegram);   
  	}
}

//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::dispatchDelayedMessages()
{ 
	//first get current time
  	double currentTime = mServer->mGameTime; 

  	//now peek at the queue to see if any telegrams need dispatching.
  	//remove all telegrams from the front of the queue that have gone
  	//past their sell by date
  	while( !mPriorityQ.empty() &&
	     (mPriorityQ.begin()->mDispatchTime < currentTime) && 
         (mPriorityQ.begin()->mDispatchTime > 0) )
  	{
    		//read the telegram from the front of the queue
    		const Telegram& telegram = *mPriorityQ.begin();

    		//find the recipient
    		BaseEntity* receiver = mServer->getBaseEntityFromID(telegram.mReceiver);

    		//send the telegram to the recipient
    		discharge(receiver, telegram);

		//remove it from the queue
    		mPriorityQ.erase(mPriorityQ.begin());
  	}
}



