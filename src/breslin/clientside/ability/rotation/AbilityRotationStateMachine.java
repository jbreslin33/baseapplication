package breslin.clientside.ability;

/**********************************
*          INCLUDES
**********************************/

//rotation
import breslin.clientside.ability.rotation.AbilityRotation;
import breslin.clientside.ability.rotation.AbilityRotationState;

/**********************************
*          CLASS
**********************************/
public class AbilityRotationStateMachine
{


public AbilityRotationStateMachine(AbilityRotation owner)

{
	m_pOwner = owner;
	m_pCurrentState  = null;
   	m_pPreviousState = null;
    m_pGlobalState   = null;


}

/**********************************
*          VARIABLES
**********************************/

AbilityRotation        m_pOwner;
AbilityRotationState   m_pCurrentState;
AbilityRotationState   m_pPreviousState;
AbilityRotationState   m_pGlobalState;

/**********************************
*          METHODS
**********************************/

void setCurrentState(AbilityRotationState s)
{
	m_pCurrentState = s;
}
void setGlobalState(AbilityRotationState s)
{
	m_pGlobalState = s;
}
void setPreviousState(AbilityRotationState s)
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

void  changeState(AbilityRotationState pNewState)
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

