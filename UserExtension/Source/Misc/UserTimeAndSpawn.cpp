#pragma once


#include "UserTimeAndSpawn.h"
#include "SDL.h"
#include "ECS_Framework.h"
#include "UserExtension.h"
#include "UserGameState.h"
#include "UserBlueprints.h"

// ENEMY DATA MAPPER
std::unordered_map<char, user::EnemyType> EnemyDataMapper{

	std::make_pair('G', user::EnemyType::GOBLIN_WARRIOR),
	std::make_pair('S', user::EnemyType::SKELETON_WARRIOR),
	std::make_pair('O', user::EnemyType::ORC_WARRIOR),
	std::make_pair('M', user::EnemyType::MUMMY),
	std::make_pair('B', user::EnemyType::OGRE),
	std::make_pair('D', user::EnemyType::DRAGON)
};


// CONSTRUCTORS
UserTimeAndSpawn::UserTimeAndSpawn(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmananger, UserGameState* gamestate, UserBlueprints* blueprints)
{
	m_Game = game;
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_Manager_Systems = systemsmananger;
	m_GameState = gamestate;
	m_Blueprints = blueprints;
}
UserTimeAndSpawn::~UserTimeAndSpawn() {}


// TIMERS AND SPAWNING
void UserTimeAndSpawn::_CountDown()
{
	std::vector<uint64_t> deleteafterloop;

	for (auto& TimerId : m_MapOfTimers)
	{
		Entity* TimerEntityPtr = m_Manager_Entities->_Get_EntityById(TimerId.first);
		TimeComponent* Timer_TimeComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(TimerEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TIME), m_Manager_Components->m_Components_Time);

		if (Timer_TimeComponentPtr->m_bIsDestroyedWhenDurationEnds)
		{
			Timer_TimeComponentPtr->m_DurationLeft = Timer_TimeComponentPtr->m_EffectDuration - (Timer_TimeComponentPtr->m_Time_Current - Timer_TimeComponentPtr->m_Time_CountStart) / 1000;
		}

		if (TimerEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TIME) != NULL)
		{
			TextComponent* Timer_TextComponentPtr = m_Manager_Components->_Get_ComponentPtrFromId(TimerEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), m_Manager_Components->m_Components_Text);

			int CountText = (Timer_TimeComponentPtr->m_DurationLeft - (int)Timer_TimeComponentPtr->m_DurationLeft > 0) ? ((int)Timer_TimeComponentPtr->m_DurationLeft + 1) : ((int)Timer_TimeComponentPtr->m_DurationLeft);
			
			std::string ActualText;

			if (Timer_TimeComponentPtr->m_EffectDuration - Timer_TimeComponentPtr->m_DurationLeft <= 5)
			{
				ActualText = "Prepare your defenses!";
				Timer_TextComponentPtr->_SwitchTextTo(ActualText.data(), Timer_TextComponentPtr->m_FontPath.data(), Timer_TextComponentPtr->m_TextHeight, Timer_TextComponentPtr->m_Colour, Timer_TextComponentPtr->m_Position, m_Game->_Get_Renderer());

			}
			else if (CountText >= 3)
			{
				ActualText = std::to_string(CountText) + "..";
				Timer_TextComponentPtr->_SwitchTextTo(ActualText.data(), Timer_TextComponentPtr->m_FontPath.data(), Timer_TextComponentPtr->m_TextHeight, Timer_TextComponentPtr->m_Colour, Timer_TextComponentPtr->m_Position, m_Game->_Get_Renderer());
			}
			else
			{
				ActualText = "Your Tower is under siege!";
				Timer_TextComponentPtr->_SwitchTextTo(ActualText.data(), Timer_TextComponentPtr->m_FontPath.data(), Timer_TextComponentPtr->m_TextHeight, Timer_TextComponentPtr->m_Colour, Timer_TextComponentPtr->m_Position, m_Game->_Get_Renderer());
			}
		}

		if (Timer_TimeComponentPtr->m_DurationLeft <= 0.f)
		{
			if (Timer_TimeComponentPtr->m_TypeOfTimer == user::TimerType::TIMER_STARTING || Timer_TimeComponentPtr->m_TypeOfTimer == user::TimerType::TIMER_INTERVAL_BETWEEN_WAVES)
			{
				if (m_GameState->m_CurrentWave < m_GameState->m_EnemyData.size() - 1)
				{
					if(Timer_TimeComponentPtr->m_TypeOfTimer == user::TimerType::TIMER_INTERVAL_BETWEEN_WAVES)
					{
						m_GameState->m_CurrentWave++;
					}
					m_GameState->m_CurrentEnemyUnit = 0;
					m_bCurrentWaveExhausted = false;
					m_GameState->_Set_GamePhaseTo(user::GamePhase::DEFENSE_PHASE);
					
					bool Exit = (m_GameState->m_Mode == user::GameMode::PLACEMENT_MODE)?(true):(false);
					m_GameState->_EXIT_PLACEMENT_MODE(Exit);
				}
			}

			if (m_bCurrentWaveExhausted == false)
			{
				_Event_SpawnUnit();

				if (m_bCurrentWaveExhausted == false)
				{
					_Create_IntervalBetweenEnemiesCountdown();
				}
			}
			else
			{
				std::cout << "WAVE FINISHED\n";
			}
			m_GameState->m_EntitiesToBeDeleted.push_back(TimerId.first);
			deleteafterloop.push_back(TimerId.first);
		}






	}

	for (auto& id : deleteafterloop)
	{
		m_MapOfTimers.erase(id);
	}
}
void UserTimeAndSpawn::_Create_IntervalBetweenEnemiesCountdown()
{
	uint64_t StartingCountdown = m_Blueprints->_Create_TimerOnScreen((float)m_GameState->m_GargabeTransform.first, (float)m_GameState->m_GargabeTransform.second, m_GameState->m_IntervalBetweenSpawns, m_TextHeight, m_Game->_Get_CurrentTickInGame(), user::TimerType::TIMER_INTERVAL_BETWEEN_UNITS);

	m_MapOfTimers.insert(std::make_pair(StartingCountdown, StartingCountdown));
}
void UserTimeAndSpawn::_Create_IntervalBetweenWavesCountdown()
{
	uint64_t IntervalBetweenWavesCountdown = m_Blueprints->_Create_TimerOnScreen((float)m_Game->_Get_WindowDimensions().first / 2, (float)m_Y_Value, m_GameState->m_IntervalBetweenWaves, m_TextHeight, m_Game->_Get_CurrentTickInGame(), user::TimerType::TIMER_INTERVAL_BETWEEN_WAVES);

	m_MapOfTimers.insert(std::make_pair(IntervalBetweenWavesCountdown, IntervalBetweenWavesCountdown));
}

