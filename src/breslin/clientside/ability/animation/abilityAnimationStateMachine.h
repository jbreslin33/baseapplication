#ifndef ABILITYANIMATIONSTATEMACHINE_H
#define ABILITYANIMATIONSTATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/

#include "abilityAnimationState.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class AbilityAnimationOgre;

/**********************************
*          CLASS
**********************************/
class AbilityAnimationStateMachine
{
public:

AbilityAnimationStateMachine(AbilityAnimationOgre* owner):m_pOwner(owner),
	                               m_pCurrentState(0),
                                   m_pPreviousState(0),
                                   m_pGlobalState(0)
{

}
virtual ~AbilityAnimationStateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  
AbilityAnimationOgre*        m_pOwner;
AbilityAnimationState*   m_pCurrentState;
AbilityAnimationState*   m_pPreviousState;
AbilityAnimationState*   m_pGlobalState;

/**********************************
*          METHODS
**********************************/
public:

void setCurrentState(AbilityAnimationState* s)
{
	m_pCurrentState = s;
}
void setGlobalState(AbilityAnimationState* s)
{
	m_pGlobalState = s;
}
void setPreviousState(AbilityAnimationState* s)
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

void  changeState(AbilityAnimationState* pNewState)
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
};
#endif


