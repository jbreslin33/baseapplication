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

void MessageDispatcher::Discharge(Shape* pReceiver, const Telegram& telegram)
{
	if (!pReceiver->handleMessage(telegram))
  	{
		LogString("telegram could not be handled");
  	}
}

void MessageDispatcher::DispatchMsg(double       delay,
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
    		Discharge(pReceiver, telegram);
  	}

  	//else calculate the time when the telegram should be dispatched
  	else
  	{
    		double CurrentTime = mGame->mServer->mGameTime; 

    		telegram.DispatchTime = CurrentTime + delay;

    		//and put it in the queue
    		PriorityQ.insert(telegram);   
  	}
}

//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages()
{ 
	//first get current time
  	double CurrentTime = mGame->mServer->mGameTime; 

  	//now peek at the queue to see if any telegrams need dispatching.
  	//remove all telegrams from the front of the queue that have gone
  	//past their sell by date
  	while( !PriorityQ.empty() &&
	     (PriorityQ.begin()->DispatchTime < CurrentTime) && 
         (PriorityQ.begin()->DispatchTime > 0) )
  	{
    		//read the telegram from the front of the queue
    		const Telegram& telegram = *PriorityQ.begin();

    		//find the recipient
    		Shape* pReceiver = mGame->getShapeFromID(telegram.Receiver);

    		//send the telegram to the recipient
    		Discharge(pReceiver, telegram);

		//remove it from the queue
    		PriorityQ.erase(PriorityQ.begin());
  	}
}



