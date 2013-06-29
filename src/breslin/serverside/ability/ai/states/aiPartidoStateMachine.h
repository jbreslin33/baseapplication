#ifndef AIPARTIDOSTATEMACHINE_H
#define AIPARTIDOSTATEMACHINE_H
#include "aiPartidoState.h"

class AIPartido;

class AIPartidoStateMachine : AIStateMachine
{
private:
  //a pointer to the agent that owns this instance
  AIPartido*   mAIPartido;
  AIPartidoState*    m_pCurrentState;

  //a record of the last state the agent was in
  AIState*   m_pPreviousState;

  //this is called every time the FSM is updated
  AIState*   m_pGlobalState;

public:

  AIStateMachine(AI* owner):m_pOwner(owner),
	                               m_pCurrentState(0),
                                   m_pPreviousState(0),
                                   m_pGlobalState(0)
  {}

  virtual ~AIStateMachine(){}

  void setCurrentState(AIState* s){m_pCurrentState = s;}
  void setGlobalState(AIState* s) {m_pGlobalState = s;}
  void setPreviousState(AIState* s){m_pPreviousState = s;}

  //call this to update the FSM
  void  update()const
  {
    if(m_pGlobalState)   m_pGlobalState->execute(m_pOwner);
    if (m_pCurrentState) m_pCurrentState->execute(m_pOwner);
  }

  //change to a new state
  void  changeState(AIState* pNewState)
  {

    m_pPreviousState = m_pCurrentState;

	if(m_pCurrentState)
       m_pCurrentState->exit(m_pOwner);

    m_pCurrentState = pNewState;

	if(m_pCurrentState)
       m_pCurrentState->enter(m_pOwner);
  }

  void  revertToPreviousState()
  {
    changeState(m_pPreviousState);
  }

  AIState*  currentState()  const{return m_pCurrentState;}
  AIState*  globalState()   const{return m_pGlobalState;}
  AIState*  previousState() const{return m_pPreviousState;}
};
#endif


