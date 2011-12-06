#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/

#include "State.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/


/**********************************
*          CLASS
**********************************/

class StateMachine
{
public:

StateMachine():                    mCurrentState(0),
                                   mPreviousState(0),
                                   mGlobalState(0)
{

}
virtual ~StateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  
State*   mCurrentState;
State*   mPreviousState;
State*   mGlobalState;

/**********************************
*          METHODS
**********************************/
public:

void setCurrentState(State* s)
{
	mCurrentState = s;
}
void setGlobalState(State* s)
{
	mGlobalState = s;
}
void setPreviousState(State* s)
{
	mPreviousState = s;
}

void  update()const
{
	if(mGlobalState)
	{
		mGlobalState->execute();
	}
	if (mCurrentState)
	{
		mCurrentState->execute();
	}
 }

void  changeState(State* pNewState)
{
	mPreviousState = mCurrentState;

	if(mCurrentState)
	{
       		mCurrentState->exit();
	}
    
    	mCurrentState = pNewState;

	if(mCurrentState)
	{
        	mCurrentState->enter();
	}
}

};
#endif


