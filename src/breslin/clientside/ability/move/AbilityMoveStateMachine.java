package breslin.clientside.ability.move;

/**********************************
*          INCLUDES
**********************************/

//move
import breslin.clientside.ability.move.AbilityMove;
import breslin.clientside.ability.move.AbilityMoveState;

/**********************************
*          CLASS
**********************************/
public class AbilityMoveStateMachine
{


public AbilityMoveStateMachine(AbilityMove owner)

{
	m_pOwner = owner;
	m_pCurrentState  = null;
   	m_pPreviousState = null;
    m_pGlobalState   = null;


}

/**********************************
*          VARIABLES
**********************************/

AbilityMove        m_pOwner;
AbilityMoveState   m_pCurrentState;
AbilityMoveState   m_pPreviousState;
AbilityMoveState   m_pGlobalState;

/**********************************
*          METHODS
**********************************/

void setCurrentState(AbilityMoveState s)
{
	m_pCurrentState = s;
}
void setGlobalState(AbilityMoveState s)
{
	m_pGlobalState = s;
}
void setPreviousState(AbilityMoveState s)
{
	m_pPreviousState = s;
}

void  update()
{
	if(m_pGlobalState != null)
	{
		m_pGlobalState.execute(m_pOwner);
	}
	if (m_pCurrentState != null)
	{
		m_pCurrentState.execute(m_pOwner);
	}
 }

void  changeState(AbilityMoveState pNewState)
{
	m_pPreviousState = m_pCurrentState;

	if(m_pCurrentState != null)
	{
       m_pCurrentState.exit(m_pOwner);
	}

    m_pCurrentState = pNewState;

	if(m_pCurrentState != null)
	{
       m_pCurrentState.enter(m_pOwner);
	}
  }
}

