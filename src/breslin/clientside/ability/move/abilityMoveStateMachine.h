#ifndef ABILITYSTATEMACHINE_H
#define ABILITYSTATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/

#include "abilityState.h"

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
{

}
virtual ~AbilityStateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  
Ability*        m_pOwner;
AbilityState*   m_pCurrentState;
AbilityState*   m_pPreviousState;
AbilityState*   m_pGlobalState;

/**********************************
*          METHODS
**********************************/
public:

AbilityState*  currentState()  const
{
	return m_pCurrentState;
}

AbilityState*  globalState()   const
{
	return m_pGlobalState;
}
AbilityState*  previousState() const
{
	return m_pPreviousState;
}

void setCurrentState(AbilityState* s)
{
	m_pCurrentState = s;
}
void setGlobalState(AbilityState* s)
{
	m_pGlobalState = s;
}
void setPreviousState(AbilityState* s)
{
	m_pPreviousState = s;
}

void  update()const
{
	if(m_pGlobalState)
	{
		m_pGlobalState->execute(m_pOwner);
	}
	if (m_pCurrentState)
	{
		m_pCurrentState->execute(m_pOwner);
	}
 }

void  changeState(AbilityState* pNewState)
{
	m_pPreviousState = m_pCurrentState;

	if(m_pCurrentState)
	{
       m_pCurrentState->exit(m_pOwner);
	}
    
    m_pCurrentState = pNewState;

	if(m_pCurrentState)
	{
       m_pCurrentState->enter(m_pOwner);
	}
  }

void  revertToPreviousState()
{
	changeState(m_pPreviousState);
}

};
#endif


