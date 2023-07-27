#pragma once

#include "UserExtension.h"

struct SDL_Renderer;
class UserMenuState;
class UserBlueprints;
class UserTimeAndSpawn;

// USER BLUEPRINTS
class UserGameState
{
public:
	UserGameState(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, SystemsManager* systemsmananger, UserMenuState* menustate, UserBlueprints* blueprints);
	~UserGameState();


public:
	void _Delete_DeadEntities(SDL_Renderer* renderer, std::pair<uint16_t, uint16_t> Resolution);

	void _Set_TimeAndSpawnPointer(UserTimeAndSpawn* timeandspawn);
	void _Set_PlayableScreen(std::pair<int, int> WindowDimensions, std::pair<int, int> uihorizontalstripheights, std::pair<int, int> uiverticalstripwidths);
	void _Set_InitialGoldAndMana(int initialgold, int initialmana);
	void _Set_GamePhaseTo(user::GamePhase gamephase);
	

	bool _IsWithinScreen(float x, float y);
	void _Placement_SetAllToGarbageTransform();
	void _Placement_SetAllNodesSubstate(std::vector<uint64_t>& m_Nodes, user::SubState substate);
	void _Update_KillCounter(SDL_Renderer* renderer);

	void _Check_Traps_All();
	void _Check_SpellEffects();
	void _Check_SpecialEffects();
	void _Check_Arrows();
	void _Check_Ballistas_All();
	

	void _RETURN_TO_MENU();
	void _ENTER_PLACEMENT_MODE(user::UI_Button buttontype);
	void _EXIT_PLACEMENT_MODE(bool& bExitPlacementMode);

private:
	void _Set_UI_StripDimensions(std::pair<int, int> horizontalstripheights, std::pair<int, int> verticalstripwidths);


public:

	int m_NumberOfLevels = 0;

	// Imported LEVEL SETTINGS
	int m_InitialGold;
	int m_InitialMana;
	int m_TimeBeforeStart;
	int m_IntervalBetweenSpawns;
	int m_IntervalBetweenWaves;


	// Imported LEVEL DATA
	std::vector<std::vector<char>> m_LevelData;
	std::vector<std::vector<char>> m_CellData;
	uint64_t m_PlayerTower;
	std::vector<uint64_t> m_Nodes;
	uint64_t m_TowerNode;
	std::vector<uint64_t> m_Portals;


	// Imported ENEMY DATA
	std::vector<std::vector<char>> m_EnemyData;
	std::vector<int> m_WaveThreshholds;
	int m_CurrentWave = 0;
	int m_CurrentEnemyUnit = 0;






	//Garbage collection
	std::vector<uint64_t> m_EntitiesToBeDeleted;
	
	
	int m_CurrentLevel;
	int m_EnemiesKilled = 0;
	int m_Enemies_Total; // imported
	int m_Score_AfterEndGame = 0;


	bool m_bGameHasBeenWon = false;
	bool m_bGameHasBeenLost = false;

	user::Motif m_LevelMotif;
	user::GameMode m_Mode;
	user::GamePhase m_Phase;
	user::PlacementMode m_Placement;
	std::pair<int, int> m_UI_HorizontalStripHeights;
	std::pair<int, int> m_UI_VerticalStripWidths;
	std::pair<int, int> m_PlayableScreen_XAxis;
	std::pair<int, int> m_PlayableScreen_YAxis;
	std::pair<int, int> m_GargabeTransform = std::make_pair(-100000, -100000);


	uint64_t m_Player;
	uint64_t m_Mouse;
	uint64_t m_Camera;


	
	

	// UI
	uint64_t m_UI_GoldText;
	uint64_t m_UI_ManaText;
	uint64_t m_UI_ScoreText;
	uint64_t m_UI_KillCounter;
	uint64_t m_UI_CountdownTimer;
	uint64_t m_UI_Button_Ballista;
	uint64_t m_UI_Button_WoodenBox;
	uint64_t m_UI_Button_TarTrap;
	uint64_t m_UI_Button_SpikeTrap;
	uint64_t m_UI_Button_HealSpell;
	uint64_t m_UI_Button_FireballSpell;
	uint64_t m_UI_Button_Cancel;
	uint64_t m_UI_Button_Menu;
	uint64_t m_UI_Background;


	//PLACEMENT
	uint64_t m_Placement_Ballista;
	uint64_t m_Placement_WoodenBox;
	uint64_t m_Placement_TarTrap;
	uint64_t m_Placement_SpikeTrap;
	uint64_t m_Placement_HealSpell;
	uint64_t m_Placement_FireballSpell;
	bool m_bPlacementIsApproved;
	UserMenuState* m_MenuState;

private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	SystemsManager* m_Manager_Systems;
	MyFramework* m_Game;
	UserTimeAndSpawn* TimeAndSpawn;
	UserBlueprints* m_Blueprints;

	friend UserTimeAndSpawn;	
};











