#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
#pragma warning (disable:4786)

#include <set>
#include <string>
#include "telegram.h"

class Server;
class BaseEntity;

//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;


class MessageDispatcher
{

private:  
  
	MessageDispatcher(Server* server);
	~MessageDispatcher();
  
	std::set<Telegram> mPriorityQ;
 	void discharge(BaseEntity* receiver, const Telegram& message);

	public:

	Server* mServer;
	
	void dispatchMsg(double      delay,
                   int         sender,
                   int         receiver,
                   int         msg,
                   void*       ExtraInfo);

	void dispatchDelayedMessages();
};

#endif
