#pragma once

#include <iostream>
#include <unordered_map>

class MyFramework;
class ComponentsManager;
class EntitiesManager;
class SystemsManager;
class UserGameState;
class UserBlueprints;
struct SDL_Renderer;

// USER TIME AND SPAWN
class UserTimeAndSpawn
{
public:
	UserTimeAndSpawn(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmananger, UserGameState* gamestate, UserBlueprints* blueprints);
	~UserTimeAndSpawn();


public:
	void _CountDown();
	void _Create_IntervalBetweenEnemiesCountdown();
	void _Create_IntervalBetweenWavesCountdown();

	void _Event_SpawnUnit();
	void _Event_StartingCountdown();
	
private:
	std::unordered_map<uint64_t, uint64_t> m_MapOfTimers;
	int m_Y_Value = 200;
	int m_TextHeight = 32;
	bool m_bCurrentWaveExhausted = false;
	bool m_bEnemyDataExhausted = false;

private:
	MyFramework* m_Game;
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	SystemsManager* m_Manager_Systems;
	UserGameState* m_GameState;
	UserBlueprints* m_Blueprints;
};











