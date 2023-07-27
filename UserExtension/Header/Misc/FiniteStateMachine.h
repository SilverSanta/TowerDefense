#pragma once

#include <iostream>
#include <vector>

class MyFramework;
class ComponentsManager;
class EntitiesManager;
class SystemsManager;
class UserGameState;
class UserBlueprints;
struct SDL_Renderer;
class CollisionComponent;
class AIComponent;

// USER TIME AND SPAWN
class FiniteStateMachine
{
public:
	FiniteStateMachine(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmananger, UserGameState* gamestate);
	~FiniteStateMachine();

public:	
	void _StateMachine_All();

private:
	void _StateMachine(uint64_t entityid);
	bool _CHECK_DoesTowerStillExist();
	bool _CHECK_DetectedPlayerUnitsContainTarget(AIComponent* AI, std::vector<CollisionComponent*> DetectedPlayerUnits);
	bool _CHECK_TargetIsInTheAttackZone(AIComponent* AI);
	bool _CHECK_TargetIsAmongDetectedUnits(uint64_t TargetId, std::vector<CollisionComponent*> DetectedEntities);
	std::vector<CollisionComponent*> _CHECK_DetectPlayerUnits(uint64_t EnemyUnitId);
	std::pair<uint64_t, std::vector<std::pair<int, int>>> _CHECK_AllPathsToPotentialTargets(uint64_t AIControlledId, std::vector<CollisionComponent*> PotentialTargets);

private:
	MyFramework* m_Game;
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	SystemsManager* m_Manager_Systems;
	UserGameState* m_GameState;
};