void UserTimeAndSpawn::_Event_SpawnUnit()
{	

	// Getting Enemy data (for convenience purposes)
	int WaveIndex = m_GameState->m_CurrentWave;
	int EnemyIndex = m_GameState->m_CurrentEnemyUnit;

	// Spawning Enemy at very portal location
	for (auto& Portal : m_GameState->m_Portals)
	{
		Entity* PortalPtr = m_Manager_Entities->_Get_EntityById(Portal);
		TransformComponent* Portal_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(PortalPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		auto EnemyKey = m_GameState->m_EnemyData[WaveIndex][EnemyIndex];
		user::EnemyType m_TypeOfEnemy = EnemyDataMapper.at(EnemyKey);

		m_Blueprints->_Create_EnemyUnit(Portal_TransformPtr->m_X + 32, Portal_TransformPtr->m_Y + 5, m_TypeOfEnemy, m_Game->_Get_CurrentTickInGame());
	
		
	}

	EnemyIndex++;
	m_GameState->m_CurrentEnemyUnit++;

	if (EnemyIndex == m_GameState->m_EnemyData.at(WaveIndex).size())
	{
		m_bCurrentWaveExhausted = true;

		if (WaveIndex == m_GameState->m_EnemyData.size() - 1)
		{
			m_bEnemyDataExhausted = true;
		}
	}
}
void UserTimeAndSpawn::_Event_StartingCountdown()
{
	uint64_t StartingCountdown = m_Blueprints->_Create_TimerOnScreen((float)m_Game->_Get_WindowDimensions().first / 2, (float)m_Y_Value, m_GameState->m_TimeBeforeStart, m_TextHeight, m_Game->_Get_CurrentTickInGame(), user::TimerType::TIMER_STARTING);

	m_MapOfTimers.insert(std::make_pair(StartingCountdown, StartingCountdown));
}