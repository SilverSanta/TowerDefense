#pragma once

#include <algorithm>

#include "UserExtension.h"
#include "UserBlueprints.h"
#include "ECS_Framework.h"

// NEW COMPONENT CLASS NEEDS TO BE INCLUDED IN THE SWITCH
void ComponentsManager::_DeleteComponents(std::unordered_map<user::ComponentType, uint64_t> IDsOfComponentsToBeDeleted)
{
	LegacyComponentsManager::_DeleteComponents(IDsOfComponentsToBeDeleted);


	for (const auto& component : IDsOfComponentsToBeDeleted)
	{
		switch (component.first)
		{	
		case user::ComponentType::AI:
			_RemoveComponent(m_Components_AI, component.second);
			break;
		case user::ComponentType::ATTACK:
			_RemoveComponent(m_Components_Attack, component.second);
			break;
		case user::ComponentType::BALLISTA:
			_RemoveComponent(m_Components_Ballista, component.second);
			break;
		case user::ComponentType::BARRICADE:
			_RemoveComponent(m_Components_Barricade, component.second);
			break;
		case user::ComponentType::BUTTON:
			_RemoveComponent(m_Components_Button, component.second);
			break;	
		case user::ComponentType::CAMERA:
			_RemoveComponent(m_Components_Camera, component.second);
			break;
		case user::ComponentType::ENEMY:
			_RemoveComponent(m_Components_Enemy, component.second);
			break;
		case user::ComponentType::HEALTH:
			_RemoveComponent(m_Components_Health, component.second);
			break;
		case user::ComponentType::NODE:
			_RemoveComponent(m_Components_Node, component.second);
			break;	
		case user::ComponentType::PATHFINDING:
			_RemoveComponent(m_Components_Pathfinding, component.second);
			break;
		case user::ComponentType::PROJECTILE:
			_RemoveComponent(m_Components_Projectile, component.second);
			break;
		case user::ComponentType::RESOURCES:
			_RemoveComponent(m_Components_Resources, component.second);
			break;
		case user::ComponentType::TIME:
			_RemoveComponent(m_Components_Time, component.second);
			break;
		case user::ComponentType::TEST:
			_RemoveComponent(m_Components_Test, component.second);
			break;
		case user::ComponentType::TEXT:
			_RemoveComponent(m_Components_Text, component.second);
			break;
		case user::ComponentType::TRAP:
			_RemoveComponent(m_Components_Trap, component.second);
			break;

			// USER-DEFININED
			// USER-DEFININED
			// USER-DEFININED
			// USER-DEFININED
			// USER-DEFININED
			// USER-DEFININED
		}
	}
}


// NEW COMPONENT CLASS NEEDS TO BE UPDATED
void ComponentsManager::_UpdateRepositories(uint64_t currenttime)
{
	LegacyComponentsManager::_UpdateRepositories(currenttime);

	_UpdateComponents(m_Components_AI, currenttime);
	_UpdateComponents(m_Components_Attack, currenttime);
	_UpdateComponents(m_Components_Ballista, currenttime);
	_UpdateComponents(m_Components_Barricade, currenttime);
	_UpdateComponents(m_Components_Button, currenttime);
	_UpdateComponents(m_Components_Camera, currenttime);
	_UpdateComponents(m_Components_Enemy, currenttime);
	_UpdateComponents(m_Components_Health, currenttime);
	_UpdateComponents(m_Components_Node, currenttime);
	_UpdateComponents(m_Components_Pathfinding, currenttime);
	_UpdateComponents(m_Components_Projectile, currenttime);
	_UpdateComponents(m_Components_Resources, currenttime);
	_UpdateComponents(m_Components_Test, currenttime);
	_UpdateComponents(m_Components_Text, currenttime);
	_UpdateComponents(m_Components_Time, currenttime);
	_UpdateComponents(m_Components_Trap, currenttime);

	// USER-DEFININED
	// USER-DEFININED
	// USER-DEFININED
	// USER-DEFININED
	// USER-DEFININED
	// USER-DEFININED
}
void ComponentsManager::_SortTextByLayer()
{
	if ((int)m_Components_Text.size() <= 1) { return; }

	auto* TextPtr = &m_Components_Text;

	for (int i = 1; i < (int)TextPtr->size(); i++)
	{
		auto key = TextPtr->at(i);
		int keyLayerIndex = (int)key.m_TextLayer;
		int j = i - 1;

		while (j >= 0 && (int)TextPtr->at(j).m_TextLayer > keyLayerIndex)
		{
			TextPtr->at(j + 1) = TextPtr->at(j);
			j = j - 1;
		}
		TextPtr->at(j + 1) = key;
	}
}


