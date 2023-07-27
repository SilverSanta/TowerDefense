#pragma once


#include "FiniteStateMachine.h"
#include "SDL.h"
#include "ECS_Framework.h"
#include "UserExtension.h"
#include "UserGameState.h"


// CONSTRUCTORS
FiniteStateMachine::FiniteStateMachine(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmananger, UserGameState* gamestate)
{
	m_Game = game;
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_Manager_Systems = systemsmananger;
	m_GameState = gamestate;

}
FiniteStateMachine::~FiniteStateMachine() {}


void FiniteStateMachine::_StateMachine(uint64_t entityid)
{
	// IS AI NEEDED IN THE GAME
	if (_CHECK_DoesTowerStillExist() == false) { return; }

	// SETUP
	Entity* AIControlledUnit_EntityPtr = m_Manager_Entities->_Get_EntityById(entityid);
	AIComponent* AIControlledUnit_AIPtr = m_Manager_Components->_Get_ComponentPtrFromId(AIControlledUnit_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::AI), m_Manager_Components->m_Components_AI);
	StateComponent* AIControlledUnit_StatePtr = m_Manager_Components->_Get_ComponentPtrFromId(AIControlledUnit_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), m_Manager_Components->m_Components_State);
	MovementComponent* AIControlledUnit_MovementPtr = m_Manager_Components->_Get_ComponentPtrFromId(AIControlledUnit_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::MOVEMENT), m_Manager_Components->m_Components_Movement);

	if (_CHECK_DoesTowerStillExist() == false) { AIControlledUnit_AIPtr->m_bAIIsNeededInGame = false; } 

	// (1) IS THERE A TARGET??
	bool bTargetInAttackRange = false;
	bool bTargetHasBeenReleased = false;
		

	if (AIControlledUnit_AIPtr->m_TargetEntityId != NULL && AIControlledUnit_MovementPtr->m_MovementPath.size() <= 1)
	{		
		// (1.1) IS THE TARGET VALID (NOT A NULLPTR)?
		if (m_Manager_Entities->_Get_EntityById(AIControlledUnit_AIPtr->m_TargetEntityId) != nullptr)
		{		
			// (1.1.1) IS THE TARGET IN ATTACK RANGE?
			if (_CHECK_TargetIsInTheAttackZone(AIControlledUnit_AIPtr))
			{				
				bool bReadyToAttack = false;

				TimeComponent* AIControlledUnit_AttackTimePtr = m_Manager_Components->_Get_ComponentPtrFromId(AIControlledUnit_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TIME), m_Manager_Components->m_Components_Time);

				if (AIControlledUnit_AttackTimePtr->m_Time_Current - AIControlledUnit_AttackTimePtr->m_Time_CountStart >= AIControlledUnit_AttackTimePtr->m_EffectDuration * 1000) { bReadyToAttack = true; }

				// THIS IS CRITICAL
				if (bReadyToAttack)
				{
					m_Manager_Systems->m_System_Action->_Action_Attack(AIControlledUnit_AIPtr->Get_OwnerId(), AIControlledUnit_AIPtr->m_TargetEntityId);

					AIControlledUnit_AttackTimePtr->m_Time_CountStart = AIControlledUnit_AttackTimePtr->m_Time_Current;
					AIControlledUnit_AIPtr->m_Time_LastDecisionStartTime = AIControlledUnit_AIPtr->m_Time_Current;
					return;
				}
				else
				{
					m_Manager_Systems->m_System_State->_ChangeCurrentState(AIControlledUnit_StatePtr, user::State::IDLE, user::SubState::IDLE_DEFAULT, AIControlledUnit_StatePtr->m_CurrentDirection);
					return;
				}
				//Manager_Systems->System_Action->Action_Attack(AIControlledUnit_AIPtr->Get_OwnerId(), AIControlledUnit_AIPtr->TargetEntityId);
				//AIControlledUnit_AIPtr->Time_LastDecisionStartTime = AIControlledUnit_AIPtr->Time_Current;
				//return;								
				// THIS IS CRITICAL
			}
		}
		// (1.2) SET TARGET TO NULL (RELEASE THE TARGET)
		else
		{				
			bTargetHasBeenReleased = true;			
			AIControlledUnit_AIPtr->m_TargetEntityId = NULL;
			AIControlledUnit_AIPtr->m_Time_LastDecisionStartTime = AIControlledUnit_AIPtr->m_Time_Current;			
		}
	}


	// (3) IS TOWER ALREADY A TARGET AT ALL?
	if (AIControlledUnit_AIPtr->m_TargetEntityId == m_GameState->m_PlayerTower)
	{		
		// (3.1) UPDATE PATH AND WALK
		return;
	}

	else if (AIControlledUnit_AIPtr->m_TargetEntityId == NULL)
	{
		
		//   (3.2) Can Tower be a target? (reachable) 
		uint64_t StartingNodeId;
		if (bTargetHasBeenReleased)
		{
			if ((int)AIControlledUnit_MovementPtr->m_MovementPath.size() == 0)
			{
				StartingNodeId = m_Manager_Systems->m_System_Pathfinding->_SelectClosestNodefromCoordinates(AIControlledUnit_AIPtr->m_TargetNodeCoordinates, +16);
				AIControlledUnit_MovementPtr->m_MovementPath.clear();
			}
			else
			{
				StartingNodeId = m_Manager_Systems->m_System_Pathfinding->_SelectClosestNodefromCoordinates(AIControlledUnit_MovementPtr->m_MovementPath.at(0), +16);
				AIControlledUnit_MovementPtr->m_MovementPath.clear();
			}
		}
		else
		{
			StartingNodeId = m_Manager_Systems->m_System_Pathfinding->_SelectClosestNodefromEntity(entityid, -16);
		}
		std::vector<std::pair<int, int>> Path;

		auto PathDistance = m_Manager_Systems->m_System_Pathfinding->_Calculate_Path(StartingNodeId, m_GameState->m_TowerNode, Path, false, true);

		if (PathDistance.first == true)
		{
			
			// (3.2.1) SET PATH AND WALK!!!	// (3.2.1) SET PATH AND WALK!!!		
			Entity* Node_EntityPtr = m_Manager_Entities->_Get_EntityById(m_GameState->m_TowerNode);
			TransformComponent* Node_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(Node_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

			AIControlledUnit_AIPtr->m_TargetEntityId = m_GameState->m_PlayerTower;
			AIControlledUnit_AIPtr->m_TargetNodeCoordinates = std::make_pair((int)Node_TransformPtr->m_X, (int)Node_TransformPtr->m_Y);
			m_Manager_Systems->m_System_Pathfinding->_Set_PathForUnitToTargetAndMove(entityid, StartingNodeId, m_GameState->m_TowerNode, Path);

			return;
		}
		else
		{
			// (3.2.2) N->Check ideal path, set WOODEN BOX AS TARGET, WALK AND RETURN!
			std::vector<std::pair<int, int>> ActualPath;
			std::pair<uint64_t, int> ActualPathToBox = m_Manager_Systems->m_System_Pathfinding->_Calculate_PathToBarricade(StartingNodeId, m_GameState->m_TowerNode, ActualPath, true);
			Entity* Box_EntityPtr = m_Manager_Entities->_Get_EntityById(ActualPathToBox.first);
			TransformComponent* Box_TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(Box_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);
			AIControlledUnit_AIPtr->m_TargetEntityId = ActualPathToBox.first;
			AIControlledUnit_AIPtr->m_TargetNodeCoordinates = std::make_pair((int)Box_TransformPtr->m_X, (int)Box_TransformPtr->m_Y);
			m_Manager_Systems->m_System_Pathfinding->_Set_PathForUnitToTargetAndMove(entityid, StartingNodeId, AIControlledUnit_AIPtr->m_TargetEntityId, ActualPath);
			return;
		}
	}
}
void FiniteStateMachine::_StateMachine_All()
{
	for (auto& AI : m_Manager_Components->m_Components_AI)
	{
		_StateMachine(AI.Get_OwnerId());
	}
}

