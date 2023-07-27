#pragma once

#include "ActionSystem.h"

#include "EntitiesManager.h"
#include "UserExtension.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "MovementComponent.h"
#include "MovementSystem.h"
#include "StateSystem.h"
#include "HealthAndAttackSystem.h"
#include "UserGameState.h"
#include "ECS_Framework.h"


// CONSTRUCTORS
ActionSystem::ActionSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, MovementSystem* systemmovement, StateSystem* statesystem)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_System_Movement = systemmovement;
	m_System_State = statesystem;
}
ActionSystem::~ActionSystem(){}


// DEFINITIONS
void ActionSystem::_Action_StopMoving(MovementComponent* MovementPtr, StateComponent* StatePtr)
{
	if (MovementPtr != nullptr && StatePtr != nullptr)
	{
		m_System_State->_ChangeCurrentState(StatePtr, user::State::IDLE, user::SubState::IDLE_DEFAULT, StatePtr->m_CurrentDirection);
	}
}
void ActionSystem::_Action_WalkTo(MovementComponent* MovementPtr, TransformComponent* TransformPtr, StateComponent* StatePtr, int targetx, int targety)
{
	if (TransformPtr != nullptr && MovementPtr != nullptr && StatePtr != nullptr)
	{
		// (1) HEADING
		MovementPtr->m_NormalVector.NormalBetweenTwoPoints(TransformPtr->m_X, TransformPtr->m_Y, (float)targetx, (float)targety);
		// (2) Setting the target
		MovementPtr->m_Target_X = targetx;
		MovementPtr->m_Target_Y = targety;
		MovementPtr->m_bHasTarget = true;
		// (3) Walk
		_Action_Walk(MovementPtr, StatePtr);
	}
}
void ActionSystem::_Action_Walk(MovementComponent* MovementPtr, StateComponent* StatePtr)
{
	if (MovementPtr != nullptr && StatePtr != nullptr)
	{
		m_System_State->_ChangeCurrentState(StatePtr, user::State::MOVING, user::SubState::MOVING_WALKING, StatePtr->m_CurrentDirection);
	}
}
void ActionSystem::_Action_Attack(uint64_t AttackerID, uint64_t DefenderID)
{	
	Entity* Attacker = m_Manager_Entities->_Get_EntityById(AttackerID);
	Entity* Defender = m_Manager_Entities->_Get_EntityById(DefenderID);

	if (Defender == nullptr)
	{
		StateComponent* Attacker_State = m_Manager_Components->_Get_ComponentPtrFromId(Attacker->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);

		m_System_State->_ReturnToIdle(Attacker_State);
		return;
	}
	else if (Attacker->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL && Attacker->_Get_ComponentIdFromEntityByType(user::ComponentType::ATTACK) != NULL && Defender->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH) != NULL)
	{
		// Change state of the attacked to ATTACKING
		StateComponent* Attacker_State = m_Manager_Components->_Get_ComponentPtrFromId(Attacker->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		AttackComponent* Attacker_AttackPtr = m_Manager_Components->_Get_ComponentPtrFromId(Attacker->_Get_ComponentIdFromEntityByType(user::ComponentType::ATTACK), m_Manager_Components->m_Components_Attack);		
		HealthComponent* Defender_HealthPtr = m_Manager_Components->_Get_ComponentPtrFromId(Defender->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH), m_Manager_Components->m_Components_Health);
		
		m_System_State->_ChangeCurrentState(Attacker_State, user::State::TAKING_ACTION, user::SubState::ACTION_ATTACKING, Attacker_State->m_CurrentDirection);
		
		m_System_HealthAndAttack->_ApplyDamage(Defender, (int)Attacker_AttackPtr->m_MeleeDmg, m_System_HealthAndAttack->m_GameState->m_EntitiesToBeDeleted, m_System_HealthAndAttack->m_GameState, m_System_HealthAndAttack->m_Game->_Get_Renderer());
		
	}
}
void ActionSystem::_Action_DropDead(uint64_t DyingAgentID)
{
	Entity* DyingAgent = m_Manager_Entities->_Get_EntityById(DyingAgentID);

	if (DyingAgent->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL && DyingAgent->_Get_ComponentIdFromEntityByType(user::ComponentType::ACTION) != NULL)
	{
		// Change state of the dying agend to DROPPINGDEAD		
		StateComponent* DyingAgent_State = m_Manager_Components->_Get_ComponentPtrFromId(DyingAgent->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		m_System_State->_ChangeCurrentState(DyingAgent_State, user::State::DYING, user::SubState::DYING_NORMAL, DyingAgent_State->m_CurrentDirection);
	}
}
void ActionSystem::_Action_UsePotion(uint64_t UnitID)
{
	Entity* Unit = m_Manager_Entities->_Get_EntityById(UnitID);

	if (Unit->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL)
	{
		// Change state of the attacked to ATTACKING
		StateComponent* Unit_State = m_Manager_Components->_Get_ComponentPtrFromId(Unit->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		m_System_State->_ChangeCurrentState(Unit_State, user::State::TAKING_ACTION, user::SubState::ACTION_USING_POTION, Unit_State->m_CurrentDirection);




		// WIP
		// WIP
		// WIP
		// WIP
		// WIP
	}
}

void ActionSystem::_Action_SpringTrap(uint64_t TrapId)
{
	Entity* m_Trap = m_Manager_Entities->_Get_EntityById(TrapId);

	if (m_Trap->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL && m_Trap->_Get_ComponentIdFromEntityByType(user::ComponentType::TRAP) != NULL)
	{
		// Change state of the attacked to ATTACKING
		StateComponent* Trap_State = m_Manager_Components->_Get_ComponentPtrFromId(m_Trap->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		TrapComponent* Trap_TrapComponent = m_Manager_Components->_Get_ComponentPtrFromId(m_Trap->_Get_ComponentIdFromEntityByType(user::ComponentType::TRAP), m_Manager_Components->m_Components_Trap);
				
		m_System_State->_ChangeCurrentState(Trap_State, user::State::TAKING_ACTION, user::SubState::ACTION_SPRINGING_TRAP, Trap_State->m_CurrentDirection);
	}
}

void ActionSystem::_Action_Shoot(uint64_t ShooterId)
{
	Entity* Shooter = m_Manager_Entities->_Get_EntityById(ShooterId);

	if (Shooter->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE) != NULL)
	{
		// Change state of the attacked to ATTACKING
		StateComponent* Shooter_State = m_Manager_Components->_Get_ComponentPtrFromId(Shooter->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
		m_System_State->_ChangeCurrentState(Shooter_State, user::State::TAKING_ACTION, user::SubState::ACTION_SHOOTING, Shooter_State->m_CurrentDirection);
	}
}
