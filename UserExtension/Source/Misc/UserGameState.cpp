#pragma once

#include <algorithm>

#include "UserGameState.h"
#include "UserExtension.h"
#include "ECS_Framework.h"
#include "ImportDataSystem.h"
#include "SDL.h"
#include "UserMenuState.h"
#include "UserTimeAndSpawn.h"
#include "UserBlueprints.h"



std::unordered_map<user::UI_Button, user::PlacementMode> UIButtonMapper{

	std::make_pair(user::UI_Button::BALLISTA, user::PlacementMode::PLACEMENT_BALLISTA),
	std::make_pair(user::UI_Button::WOODEN_BOX, user::PlacementMode::PLACEMENT_WOODENBOX),
	std::make_pair(user::UI_Button::SPIKE_TRAP, user::PlacementMode::PLACEMENT_SPIKETRAP),
	std::make_pair(user::UI_Button::TAR_TRAP, user::PlacementMode::PLACEMENT_TARTRAP),
	std::make_pair(user::UI_Button::HEAL_SPELL, user::PlacementMode::PLACEMENT_HEALSPELL),
	std::make_pair(user::UI_Button::FIREBALL_SPELL, user::PlacementMode::PLACEMENT_FIREBALLSPELL),
};

UserGameState::UserGameState(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmananger, UserMenuState* menustate, UserBlueprints* userblueprints)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_Manager_Systems = systemsmananger;
	m_Game = game;
	m_MenuState = menustate;
	m_Blueprints = userblueprints;

	m_CurrentLevel = 1;
	m_LevelMotif = user::Motif::VALLEY;
	m_Mode = user::GameMode::NORMAL_MODE;
	m_Placement = user::PlacementMode::NONE;
	m_bPlacementIsApproved = false;

}
UserGameState::~UserGameState() {}

void UserGameState::_Set_UI_StripDimensions(std::pair<int, int> horizontalstripheights, std::pair<int, int> verticalstripwidths)
{
	m_UI_HorizontalStripHeights = horizontalstripheights;
	m_UI_VerticalStripWidths = verticalstripwidths;
}
void UserGameState::_Update_KillCounter(SDL_Renderer* renderer)
{
	Entity* UI_KillCounter_Ptr = m_Manager_Entities->_Get_EntityById(m_UI_KillCounter);
	TextComponent* UI_KillCounter_TextPtr = m_Manager_Components->_Get_ComponentPtrFromId(UI_KillCounter_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), m_Manager_Components->m_Components_Text);

	std::string newstring = std::to_string(m_EnemiesKilled) + " / " + std::to_string(m_Enemies_Total);

	UI_KillCounter_TextPtr->_SwitchTextTo(newstring.data(), UI_KillCounter_TextPtr->m_FontPath.data(), UI_KillCounter_TextPtr->m_TextHeight, UI_KillCounter_TextPtr->m_Colour, UI_KillCounter_TextPtr->m_Position, renderer);

}
void UserGameState::_Set_TimeAndSpawnPointer(UserTimeAndSpawn* timeandspawn)
{
	TimeAndSpawn = timeandspawn;
}
void UserGameState::_Set_PlayableScreen(std::pair<int, int> WindowDimensions, std::pair<int, int> uihorizontalstripheights, std::pair<int, int> uiverticalstripwidths)
{
	_Set_UI_StripDimensions(uihorizontalstripheights, uiverticalstripwidths);

	m_PlayableScreen_XAxis = std::make_pair(uiverticalstripwidths.first, WindowDimensions.first - uiverticalstripwidths.second);
	m_PlayableScreen_YAxis = std::make_pair(uihorizontalstripheights.first, WindowDimensions.second - uihorizontalstripheights.second);
}
void UserGameState::_Set_InitialGoldAndMana(int initialgold, int initialmana)
{
	m_InitialGold = initialgold;
	m_InitialMana = initialmana;
}

