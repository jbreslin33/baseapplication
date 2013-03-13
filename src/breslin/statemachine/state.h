#ifndef STATE_H
#define STATE_H

#include "../clientside/io/editString.h"

class State
{
public:

virtual ~State(){}

virtual void enter  ()=0;
virtual void execute()=0;
virtual void exit   ()=0;
virtual EditString* getEditString() { return mEditString; } 

EditString* mEditString;	
};

#endif
