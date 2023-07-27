#pragma once

#include "HealthAndAttackSystem.h"
#include "UserExtension.h"
#include "UserGameState.h"
#include "SDL.h"
#include "ECS_Framework.h"

HealthAndAttackSystem::HealthAndAttackSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem, AnimationSystem* animationsystem, ResourcesSystem* resourcessystem)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_System_State = statesystem;
	m_System_Animation = animationsystem;
	m_System_Resources = resourcessystem;
}
HealthAndAttackSystem::~HealthAndAttackSystem(){}

void HealthAndAttackSystem::_ApplyDamage(Entity* DamagedObject, int dmgvalue, std::vector<uint64_t>& m_EntitiesToBeDeleted, UserGameState* gamestate, SDL_Renderer* renderer)
{
	// Check if entity has health component
	uint64_t HealthComponentId = DamagedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH);
	uint64_t HealthbarSpriteId = DamagedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE2);

	if (HealthComponentId != NULL && HealthbarSpriteId != NULL)
	{
		HealthComponent* HealthComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(DamagedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH), m_Manager_Components->m_Components_Health);
		
		if (HealthComponentPtr->m_CurrentHealth - dmgvalue > 0)
		{
			HealthComponentPtr->m_CurrentHealth -= dmgvalue;
		}
		else
		{
			uint64_t StateComponentId = DamagedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE);
			if (StateComponentId == NULL)
			{					
				if (std::find(m_EntitiesToBeDeleted.begin(), m_EntitiesToBeDeleted.end(), DamagedObject->_Get_EntityId()) == m_EntitiesToBeDeleted.end())
				{					
					m_EntitiesToBeDeleted.push_back(DamagedObject->_Get_EntityId());
				}
			}
			else
			{
				StateComponent* StateComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(DamagedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
				m_System_State->_ChangeCurrentState(StateComponentPtr, user::State::DYING, user::SubState::DYING_NORMAL, StateComponentPtr->m_CurrentDirection);				
			}
			
			HealthComponentPtr->m_CurrentHealth = 0;			
		}
	
		_Update_HealthBar(DamagedObject);
	}	
}
void HealthAndAttackSystem::_ApplyHeal(Entity* HealedObject, int healvalue)
{
	// Check if entity has health component
	uint64_t HealthComponentId = HealedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH);
	uint64_t HealthbarSpriteId = HealedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE2);

	if (HealthComponentId != NULL && HealthbarSpriteId != NULL)
	{
		HealthComponent* HealthComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(HealedObject->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH), m_Manager_Components->m_Components_Health);

		if (HealthComponentPtr->m_CurrentHealth + healvalue > HealthComponentPtr->m_MaxHealth)
		{
			HealthComponentPtr->m_CurrentHealth = HealthComponentPtr->m_MaxHealth;
		}
		else
		{
			HealthComponentPtr->m_CurrentHealth += healvalue;
		}

		_Update_HealthBar(HealedObject);
	}
}
void HealthAndAttackSystem::_Update_HealthBar(Entity* entity)
{
	// Check if entity has health component and sprite (2) component
	uint64_t HealthComponentId = entity->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH);
	uint64_t HealthbarSpriteId = entity->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE2);

	if (HealthComponentId != NULL && HealthbarSpriteId != NULL)
	{
		AnimatedSpriteComponent* HealthbarSpritePtr = m_Manager_Components->_Get_ComponentPtrFromId(entity->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE2), m_Manager_Components->m_Components_AnimatedSprite);
		HealthComponent* HealthComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(entity->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH), m_Manager_Components->m_Components_Health);

		float HealthPercentage = (float)HealthComponentPtr->m_CurrentHealth / (float)HealthComponentPtr->m_MaxHealth;

		int Index = 1;

		// LOGIC
		if (HealthPercentage >= 0.95) { Index = 1; }
		else if (HealthPercentage >= 0.85 && HealthPercentage < 0.95) { Index = 2; }
		else if (HealthPercentage >= 0.75 && HealthPercentage < 0.85) { Index = 3; }
		else if (HealthPercentage >= 0.65 && HealthPercentage < 0.75) { Index = 4; }
		else if (HealthPercentage >= 0.55 && HealthPercentage < 0.65) { Index = 5; }
		else if (HealthPercentage >= 0.45 && HealthPercentage < 0.55) { Index = 6; }
		else if (HealthPercentage >= 0.35 && HealthPercentage < 0.45) { Index = 7; }
		else if (HealthPercentage >= 0.25 && HealthPercentage < 0.35) { Index = 8; }
		else if (HealthPercentage >= 0.15 && HealthPercentage < 0.25) { Index = 9; }
		else if (HealthPercentage >= 0.05 && HealthPercentage < 0.15) { Index = 10; }
		else if (HealthPercentage < 0.05) { Index = 11; }

		m_System_Animation->_Set_AnimationIndex(HealthbarSpritePtr, Index);
	}
}


