#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "../messaging/telegram.h"

class BaseEntity
{
public:

BaseEntity(int id);
~BaseEntity();

int mID;

static int mNextValidID;

virtual void update()=0;

virtual bool handleMessage(const Telegram& msg)=0;

void setID(int id);
int  getID()const { return mID; }
  //use this to grab the next valid ID

static int   getNextValidID(){ return mNextValidID; }

};
#endif

