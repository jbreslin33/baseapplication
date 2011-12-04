#ifndef ABILITYMOVESTATEMACHINE_H
#define ABILITYMOVESTATEMACHINE_H

/**********************************
*          INCLUDES
**********************************/

#include "abilityMoveState.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class AbilityMove;

/**********************************
*          CLASS
**********************************/
class AbilityMoveStateMachine
{
public:

AbilityMoveStateMachine(AbilityMove* owner):m_pOwner(owner),
	                               m_pCurrentState(0),
                                   m_pPreviousState(0),
                                   m_pGlobalState(0)
{

}
virtual ~AbilityMoveStateMachine(){}

/**********************************
*          VARIABLES
**********************************/
private:
  
AbilityMove*        m_pOwner;
AbilityMoveState*   m_pCurrentState;
AbilityMoveState*   m_pPreviousState;
AbilityMoveState*   m_pGlobalState;

/**********************************
*          METHODS
**********************************/
public:

void setCurrentState(AbilityMoveState* s)
{
	m_pCurrentState = s;
}
void setGlobalState(AbilityMoveState* s)
{
	m_pGlobalState = s;
}
void setPreviousState(AbilityMoveState* s)
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

void  changeState(AbilityMoveState* pNewState)
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


