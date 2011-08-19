#ifndef SHAPEDYNAMICSTATEMACHINE_H
#define SHAPEDYNAMICSTATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/
//parent
#include "stateShapeDynamic.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class ShapeDynamic;

/**********************************
*          CLASS
**********************************/
class ShapeDynamicStateMachine
{
public:

  ShapeDynamicStateMachine(ShapeDynamic* owner):m_pOwner(owner),
	                               m_pCurrentState(0),
                                   m_pPreviousState(0),
                                   m_pGlobalState(0)
  {}
  virtual ~ShapeDynamicStateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  //a pointer to the agent that owns this instance
  ShapeDynamic*   m_pOwner;
  ShapeDynamicState*    m_pCurrentState;

  //a record of the last state the agent was in
  ShapeDynamicState*   m_pPreviousState;

  //this is called every time the FSM is updated
  ShapeDynamicState*   m_pGlobalState;

/**********************************
*          METHODS
**********************************/
public:

  ShapeDynamicState*  currentState()  const{return m_pCurrentState;}
  ShapeDynamicState*  globalState()   const{return m_pGlobalState;}
  ShapeDynamicState*  previousState() const{return m_pPreviousState;}

  //use these methods to initialize the FSM
  void setCurrentState(ShapeDynamicState* s){m_pCurrentState = s;}
  void setGlobalState(ShapeDynamicState* s) {m_pGlobalState = s;}
  void setPreviousState(ShapeDynamicState* s){m_pPreviousState = s;}

  //call this to update the FSM
  void  update()const
  {
    //if a global state exists, call its execute method, else do nothing
    if(m_pGlobalState)   m_pGlobalState->execute(m_pOwner);
    //same for the current state
	    //Con::errorf("fieldPlayerStateMachine update");
    if (m_pCurrentState) m_pCurrentState->execute(m_pOwner);
  }

  //change to a new state
  void  changeState(ShapeDynamicState* pNewState)
  {
   // assert(pNewState &&
           //"<StateMachine::ChangeState>: trying to change to NULL state");

    //keep a record of the previous state
    m_pPreviousState = m_pCurrentState;

    //call the exit method of the existing state
	if(m_pCurrentState)
       m_pCurrentState->exit(m_pOwner);

    //change state to the new state
    m_pCurrentState = pNewState;

    //call the entry method of the new state
	if(m_pCurrentState)
       m_pCurrentState->enter(m_pOwner);
  }

  //change state back to the previous state
  void  revertToPreviousState()
  {
    changeState(m_pPreviousState);
  }
};
#endif