// NEW SYSTEM NEEDS TO BE IMPLEMENTED IN THE CONSTRUCTOR
SystemsManager::SystemsManager(EntitiesManager* entitiesmanager, ComponentsManager* componentsmanager, UserBlueprints* blueprints) : LegacySystemsManager(entitiesmanager, componentsmanager, blueprints)
{
	m_System_Test = new TestSystem(m_Manager_Components, m_Manager_Entities);
	m_System_Camera = new CameraSystem(m_Manager_Components, m_Manager_Entities, m_System_State);
	m_System_ImportData = new ImportAndProcessDataSystem(m_Manager_Components, m_Manager_Entities, m_System_State);
	m_System_Resources = new ResourcesSystem(m_Manager_Components, m_Manager_Entities, m_System_State);
	m_System_HealthAndAttack = new HealthAndAttackSystem(m_Manager_Components, m_Manager_Entities, m_System_State, m_System_Animation, m_System_Resources);
	m_System_Pathfinding = new PathfindingSystem(m_Manager_Components, m_Manager_Entities, this);

	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
}


// NEW STATES WITH TIMERS NEED TO BE INCLUDED BELOW (CHECKED EVERY FRAME)
void StateSystem::_UpdateState_PreviousToCurrent(StateComponent* stateptr)
{
	if (stateptr->m_CurrentSubState == user::SubState::ACTION_ATTACKING && stateptr->m_Time_Current - stateptr->m_Time_StartOfCurrentState >= stateptr->m_Time_Attacking * 1000)
	{
		_ReturnToIdle(stateptr);
	}
	else if (stateptr->m_CurrentSubState == user::SubState::ACTION_USING_POTION && stateptr->m_Time_Current - stateptr->m_Time_StartOfCurrentState >= stateptr->m_Time_UsingPotion * 1000)
	{
		_ReturnToIdle(stateptr);
	}
	else if (stateptr->m_CurrentSubState == user::SubState::ACTION_SPRINGING_TRAP && stateptr->m_Time_Current - stateptr->m_Time_StartOfCurrentState >= stateptr->m_Time_SpringingSpikes * 1000)
	{
		_ReturnToIdle(stateptr);
	}
	else if (stateptr->m_CurrentSubState == user::SubState::ACTION_SHOOTING && stateptr->m_Time_Current - stateptr->m_Time_StartOfCurrentState >= stateptr->m_Time_Shooting * 1000)
	{		
		_ChangeCurrentState(stateptr, user::State::STATUS_EFFECT, user::SubState::STATUS_RELOADING, stateptr->m_CurrentDirection);


		// Get Ballista pointers
		Entity* Ballista_EntityPtr = m_Manager_Entities->_Get_EntityById(stateptr->Get_OwnerId());
		TransformComponent* Ballista_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(Ballista_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
		BallistaComponent* Ballista_BallistaPtr = m_Manager_Components->_Get_ComponentPtrFromId(Ballista_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::BALLISTA), m_Manager_Components->m_Components_Ballista);

		int ARROW_LENGTH = 46;

		uint64_t Arrow = m_Blueprints->_Create_BallistaArrow(Ballista_TransformPtr->m_X, Ballista_TransformPtr->m_Y, Ballista_TransformPtr->m_TransformAngle.x, Ballista_TransformPtr->m_TransformAngle.y, ARROW_LENGTH, Ballista_BallistaPtr->m_Damage, 3.f, stateptr->m_Time_Current, user::TimerType::_NONE);
	}
	else if (stateptr->m_CurrentSubState == user::SubState::STATUS_RELOADING && stateptr->m_Time_Current - stateptr->m_Time_StartOfCurrentState >= stateptr->m_Time_Reloading * 1000)
	{
		// Change the ballista to default setting
		_ReturnToIdle(stateptr);

	}

	else if (stateptr->m_CurrentSubState == user::SubState::DYING_NORMAL && stateptr->m_Time_Current - stateptr->m_Time_StartOfCurrentState >= stateptr->m_Time_Dying * 1000)
	{
		_ChangeCurrentState(stateptr, user::State::DEAD, user::SubState::DEAD_NORMAL, stateptr->m_CurrentDirection);
	}

	else
	{
		stateptr->m_StateFromPreviousFrame = stateptr->m_CurrentState;
		stateptr->m_SubStateFromPreviousFrame = stateptr->m_CurrentSubState;
		stateptr->m_DirectionFromPreviousFrame = stateptr->m_CurrentDirection;
	}
}