void UserGameState::_Set_GamePhaseTo(user::GamePhase gamephase)
{
	if (gamephase == user::GamePhase::DEFENSE_PHASE)
	{
		m_Phase = gamephase;
		//std::cout << "GAME PHASE SET TO < DEFENSE >\n";
	}
	else if (gamephase == user::GamePhase::PREPARATION_PHASE)
	{
		m_Phase = gamephase;
		//std::cout << "GAME PHASE SET TO < PREPARATION >\n";
	}	
}
bool UserGameState::_IsWithinScreen(float x, float y)
{
	if (x < m_PlayableScreen_XAxis.first ||
		x > m_PlayableScreen_XAxis.second ||
		y < m_PlayableScreen_YAxis.first ||
		y > m_PlayableScreen_YAxis.second)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void UserGameState::_Placement_SetAllToGarbageTransform()
{
	TransformComponent* PlacementBallista_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_Ballista)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	TransformComponent* PlacementWoodenBox_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_WoodenBox)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	TransformComponent* PlacementTarTrap_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_TarTrap)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	TransformComponent* PlacementSpikeTrap_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_SpikeTrap)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	TransformComponent* PlacementHealSpell_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_HealSpell)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	TransformComponent* PlacementFireballSpell_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_FireballSpell)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
	CollisionComponent* PlacementFireballSpell_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Placement_FireballSpell)->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);



	PlacementBallista_TransformPtr->m_X = (float)m_GargabeTransform.first; PlacementBallista_TransformPtr->m_Y = (float)m_GargabeTransform.second;
	PlacementWoodenBox_TransformPtr->m_X = (float)m_GargabeTransform.first; PlacementWoodenBox_TransformPtr->m_Y = (float)m_GargabeTransform.second;
	PlacementTarTrap_TransformPtr->m_X = (float)m_GargabeTransform.first; PlacementTarTrap_TransformPtr->m_Y = (float)m_GargabeTransform.second;
	PlacementSpikeTrap_TransformPtr->m_X = (float)m_GargabeTransform.first; PlacementSpikeTrap_TransformPtr->m_Y = (float)m_GargabeTransform.second;
	PlacementHealSpell_TransformPtr->m_X = (float)m_GargabeTransform.first; PlacementHealSpell_TransformPtr->m_Y = (float)m_GargabeTransform.second;
	PlacementFireballSpell_TransformPtr->m_X = (float)m_GargabeTransform.first; PlacementFireballSpell_TransformPtr->m_Y = (float)m_GargabeTransform.second;	
}
void UserGameState::_Placement_SetAllNodesSubstate(std::vector<uint64_t>& m_Nodes, user::SubState substate)
{
	for (auto& NodeId : m_Nodes)
	{
		Entity* NodePtr = m_Manager_Entities->_Get_EntityById(NodeId);
		StateComponent* Node_StatePtr = m_Manager_Components->_Get_ComponentPtrFromId(NodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);		
		m_Manager_Systems->m_System_State->_ChangeCurrentState(Node_StatePtr, user::State::IDLE, substate, user::Direction::Facing_RIGHT);
	}
}
void UserGameState::_Check_Traps_All()
{
	// Spring Trap Logic (SPIKE TRAP)
	for (auto& TrapComp : m_Manager_Components->m_Components_Trap)
	{
		if(TrapComp.m_Trap == user::TrapType::SPIKE_TRAP)
		{
			Entity* TrapEntityPtr = m_Manager_Entities->_Get_EntityById(TrapComp.Get_OwnerId());
			CollisionComponent* TrapNode_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(TrapEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);
			TimeComponent* Trap_TimePtr = m_Manager_Components->_Get_ComponentPtrFromId(TrapEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TIME), m_Manager_Components->m_Components_Time);

			// Activating the trap if cooled down
			if (TrapComp.m_bActivated == false)
			{
				if (Trap_TimePtr->m_Time_Current - Trap_TimePtr->m_Time_CountStart >= Trap_TimePtr->m_EffectDuration * 1000)
				{
					TrapComp.m_bActivated = true;
				}
			}

			// If Active -> call the trap
			if (TrapComp.m_bActivated)
			{
				bool bHitsSomething = m_Manager_Systems->m_System_Collision->_CollisionCheck_AllFromLayerToLayer(TrapNode_CollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::UNIT_PLAYER);

				if (bHitsSomething)
				{
					TrapComp.m_bActivated = false;
					TimeComponent* Trap_TimePtr = m_Manager_Components->_Get_ComponentPtrFromId(TrapEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TIME), m_Manager_Components->m_Components_Time);
					Trap_TimePtr->m_Time_CountStart = Trap_TimePtr->m_Time_Current;

					std::vector<CollisionComponent*> ListOfHitEnemies = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(TrapNode_CollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::UNIT_PLAYER);

					for (auto& m_CollisionBox : ListOfHitEnemies)
					{
						Entity* HitEnemyPtr = m_Manager_Entities->_Get_EntityById(m_CollisionBox->Get_OwnerId());

						if (TrapComp.m_Trap == user::TrapType::SPIKE_TRAP)
						{
							AttackComponent* Trap_AttackPtr = m_Manager_Components->_Get_ComponentPtrFromId(TrapEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::ATTACK), m_Manager_Components->m_Components_Attack);
							m_Manager_Systems->m_System_Action->_Action_SpringTrap(TrapComp.Get_OwnerId());
							m_Manager_Systems->m_System_HealthAndAttack->_ApplyDamage(HitEnemyPtr, (int)Trap_AttackPtr->m_MeleeDmg, m_EntitiesToBeDeleted, this, m_Game->_Get_Renderer());
						}
					}
				}
			}
		}
	}

	// Const Trap Logic (TAR TRAP)
	for (auto& EnemyComp : m_Manager_Components->m_Components_Enemy)
	{
		bool bAffectedByTar = false;

		Entity* Enemy_EntityPtr = m_Manager_Entities->_Get_EntityById(EnemyComp.Get_OwnerId());
		CollisionComponent* Enemy_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(Enemy_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);
		MovementComponent* Enemy_MovementPtr = m_Manager_Components->_Get_ComponentPtrFromId(Enemy_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::MOVEMENT), m_Manager_Components->m_Components_Movement);

		bool bNotDone = true;
		int i = 0;
		float SpeedFactor = 1.0;
		while (i < m_Manager_Components->m_Components_Trap.size() && bNotDone)
		{			
			TrapComponent* TrapCompPtr = &m_Manager_Components->m_Components_Trap.at(i);
			if(TrapCompPtr->m_Trap == user::TrapType::TAR_TRAP)
			{
	
				Entity* Trap_EntityPtr = m_Manager_Entities->_Get_EntityById(TrapCompPtr->Get_OwnerId());
				CollisionComponent* Trap_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(Trap_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);

				if (m_Manager_Systems->m_System_Collision->_CollisionCheck(Enemy_CollisionPtr, Trap_CollisionPtr) == true)
				{					
					bAffectedByTar = true;
					bNotDone = false;
					SpeedFactor = TrapCompPtr->m_TrapSlow;
				}
			}

			i++;
		}

		Enemy_MovementPtr->m_SpeedFactor = SpeedFactor;		
	}
}
void UserGameState::_Check_SpellEffects()
{
	for (auto& Timer : m_Manager_Components->m_Components_Time)
	{
		if (Timer.m_bIsDestroyedWhenDurationEnds == true && Timer.m_TypeOfTimer == user::TimerType::TIMER_SPELL_EFFECT)
		{
			Timer.m_DurationLeft = (Timer.m_EffectDuration * 1000 - (Timer.m_Time_Current - Timer.m_Time_CountStart)) / 1000.f;

			if (Timer.m_DurationLeft <= 0.f)
			{
				m_EntitiesToBeDeleted.push_back(Timer.Get_OwnerId());
			}
		}
	}
}
void UserGameState::_Check_SpecialEffects()
{
	for (auto& Timer : m_Manager_Components->m_Components_Time)
	{
		if (Timer.m_bIsDestroyedWhenDurationEnds == true && Timer.m_TypeOfTimer == user::TimerType::TIMER_SPECIAL_EFFECT)
		{
			Timer.m_DurationLeft = (Timer.m_EffectDuration * 1000 - (Timer.m_Time_Current - Timer.m_Time_CountStart))/1000.f;

			if (Timer.m_DurationLeft <= 0.f)
			{
				m_EntitiesToBeDeleted.push_back(Timer.Get_OwnerId());
			}
		}
	}
}
void UserGameState::_Check_Arrows()
{
	for (auto& Timer : m_Manager_Components->m_Components_Time)
	{
		if (Timer.m_bIsDestroyedWhenDurationEnds == true && Timer.m_TypeOfTimer == user::TimerType::TIMER_ARROW_VANISHING)
		{
			Timer.m_DurationLeft = Timer.m_EffectDuration - (Timer.m_Time_Current - Timer.m_Time_CountStart) / 1000;
			
			if (Timer.m_DurationLeft <= 0.f)
			{
				m_EntitiesToBeDeleted.push_back(Timer.Get_OwnerId());
			}
		}
	}

	for (auto& Arrow : m_Manager_Components->m_Components_Projectile)
	{
		Entity* Arrow_EntityPtr = m_Manager_Entities->_Get_EntityById(Arrow.Get_OwnerId());
		ProjectileComponent* Arrow_ProjectilePtr = m_Manager_Components->_Get_ComponentPtrFromId(Arrow_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::PROJECTILE), m_Manager_Components->m_Components_Projectile);

		CollisionComponent* Arrow_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(Arrow_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);

		std::vector<CollisionComponent*> ListOfHitEnemies = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(Arrow_CollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::UNIT_PLAYER);


		if (ListOfHitEnemies.size() > 0)
		{				
			Entity* HitEnemy_EntityPtr = m_Manager_Entities->_Get_EntityById(ListOfHitEnemies.at(0)->Get_OwnerId());
			m_Manager_Systems->m_System_HealthAndAttack->_ApplyDamage(HitEnemy_EntityPtr, Arrow_ProjectilePtr->m_Damage, m_EntitiesToBeDeleted, this, m_Game->_Get_Renderer());
			
			float Hit_X = (float)(ListOfHitEnemies.at(0)->m_CollisionBox.x + ListOfHitEnemies.at(0)->m_CollisionBox.w / 2);
			float Hit_Y = (float)(ListOfHitEnemies.at(0)->m_CollisionBox.y + ListOfHitEnemies.at(0)->m_CollisionBox.h / 2);

			m_Blueprints->_Create_HitEffect(Hit_X, Hit_Y, m_Game->_Get_CurrentTickInGame());

			m_EntitiesToBeDeleted.push_back(Arrow_EntityPtr->_Get_EntityId());
		}
	}
}
void UserGameState::_Check_Ballistas_All()
{
	for (auto& BallistaComp : m_Manager_Components->m_Components_Ballista)
	{
		Entity* BallistaEntityPtr = m_Manager_Entities->_Get_EntityById(BallistaComp.Get_OwnerId());
		CollisionComponent* Ballista_DetectionCollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(BallistaEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION2), m_Manager_Components->m_Components_Collision);
		TransformComponent* Ballista_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(BallistaEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		TimeComponent* Ballista_TimePtr = m_Manager_Components->_Get_ComponentPtrFromId(BallistaEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TIME), m_Manager_Components->m_Components_Time);

		// Activating the trap if cooled down
		if (BallistaComp.m_bActivated == false)
		{
			if (Ballista_TimePtr->m_Time_Current - Ballista_TimePtr->m_Time_CountStart >= Ballista_TimePtr->m_EffectDuration * 1000)
			{
				BallistaComp.m_bActivated = true;
			}
		}

		// If Active -> call the ballista
		if (BallistaComp.m_bActivated)
		{
			bool bDetectsSomething = m_Manager_Systems->m_System_Collision->_CollisionCheck_AllFromLayerToLayer(Ballista_DetectionCollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::UNIT_PLAYER);

			if (bDetectsSomething)
			{
				AnimatedSpriteComponent* Ballista_SpritePtr = m_Manager_Components->_Get_ComponentPtrFromId(BallistaEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE1), m_Manager_Components->m_Components_AnimatedSprite);

				BallistaComp.m_bActivated = false;
				Ballista_TimePtr->m_Time_CountStart = Ballista_TimePtr->m_Time_Current;

				std::vector<CollisionComponent*> ListOfDetectedEnemies = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(Ballista_DetectionCollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::UNIT_PLAYER);

				int counter = 0;
				Entity* ClosestEnemyPtr = m_Manager_Entities->_Get_EntityById(ListOfDetectedEnemies.at(0)->Get_OwnerId());
				TransformComponent* ClosestEnemy_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(ClosestEnemyPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

				double ClosestDistanceSquared = std::pow((ClosestEnemy_TransformPtr->m_X - Ballista_TransformPtr->m_X), 2) + std::pow((ClosestEnemy_TransformPtr->m_Y - Ballista_TransformPtr->m_Y), 2);

				for (int i = 0; i < ListOfDetectedEnemies.size(); i++)
				{
					Entity* DetectedEnemyPtr = m_Manager_Entities->_Get_EntityById(ListOfDetectedEnemies.at(i)->Get_OwnerId());
					TransformComponent* DetectedEnemy_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(DetectedEnemyPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

					double DistanceSquared = std::pow((DetectedEnemy_TransformPtr->m_X - Ballista_TransformPtr->m_X), 2) + std::pow((DetectedEnemy_TransformPtr->m_Y - Ballista_TransformPtr->m_Y), 2);

					if (DistanceSquared < ClosestDistanceSquared)
					{
						ClosestEnemyPtr = DetectedEnemyPtr;
						ClosestDistanceSquared = DistanceSquared;
						ClosestEnemy_TransformPtr = DetectedEnemy_TransformPtr;
						counter = i;
					}
				}

				mfk::NormalVector2D NewVector;
				NewVector.NormalBetweenTwoPoints(Ballista_TransformPtr->m_X, Ballista_TransformPtr->m_Y - 16, ClosestEnemy_TransformPtr->m_X, ClosestEnemy_TransformPtr->m_Y);

				m_Manager_Systems->m_System_Movement->_Set_Angle(Ballista_TransformPtr, Ballista_SpritePtr, NewVector);
				m_Manager_Systems->m_System_Action->_Action_Shoot(BallistaEntityPtr->_Get_EntityId());
			}
		}		
	}
}
void UserGameState::_Delete_DeadEntities(SDL_Renderer* renderer, std::pair<uint16_t, uint16_t> Resolution)
{
	bool bHasAnyBarricadeBeenKilled = false;
	bool bHasAnyUnitBeenKilled = false;

	for (auto& id : m_EntitiesToBeDeleted)
	{
		Entity* EntityToBeDeleted = m_Manager_Entities->_Get_EntityById(id);

		// CHECK FOR BARRICADES
		if (EntityToBeDeleted->_Get_ComponentIdFromEntityByType(user::ComponentType::BARRICADE) != NULL)
		{
			bHasAnyBarricadeBeenKilled = true;

			uint64_t DamagedObject_BarricadeID = EntityToBeDeleted->_Get_ComponentIdFromEntityByType(user::ComponentType::BARRICADE);
			BarricadeComponent* DamagedObject_BarricadePtr = m_Manager_Components->_Get_ComponentPtrFromId(DamagedObject_BarricadeID, m_Manager_Components->m_Components_Barricade);

			for (auto& node : m_Manager_Components->m_Components_Node)
			{
				if (node.m_Id == DamagedObject_BarricadePtr->m_NodeComponentId)
				{
					node.m_bIsPassableByUnits = true;
				}
			}

			// UPDATE PATHFINGING
			// UPDATE AI TARGET?
		}

		// CHECK FOR RESOURCES FROM ENEMIES
		if (EntityToBeDeleted->_Get_ComponentIdFromEntityByType(user::ComponentType::ENEMY) != NULL)
		{
			bHasAnyUnitBeenKilled = true;		
			m_EnemiesKilled++;
			_Update_KillCounter(renderer);

			uint64_t DamagedObject_ObjectResourcesID = EntityToBeDeleted->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES);
			ResourcesComponent* DamagedObject_ObjectResourcesPtr = m_Manager_Components->_Get_ComponentPtrFromId(DamagedObject_ObjectResourcesID, m_Manager_Components->m_Components_Resources);

			uint64_t Player_ResourcesID = m_Manager_Entities->_Get_EntityById(m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES);
			ResourcesComponent* Player_ResourcesPtr = m_Manager_Components->_Get_ComponentPtrFromId(Player_ResourcesID, m_Manager_Components->m_Components_Resources);

			uint64_t Player_GoldTextID = m_Manager_Entities->_Get_EntityById(m_UI_GoldText)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT);
			TextComponent* Player_GoldTextPtr = m_Manager_Components->_Get_ComponentPtrFromId(Player_GoldTextID, m_Manager_Components->m_Components_Text);

			uint64_t Player_ManaTextID = m_Manager_Entities->_Get_EntityById(m_UI_ManaText)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT);
			TextComponent* Player_ManaTextPtr = m_Manager_Components->_Get_ComponentPtrFromId(Player_ManaTextID, m_Manager_Components->m_Components_Text);

			uint64_t Player_ScoreTextID = m_Manager_Entities->_Get_EntityById(m_UI_ScoreText)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT);
			TextComponent* Player_ScoreTextPtr = m_Manager_Components->_Get_ComponentPtrFromId(Player_ScoreTextID, m_Manager_Components->m_Components_Text);

			m_Manager_Systems->m_System_Resources->_Gold_Add(Player_ResourcesPtr, DamagedObject_ObjectResourcesPtr, Player_GoldTextPtr, renderer);
			m_Manager_Systems->m_System_Resources->_Mana_Add(Player_ResourcesPtr, DamagedObject_ObjectResourcesPtr, Player_ManaTextPtr, renderer);
			m_Manager_Systems->m_System_Resources->_Score_AddOrSubtract(Player_ResourcesPtr, DamagedObject_ObjectResourcesPtr, Player_ScoreTextPtr, renderer);


			



			// CHECKING WIN CONDITION
			if (m_EnemiesKilled >= m_Enemies_Total)
			{
				m_bGameHasBeenWon = true;
				m_Score_AfterEndGame = Player_ResourcesPtr->m_Score;
				_RETURN_TO_MENU();
				m_MenuState->_Set_MenuLayout_EndGameMenu(Resolution);
			}
		}

		// CHECK FOR TOWER -> ENDGAME CONDITION
		if (id == m_PlayerTower)
		{
			uint64_t Player_ResourcesID = m_Manager_Entities->_Get_EntityById(m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES);
			ResourcesComponent* Player_ResourcesPtr = m_Manager_Components->_Get_ComponentPtrFromId(Player_ResourcesID, m_Manager_Components->m_Components_Resources);

			m_bGameHasBeenLost = true;
			m_Score_AfterEndGame = Player_ResourcesPtr->m_Score;
			_RETURN_TO_MENU();
			m_MenuState->_Set_MenuLayout_EndGameMenu(Resolution);
		}
		m_Manager_Components->_DeleteComponents(m_Manager_Entities->_DeleteEntity(id));
	}

	// CHECK FOR WAVE COUNTDOWN START
	if(bHasAnyUnitBeenKilled)
	{
		if (m_EnemiesKilled == m_WaveThreshholds.at(m_CurrentWave) && m_CurrentWave != m_EnemyData.size() - 1)
		{
			TimeAndSpawn->_Create_IntervalBetweenWavesCountdown();
			_Set_GamePhaseTo(user::GamePhase::PREPARATION_PHASE);
		}
	}

	// UPDATE PATHFINDING
	if (bHasAnyBarricadeBeenKilled == true)
	{
		// WIP WIP WIP
	}

	m_EntitiesToBeDeleted = std::vector<uint64_t>();
}

