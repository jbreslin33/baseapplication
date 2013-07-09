#include "messageDispatcher.h"
#include "../serverside/shape/shape.h"
//#include "misc/FrameCounter.h"
#include "../serverside/game/game.h"
#include "../serverside/server/server.h"

//log
#include "../serverside/tdreamsock/dreamSockLog.h"

using std::set;

MessageDispatcher::MessageDispatcher(Game* game)
{
        mGame = game;
}

MessageDispatcher::~MessageDispatcher()
{
}

void MessageDispatcher::discharge(Shape* pReceiver, const Telegram& telegram)
{
	if (!pReceiver->handleMessage(telegram))
  	{
		LogString("telegram could not be handled");
  	}
}

void MessageDispatcher::dispatchMsg(double       delay,
                                    int          sender,
                                    int          receiver,
                                    int          msg,
                                    void*        AdditionalInfo = NULL)
{

	//get a pointer to the receiver
  	Shape* pReceiver = mGame->getShapeFromID(receiver);

  	//make sure the receiver is valid
  	if (pReceiver == NULL)
  	{
		LogString("WARNING: Receiver not found with id:%d",receiver);
    		return;
  	}
  
  	//create the telegram
  	Telegram telegram(0, sender, receiver, msg, AdditionalInfo);
  
  	//if there is no delay, route telegram immediately                       
  	if (delay <= 0.0)                                                        
  	{
    		//send the telegram to the recipient
    		discharge(pReceiver, telegram);
  	}

  	//else calculate the time when the telegram should be dispatched
  	else
  	{
    		double currentTime = mGame->mServer->mGameTime; 

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
  	double currentTime = mGame->mServer->mGameTime; 

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
    		Shape* receiver = mGame->getShapeFromID(telegram.mReceiver);

    		//send the telegram to the recipient
    		discharge(receiver, telegram);

		//remove it from the queue
    		mPriorityQ.erase(mPriorityQ.begin());
  	}
}