bool FiniteStateMachine::_CHECK_DoesTowerStillExist()
{
	bool bLoopIsGoing = true;
	bool bStillExists = false;
	int counter = 0;

	while (counter < (int)m_Manager_Entities->m_Entities.size() && bLoopIsGoing)
	{
		if (m_Manager_Entities->m_Entities.at(counter).m_Id == m_GameState->m_PlayerTower)
		{
			bStillExists = true;
			bLoopIsGoing = false;
		}
		else
		{
			counter++;
		}
	}

	return bStillExists;
}
std::vector<CollisionComponent*> FiniteStateMachine::_CHECK_DetectPlayerUnits(uint64_t EnemyUnitId)
{
	Entity* AIControlledUnit_EntityPtr = m_Manager_Entities->_Get_EntityById(EnemyUnitId);
	CollisionComponent* AIControlledUnit_DetectionZonePtr = m_Manager_Components->_Get_ComponentPtrFromId(AIControlledUnit_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION2), m_Manager_Components->m_Components_Collision);

	std::vector<CollisionComponent*> TowerCollisions = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(AIControlledUnit_DetectionZonePtr, user::CollisionProfile::TOWER, user::CollisionProfile::STATIC_OBJECTS);
	std::vector<CollisionComponent*> PlayerUnitsCollisions = m_Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(AIControlledUnit_DetectionZonePtr, user::CollisionProfile::UNIT_PLAYER, user::CollisionProfile::STRUCTURE);

	for (auto& Collision : TowerCollisions)
	{
		PlayerUnitsCollisions.push_back(Collision);
	}

	return PlayerUnitsCollisions;
}
bool FiniteStateMachine::_CHECK_DetectedPlayerUnitsContainTarget(AIComponent* AI, std::vector<CollisionComponent*> DetectedPlayerUnits)
{
	bool bDetectedUnitIsTarget = false;
	bool bLoopIsNotDone = false;
	int counter = 0;

	while (counter < DetectedPlayerUnits.size() && bLoopIsNotDone)
	{
		if (DetectedPlayerUnits.at(counter)->Get_OwnerId() == AI->m_TargetEntityId)
		{
			bDetectedUnitIsTarget = true;
		}
		else
		{
			counter++;
		}
	}

	return bDetectedUnitIsTarget;
}
bool FiniteStateMachine::_CHECK_TargetIsInTheAttackZone(AIComponent* AI)
{
	Entity* AIControlledUnit_EntityPtr = m_Manager_Entities->_Get_EntityById(AI->Get_OwnerId());
	CollisionComponent* AIControlledUnit_AttackZonePtr = m_Manager_Components->_Get_ComponentPtrFromId(AIControlledUnit_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION3), m_Manager_Components->m_Components_Collision);

	if (AI->m_TargetEntityId != NULL)
	{
		Entity* Target_EntityPtr = m_Manager_Entities->_Get_EntityById(AI->m_TargetEntityId);
		if (AIControlledUnit_EntityPtr != nullptr)
		{
			CollisionComponent* Target_CollisionPtr = m_Manager_Components->_Get_ComponentPtrFromId(Target_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), m_Manager_Components->m_Components_Collision);

			bool bTargetIsInTheAttackZone = m_Manager_Systems->m_System_Collision->_CollisionCheck(AIControlledUnit_AttackZonePtr, Target_CollisionPtr);
			return bTargetIsInTheAttackZone;
		}
		else
		{
			// if target is a null ptr... well.., it does not exist, so change the target to NULL
			AI->m_TargetEntityId = NULL;
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool FiniteStateMachine::_CHECK_TargetIsAmongDetectedUnits(uint64_t TargetId, std::vector<CollisionComponent*> DetectedEntities)
{
	bool bIsAmongUnits = false;
	int counter = 0;
	bool bIsNotDone = true;
	while (counter < DetectedEntities.size() && bIsNotDone)
	{

		if (TargetId = DetectedEntities.at(counter)->Get_OwnerId())
		{
			bIsAmongUnits = true;
			bIsNotDone = false;
		}
		else
		{
			counter++;
		}
	}
	return bIsAmongUnits;
}
std::pair<uint64_t, std::vector<std::pair<int, int>>> FiniteStateMachine::_CHECK_AllPathsToPotentialTargets(uint64_t AIControlledId, std::vector<CollisionComponent*> PotentialTargets)
{
	std::vector<std::vector<std::pair<int, int>>> PotentialTargetPaths;
	std::vector<uint64_t> PotentialTargetIds;
	std::vector<std::pair<bool, int>> PotentialTargetDistances;

	uint64_t StartingNode = m_Manager_Systems->m_System_Pathfinding->_SelectClosestNodefromEntity(AIControlledId, -16);

	for (auto& Collider : PotentialTargets)
	{		
		uint64_t TargetNode = m_Manager_Systems->m_System_Pathfinding->_SelectClosestNodefromEntity(Collider->Get_OwnerId(), -16);

		uint64_t PotentialTargetId = Collider->Get_OwnerId();
		std::vector<std::pair<int, int>> PotentialPath;
		std::pair<bool, int> PotentialTargetDistance = m_Manager_Systems->m_System_Pathfinding->_Calculate_Path(StartingNode, TargetNode, PotentialPath, false, true);

		if (PotentialTargetDistance.first == true)
		{
			PotentialTargetPaths.push_back(PotentialPath);
			PotentialTargetIds.push_back(PotentialTargetId);
			PotentialTargetDistances.push_back(PotentialTargetDistance);
		}
	}

	if (PotentialTargetPaths.size() == 0)
	{
		return std::make_pair(NULL, std::vector<std::pair<int, int>>());
	}
	else
	{
		int counter = 0;
		auto TargetDistance = PotentialTargetDistances.at(counter);

		for (int i = 0; i < PotentialTargetDistances.size();i++)
		{
			if (TargetDistance.second > PotentialTargetDistances.at(i).second)
			{
				TargetDistance = PotentialTargetDistances.at(i);
				counter = i;
			}			
		}

		std::pair<uint64_t, std::vector<std::pair<int, int>>> ReturnedValue = std::make_pair(PotentialTargetIds.at(counter), PotentialTargetPaths.at(counter));

		return ReturnedValue;
	}
}