void UserGameState::_RETURN_TO_MENU()
{
	TransformComponent* Camera_InGame_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	m_Game->_Set_InMenu(true);
	m_Game->m_CameraTransform_SavedInGame = std::make_pair(Camera_InGame_TransformPtr->m_X, Camera_InGame_TransformPtr->m_Y);

	for (auto& Sprite : m_Manager_Components->m_Components_AnimatedSprite)
	{
		m_Manager_Systems->m_System_Animation->_SetTextureTransparency(m_Game->_Get_Renderer(), &Sprite, true);
	}

	m_MenuState->_Set_MenuLayout_DuringGameMenu(m_Game->_Get_WindowDimensions());
}
void UserGameState::_ENTER_PLACEMENT_MODE(user::UI_Button buttontype)
{

	m_Mode = user::GameMode::PLACEMENT_MODE;
	m_Placement = UIButtonMapper.at(buttontype);

	Entity* CancelButtonPtr = m_Manager_Entities->_Get_EntityById(m_UI_Button_Cancel);
	TransformComponent* CancelButton_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(CancelButtonPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	CancelButton_TransformPtr->m_X += (float)m_GargabeTransform.first;
}
void UserGameState::_EXIT_PLACEMENT_MODE(bool& bExitPlacementMode)
{
	if (m_Game->_InMenu() == false && bExitPlacementMode)
	{
		_Placement_SetAllNodesSubstate(m_Nodes, user::SubState::IDLE_NODE_INVISIBLE);
		m_Mode = user::GameMode::NORMAL_MODE;

		Entity* CancelButtonPtr = m_Manager_Entities->_Get_EntityById(m_UI_Button_Cancel);
		TransformComponent* CancelButton_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(CancelButtonPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

		CancelButton_TransformPtr->m_X -= (float)m_GargabeTransform.first;
	}
}
