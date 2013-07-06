#ifndef SEEKSTATEMACHINE_H
#define SEEKSTATEMACHINE_H
#include "seekState.h"

class Seek;

class SeekStateMachine
{
private:
  //a pointer to the agent that owns this instance
  Seek*   mSeek;
  SeekState*    mCurrentState;

  //a record of the last state the agent was in
  SeekState*   mPreviousState;

  //this is called every time the FSM is updated
  SeekState*   mGlobalState;

public:

  SeekStateMachine(Seek* owner):mSeek(owner),
	                               mCurrentState(0),
                                   mPreviousState(0),
                                   mGlobalState(0)
  {}

  virtual ~SeekStateMachine(){}

  //use these methods to initialize the FSM
  void setCurrentState(SeekState* s){mCurrentState = s;}
  void setGlobalState(SeekState* s) {mGlobalState = s;}
  void setPreviousState(SeekState* s){mPreviousState = s;}

  //call this to update the FSM
  void  update()const
  {
    if(mGlobalState)
   	mGlobalState->execute(mSeek);
    if (mCurrentState) mCurrentState->execute(mSeek);
  }

  //change to a new state
  void  changeState(SeekState* mNewState)
  {

    mPreviousState = mCurrentState;

	if(mCurrentState)
       mCurrentState->exit(mSeek);

    mCurrentState = mNewState;

	if(mCurrentState)
       mCurrentState->enter(mSeek);
  }

  void  revertToPreviousState()
  {
    changeState(mPreviousState);
  }

  SeekState*  currentState()  const{return mCurrentState;}
  SeekState*  globalState()   const{return mGlobalState;}
  SeekState*  previousState() const{return mPreviousState;}
};
#endif


