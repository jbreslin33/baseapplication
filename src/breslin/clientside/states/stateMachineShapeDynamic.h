#ifndef ABILITYSTATEMACHINE_H
#define ABILITYSTATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/
//parent
#include "stateAbility.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class Ability;

/**********************************
*          CLASS
**********************************/
class AbilityStateMachine
{
public:

  AbilityStateMachine(Ability* owner):m_pOwner(owner),
	                               m_pCurrentState(0),
                                   m_pPreviousState(0),
                                   m_pGlobalState(0)
  {}
  virtual ~AbilityStateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  //a pointer to the agent that owns this instance
  Ability*   m_pOwner;
  AbilityState*    m_pCurrentState;

  //a record of the last state the agent was in
  AbilityState*   m_pPreviousState;

  //this is called every time the FSM is updated
  AbilityState*   m_pGlobalState;

/**********************************
*          METHODS
**********************************/
public:

  AbilityState*  currentState()  const{return m_pCurrentState;}
  AbilityState*  globalState()   const{return m_pGlobalState;}
  AbilityState*  previousState() const{return m_pPreviousState;}

  //use these methods to initialize the FSM
  void setCurrentState(AbilityState* s){m_pCurrentState = s;}
  void setGlobalState(AbilityState* s) {m_pGlobalState = s;}
  void setPreviousState(AbilityState* s){m_pPreviousState = s;}

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
  void  changeState(AbilityState* pNewState)
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


