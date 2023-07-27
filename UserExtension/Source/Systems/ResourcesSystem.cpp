#pragma once

#include "ResourcesSystem.h"
#include "UserExtension.h"
#include "UserGameState.h"


ResourcesSystem::ResourcesSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_System_State = statesystem;
}
ResourcesSystem::~ResourcesSystem(){}

void ResourcesSystem::_Score_AddOrSubtract(ResourcesComponent* PlayerResources, ResourcesComponent* ScorerResources, TextComponent* ScoreDisplayText, SDL_Renderer* renderer)
{
	PlayerResources->m_Score += ScorerResources->m_Score;

	_Score_UpdateDisplayText(PlayerResources, ScoreDisplayText, renderer);
}
void ResourcesSystem::_Gold_Add(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* GoldDisplayText, SDL_Renderer* renderer)
{
	if (PlayerResources->m_Gold_Current + ObjectResources->m_Gold_Current <= PlayerResources->m_Gold_Max)
	{
		PlayerResources->m_Gold_Current += ObjectResources->m_Gold_Current;
	}
	else
	{
		PlayerResources->m_Gold_Current = PlayerResources->m_Gold_Max;
	}	

	_Gold_UpdateDisplayText(PlayerResources, GoldDisplayText, renderer);
}
bool ResourcesSystem::_Gold_Subtract(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* GoldDisplayText, SDL_Renderer* renderer)
{
	if (PlayerResources->m_Gold_Current - ObjectResources->m_Gold_Current < 0)
	{
		return false;
	}
	else
	{
		PlayerResources->m_Gold_Current -= ObjectResources->m_Gold_Current;
		_Gold_UpdateDisplayText(PlayerResources, GoldDisplayText, renderer);
		return true;
	}
}

void ResourcesSystem::_Mana_Add(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* ManaDisplayText, SDL_Renderer* renderer)
{
	if (PlayerResources->m_Mana_Current + ObjectResources->m_Mana_Current <= PlayerResources->m_Mana_Max)
	{
		PlayerResources->m_Mana_Current += ObjectResources->m_Mana_Current;
	}
	else
	{
		PlayerResources->m_Mana_Current = PlayerResources->m_Mana_Max;
	}	
	_Mana_UpdateDisplayText(PlayerResources, ManaDisplayText, renderer);
}
bool ResourcesSystem::_Mana_Subtract(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* ManaDisplayText, SDL_Renderer* renderer)
{
	if (PlayerResources->m_Mana_Current - ObjectResources->m_Mana_Current < 0)
	{
		return false;
	}
	else
	{
		PlayerResources->m_Mana_Current -= ObjectResources->m_Mana_Current;
		_Mana_UpdateDisplayText(PlayerResources, ManaDisplayText, renderer);
		return true;
	}
}
void ResourcesSystem::_MaxMana_AddOrSubtract(ResourcesComponent* PlayerResources, int increasevalue, SDL_Renderer* renderer)
{
	PlayerResources->m_Mana_Max += increasevalue;
}

bool ResourcesSystem::_Gold_CheckForSufficientFunds(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources)
{
	if (PlayerResources->m_Gold_Current < ObjectResources->m_Gold_Current)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool ResourcesSystem::_Mana_CheckForSufficientFunds(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources)
{
	if (PlayerResources->m_Mana_Current < ObjectResources->m_Mana_Current)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ResourcesSystem::_Score_UpdateDisplayText(ResourcesComponent* PlayerResources, TextComponent* ScoreDisplayText, SDL_Renderer* renderer)
{
	int score = PlayerResources->m_Score;

	ScoreDisplayText->_SwitchTextTo(std::to_string(score).data(), ScoreDisplayText->m_FontPath.data(), ScoreDisplayText->m_TextHeight, ScoreDisplayText->m_Colour, ScoreDisplayText->m_Position, renderer);
}
void ResourcesSystem::_Gold_UpdateDisplayText(ResourcesComponent* PlayerResources, TextComponent* GoldDisplayText, SDL_Renderer* renderer)
{
	int gold = PlayerResources->m_Gold_Current;

	GoldDisplayText->_SwitchTextTo(std::to_string(gold).data(), GoldDisplayText->m_FontPath.data(), GoldDisplayText->m_TextHeight, GoldDisplayText->m_Colour, GoldDisplayText->m_Position, renderer);
}
void ResourcesSystem::_Mana_UpdateDisplayText(ResourcesComponent* PlayerResources, TextComponent* ManaDisplayText, SDL_Renderer* renderer)
{
	int mana = PlayerResources->m_Mana_Current;

	ManaDisplayText->_SwitchTextTo(std::to_string(mana).data(), ManaDisplayText->m_FontPath.data(), ManaDisplayText->m_TextHeight, ManaDisplayText->m_Colour, ManaDisplayText->m_Position, renderer);
}

void ResourcesSystem::_CheckAllButtonsForState(uint64_t m_Player)
{
	ResourcesComponent* PlayerResources = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), m_Manager_Components->m_Components_Resources);

	for (auto& Button : m_Manager_Components->m_Components_Button)
	{
		ResourcesComponent* ButtonResources = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(Button.Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), m_Manager_Components->m_Components_Resources);

		// FUNDS
		bool bHasSufficientFunds = true;
		if (ButtonResources->m_Gold_Current > 0)
		{
			if (ButtonResources->m_Gold_Current > PlayerResources->m_Gold_Current)
			{
				bHasSufficientFunds = false;
			}
		}
		else if (ButtonResources->m_Mana_Current > 0)
		{
			if (ButtonResources->m_Mana_Current > PlayerResources->m_Mana_Current)
			{
				bHasSufficientFunds = false;
			}
		}

		bool bIsOutOfPhase = true;
		// PHASE
		if (Button.m_ButtonType == user::UI_Button::BALLISTA || Button.m_ButtonType == user::UI_Button::SPIKE_TRAP || Button.m_ButtonType == user::UI_Button::TAR_TRAP || Button.m_ButtonType == user::UI_Button::WOODEN_BOX)
		{
			if (m_GameState->m_Phase == user::GamePhase::PREPARATION_PHASE)
			{
				bIsOutOfPhase = false;
			}
			else if (m_GameState->m_Phase == user::GamePhase::DEFENSE_PHASE)
			{
				bIsOutOfPhase = true;
			}
		}
		else if (Button.m_ButtonType == user::UI_Button::HEAL_SPELL || Button.m_ButtonType == user::UI_Button::FIREBALL_SPELL)
		{
			bIsOutOfPhase = false;
		}


		// STATE of the button
		if (bHasSufficientFunds == true && bIsOutOfPhase == true)
		{
			StateComponent* ButtonState = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(Button.Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
			m_System_State->_ChangeCurrentState(ButtonState, user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_DOWN);
		}
		else if (bHasSufficientFunds == true && bIsOutOfPhase == false)
		{
			StateComponent* ButtonState = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(Button.Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
			m_System_State->_ChangeCurrentState(ButtonState, user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_DOWN);
		}
		else if (bHasSufficientFunds == false && bIsOutOfPhase == true)
		{
			StateComponent* ButtonState = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(Button.Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
			m_System_State->_ChangeCurrentState(ButtonState, user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_DOWN);
		}
		else
		{
			StateComponent* ButtonState = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(Button.Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
			m_System_State->_ChangeCurrentState(ButtonState, user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_DOWN);
		}
	}
}
