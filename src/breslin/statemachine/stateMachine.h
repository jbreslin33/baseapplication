#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/

#include "State.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
//class AbilityMove;

/**********************************
*          CLASS
**********************************/

template <class T*>
class StateMachine
{
public:

StateMachine(T* owner):m_pOwner(owner),
	                           mCurrentState(0),
                                   mPreviousState(0),
                                   mGlobalState(0)
{

}
virtual ~StateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  
T*       mOwner;
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
	if(m_pGlobalState)
	{
		mGlobalState->execute(mOwner);
	}
	if (m_pCurrentState)
	{
		mCurrentState->execute(mOwner);
	}
 }

void  changeState(State* pNewState)
{
	mPreviousState = mCurrentState;

	if(mCurrentState)
	{
       		mCurrentState->exit(mOwner);
	}
    
    	mCurrentState = pNewState;

	if(mCurrentState)
	{
        	mCurrentState->enter(mOwner);
	}
}

};
#endif


