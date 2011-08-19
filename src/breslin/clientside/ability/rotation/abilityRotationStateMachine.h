#ifndef ABILITYROTATIONSTATEMACHINE_H
#define ABILITYROTATIONSTATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/

#include "abilityRotationState.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class AbilityRotation;

/**********************************
*          CLASS
**********************************/
class AbilityRotationStateMachine
{
public:

AbilityRotationStateMachine(AbilityRotation* owner):m_pOwner(owner),
	                               m_pCurrentState(0),
                                   m_pPreviousState(0),
                                   m_pGlobalState(0)
{

}
virtual ~AbilityRotationStateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  
AbilityRotation*        m_pOwner;
AbilityRotationState*   m_pCurrentState;
AbilityRotationState*   m_pPreviousState;
AbilityRotationState*   m_pGlobalState;

/**********************************
*          METHODS
**********************************/
public:

AbilityRotationState*  currentState()  const
{
	return m_pCurrentState;
}

AbilityRotationState*  globalState()   const
{
	return m_pGlobalState;
}
AbilityRotationState*  previousState() const
{
	return m_pPreviousState;
}

void setCurrentState(AbilityRotationState* s)
{
	m_pCurrentState = s;
}
void setGlobalState(AbilityRotationState* s)
{
	m_pGlobalState = s;
}
void setPreviousState(AbilityRotationState* s)
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

void  changeState(AbilityRotationState* pNewState)
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


