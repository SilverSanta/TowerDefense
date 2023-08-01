// INCLUDES
#include "ECS_Framework.h"
#include "UserExtension.h"
#include "ResourceManager.h"
#include "EntitiesManager.h"
#include "UserExtension.h"
#include "UserBlueprints.h"
#include "UserGameState.h"
#include "UserMenuState.h"
#include "UserTimeAndSpawn.h"
#include "FiniteStateMachine.h"



// GLOBALS
bool bRestart;


// POINTERS TO INSTANCES
MyFramework* Game;

EntitiesManager* Manager_Entities;
ComponentsManager* Manager_Components;
SystemsManager* Manager_Systems;
UserBlueprints* Blueprints;

EntitiesManager* Menu_Entities;
ComponentsManager* Menu_Components;
SystemsManager* Menu_Systems;
UserBlueprints* Menu_Blueprints;

UserGameState* GameState;
UserMenuState* MenuState;

UserTimeAndSpawn* TimeAndSpawn;
FiniteStateMachine* FSM;


// RESOLUTION MAPPER
std::unordered_map<user::Resolution, std::pair<uint16_t, uint16_t>> Mapper_Resolutions {
	
	std::make_pair(user::Resolution::r800x600, std::make_pair(800,600)),
	std::make_pair(user::Resolution::r1024x768, std::make_pair(1024,768)),
	std::make_pair(user::Resolution::r1920x1080, std::make_pair(1920,1080))
};


// LEVEL DATA MAPPER
std::unordered_map<char, user::TileType> LevelDataMapper{

	std::make_pair('X', user::TileType::WORLD_EDGE),
	std::make_pair('O', user::TileType::FLOWING),
	std::make_pair('-', user::TileType::FLOWING_BORDER),
	std::make_pair('L', user::TileType::LAND),
	std::make_pair('M', user::TileType::MOUNTAIN),
	std::make_pair('T', user::TileType::TREE),
	std::make_pair('S', user::TileType::SPAWN_POINT),
	std::make_pair('H', user::TileType::TOWER)
};


// PLACEMENT MAPPER
std::unordered_map<user::PlacementMode, uint64_t> PlacementMapper; // MAPPED AFTER THE CREATION OF INSTANCES FOR BUTTONS


// LANDSCAPE (called when clicking START BUTTON)
void Create_Level()
{
	Entity* PlayerPtr = Manager_Entities->_Get_EntityById(GameState->m_Player);
	ResourcesComponent* Player_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(PlayerPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);

	Entity* ManaDisplayPtr = Manager_Entities->_Get_EntityById(GameState->m_UI_ManaText);
	TextComponent* ManaDisplay_TextPtr = Manager_Components->_Get_ComponentPtrFromId(ManaDisplayPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), Manager_Components->m_Components_Text);

	Entity* GoldDisplayPtr = Manager_Entities->_Get_EntityById(GameState->m_UI_GoldText);
	TextComponent* GoldDisplay_TextPtr = Manager_Components->_Get_ComponentPtrFromId(GoldDisplayPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), Manager_Components->m_Components_Text);

	Entity* CameraPtr = Manager_Entities->_Get_EntityById(GameState->m_Camera);
	CameraComponent* Camera_CameraComponentPtr = Manager_Components->_Get_ComponentPtrFromId(CameraPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::CAMERA), Manager_Components->m_Components_Camera);
	TransformComponent* Camera_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(CameraPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);


	// INCLUDE EXCEPTION SAFETY (NONE FOR NOW)
	std::string LevelDataFilepath = "Assets/Levels/Level" + std::to_string(GameState->m_CurrentLevel) + "/LevelData.txt";
	std::string LevelSettingsFilepath = "Assets/Levels/Level" + std::to_string(GameState->m_CurrentLevel) + "/LevelSettings.txt";
	std::string EnemyDataFilepath = "Assets/Levels/Level" + std::to_string(GameState->m_CurrentLevel) + "/EnemyData.txt";

	// LEVEL DATA	
	GameState->m_LevelData = Manager_Systems->m_System_ImportData->_ImportMatrixFromTextFile(LevelDataFilepath);
	Manager_Systems->m_System_ImportData->_IntroduceBorderBetweenLandAndFlowTiles(GameState->m_LevelData, LevelDataMapper);
	GameState->m_CellData = Manager_Systems->m_System_ImportData->_CellData(GameState->m_LevelData);
	Manager_Systems->m_System_ImportData->_IntroduceMountainSmoothing(GameState->m_CellData, LevelDataMapper);
	Blueprints->_Create_Landscape(GameState->m_LevelData, GameState->m_CellData, GameState->m_LevelMotif, LevelDataMapper, std::make_pair(0, 0), GameState->m_Portals, GameState->m_PlayerTower, GameState->m_Nodes);

	// LEVEL SETTINGS
	std::vector<int> LevelSettings = Manager_Systems->m_System_ImportData->_ImportDataVectorFromTextFile(LevelSettingsFilepath);

	Player_ResourcesPtr->m_Gold_Current = LevelSettings.at(0);
	Player_ResourcesPtr->m_Mana_Current = LevelSettings.at(1);
	GameState->m_TimeBeforeStart = LevelSettings.at(2);
	GameState->m_IntervalBetweenSpawns = LevelSettings.at(3);
	GameState->m_IntervalBetweenWaves = LevelSettings.at(4);

	// ENEMY DATA
	GameState->m_EnemyData = Manager_Systems->m_System_ImportData->_ImportMatrixFromTextFile(EnemyDataFilepath);
	GameState->m_Enemies_Total = Manager_Systems->m_System_ImportData->_Get_MatrixVolume(GameState->m_EnemyData) * (int)GameState->m_Portals.size();
	GameState->m_WaveThreshholds = Manager_Systems->m_System_ImportData->_EstablishWaveThreshholds(GameState->m_EnemyData, (int)GameState->m_Portals.size());
	GameState->_Update_KillCounter(Game->_Get_Renderer());


	// UPDATE
	Manager_Systems->m_System_Resources->_Mana_UpdateDisplayText(Player_ResourcesPtr, ManaDisplay_TextPtr, Game->_Get_Renderer());
	Manager_Systems->m_System_Resources->_Gold_UpdateDisplayText(Player_ResourcesPtr, GoldDisplay_TextPtr, Game->_Get_Renderer());

	// CAMERA SETTINGS
	Camera_CameraComponentPtr->m_HorizontalLimits_LEFT = -(float)GameState->m_UI_VerticalStripWidths.first + 5;
	Camera_CameraComponentPtr->m_HorizontalLimits_RIGHT = (float)GameState->m_CellData.at(0).size() * 32 - (float)Game->_Get_WindowDimensions().first + (float)GameState->m_UI_VerticalStripWidths.second - 5;
	Camera_CameraComponentPtr->m_VerticalLimits_UP = -(float)GameState->m_UI_HorizontalStripHeights.first + 5;
	Camera_CameraComponentPtr->m_VerticalLimits_DOWN = (float)GameState->m_CellData.size() * 32 - (float)Game->_Get_WindowDimensions().second + (float)GameState->m_UI_HorizontalStripHeights.second - 5;
	Camera_TransformPtr->m_X = (Camera_CameraComponentPtr->m_HorizontalLimits_LEFT + Camera_CameraComponentPtr->m_HorizontalLimits_RIGHT) * 0.5f;
	Camera_TransformPtr->m_Y = (Camera_CameraComponentPtr->m_VerticalLimits_UP + Camera_CameraComponentPtr->m_VerticalLimits_DOWN) * 0.5f;
}


// MANAGEMENT
void QUIT()
{
	bRestart = false;
	Game->_Set_ProgramIsRunning(false);	
}
void RESTART()
{
	bRestart = true;
	Game->_Set_ProgramIsRunning(false);
}
void CLEAR_MEMORY()
{
	Game->~MyFramework();
	
	Manager_Entities->~EntitiesManager();
	Manager_Components->~ComponentsManager();
	Manager_Systems->~SystemsManager();
	Blueprints->~UserBlueprints();

	Menu_Entities->~EntitiesManager();
	Menu_Components->~ComponentsManager();
	Menu_Systems->~SystemsManager();
	Menu_Blueprints->~UserBlueprints();

	GameState->~UserGameState();
	MenuState->~UserMenuState();
}


// CALLBACKS
void HandleEvents()
{
	SDL_Event event;
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	auto DeltaTime = Game->_Get_DeltaTicksInGame();

	Entity* MousePtr = Manager_Entities->_Get_EntityById(GameState->m_Mouse);
	TransformComponent* Mouse_InGame_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(MousePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
	StateComponent* Mouse_InGame_StatePtr = Manager_Components->_Get_ComponentPtrFromId(MousePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), Manager_Components->m_Components_State);

	CameraComponent* Camera_InGame_ComponentPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::CAMERA), Manager_Components->m_Components_Camera);
	TransformComponent* Camera_InGame_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
		

	while (SDL_PollEvent(&event))
	{
		SDL_PumpEvents();
		SDL_GetMouseState(&Game->m_MousePos.first, &Game->m_MousePos.second);
				
		// MOUSE MOTION
		if (event.type == SDL_MOUSEMOTION)
		{
			Mouse_InGame_TransformPtr->m_PreviousFrame_X = Mouse_InGame_TransformPtr->m_X;
			Mouse_InGame_TransformPtr->m_PreviousFrame_Y = Mouse_InGame_TransformPtr->m_Y;

			Mouse_InGame_TransformPtr->m_X = (float)Game->m_MousePos.first + Camera_InGame_TransformPtr->m_X;
			Mouse_InGame_TransformPtr->m_Y = (float)Game->m_MousePos.second + Camera_InGame_TransformPtr->m_Y;
		}

		// MOUSE DRAGGING	
		if (GameState->m_Mode == user::GameMode::NORMAL_MODE)
		{
			if (event.button.button == SDL_BUTTON_LEFT && event.type != SDL_MOUSEMOTION && GameState->_IsWithinScreen((float)Game->m_MousePos.first, (float)Game->m_MousePos.second))
			{
				Manager_Systems->m_System_Camera->_StartDraggingCameraWithMouse(Mouse_InGame_StatePtr, Camera_InGame_TransformPtr, Game->m_CameraTransform_InGameForAnchoring.first, Game->m_CameraTransform_InGameForAnchoring.second, Game->m_MousePos.first, Game->m_MousePos.second, Game->m_CameraTransform_SavedInGame.first, Game->m_CameraTransform_SavedInGame.second);
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT) { Manager_Systems->m_System_Camera->_FreeCameraFromMouse(Mouse_InGame_StatePtr, Camera_InGame_ComponentPtr); }
			}
		}

		// MOUSE INTERACTION (PLACEMENT MODE)
		if (GameState->m_Mode == user::GameMode::NORMAL_MODE)
		{
			if (event.button.button == SDL_BUTTON_LEFT && GameState->_IsWithinScreen((float)Game->m_MousePos.first, (float)Game->m_MousePos.second) == false && event.type != SDL_MOUSEMOTION && event.button.type == SDL_MOUSEBUTTONDOWN)
			{				
				for (auto& ButtonComp : Manager_Components->m_Components_Button)
				{
					Entity* CollidingEntity = Manager_Entities->_Get_EntityById(ButtonComp.Get_OwnerId());
					CollisionComponent* ButtonComp_CollisionBoxPtr = Manager_Components->_Get_ComponentPtrFromId(CollidingEntity->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);
					CollisionComponent* Mouse_CollisionBoxPtr = Manager_Components->_Get_ComponentPtrFromId(MousePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);

					bool bIsColliding = Manager_Systems->m_System_Collision->_CollisionCheck(Mouse_CollisionBoxPtr, ButtonComp_CollisionBoxPtr);

					if (bIsColliding == true)
					{
						ButtonComponent* Button_Colliding = Manager_Components->_Get_ComponentPtrFromId(CollidingEntity->_Get_ComponentIdFromEntityByType(user::ComponentType::BUTTON), Manager_Components->m_Components_Button);
						ResourcesComponent* PlayerResources = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
						ResourcesComponent* ButtonResources = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(Button_Colliding->Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);

						bool bHasFunds = false;
						bool bInactiveInDefensePhase = false;

						if (Button_Colliding->m_ButtonType == user::UI_Button::BALLISTA || Button_Colliding->m_ButtonType == user::UI_Button::WOODEN_BOX || Button_Colliding->m_ButtonType == user::UI_Button::TAR_TRAP || Button_Colliding->m_ButtonType == user::UI_Button::SPIKE_TRAP)
						{
							bHasFunds = Manager_Systems->m_System_Resources->_Gold_CheckForSufficientFunds(PlayerResources, ButtonResources);
							bInactiveInDefensePhase = true;
						}
						else if (Button_Colliding->m_ButtonType == user::UI_Button::HEAL_SPELL || Button_Colliding->m_ButtonType == user::UI_Button::FIREBALL_SPELL)
						{
							bHasFunds = Manager_Systems->m_System_Resources->_Mana_CheckForSufficientFunds(PlayerResources, ButtonResources);
							bInactiveInDefensePhase = false;
						}
						else if (Button_Colliding->m_ButtonType == user::UI_Button::MENU)
						{
							if (Game->_InMenu() == false)
							{
								Game->_Set_InMenu(true);
								Game->m_CameraTransform_SavedInGame = std::make_pair(Camera_InGame_TransformPtr->m_X, Camera_InGame_TransformPtr->m_Y);

								for (auto& Sprite : Manager_Components->m_Components_AnimatedSprite)
								{
									Manager_Systems->m_System_Animation->_SetTextureTransparency(Game->_Get_Renderer(), &Sprite, true);
								}

								MenuState->_Set_MenuLayout_DuringGameMenu(Game->_Get_WindowDimensions());
							}
						}
						
						bool bCanBeActivated;
						if (GameState->m_Phase == user::GamePhase::PREPARATION_PHASE) { bCanBeActivated = true; }
						else if(GameState->m_Phase == user::GamePhase::DEFENSE_PHASE && bInactiveInDefensePhase == false){ bCanBeActivated = true; }
						else { bCanBeActivated = false; }

						if (bHasFunds && bCanBeActivated)
						{
							user::UI_Button m_ButtonType = Button_Colliding->m_ButtonType;
							GameState->_ENTER_PLACEMENT_MODE(m_ButtonType);
						}
					}
				}
			}
		}

		// PLACING THE OBJECT
		if (GameState->m_Mode == user::GameMode::PLACEMENT_MODE)
		{
			if (event.button.button == SDL_BUTTON_LEFT && GameState->_IsWithinScreen((float)Game->m_MousePos.first, (float)Game->m_MousePos.second) == true && event.type != SDL_MOUSEMOTION && event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				Entity* PlacementObj_Ptr = Manager_Entities->_Get_EntityById(PlacementMapper.at(GameState->m_Placement));
				CollisionComponent* PlacementObj_CollisionPtr = Manager_Components->_Get_ComponentPtrFromId(PlacementObj_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);

				if(GameState->m_Placement != user::PlacementMode::PLACEMENT_HEALSPELL && GameState->m_Placement != user::PlacementMode::PLACEMENT_FIREBALLSPELL)
				{				
					std::vector<CollisionComponent*> ListOfCollidingNodes = Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(PlacementObj_CollisionPtr, user::CollisionProfile::NODE, user::CollisionProfile::_NONE);
				
					int ObjectsNodeSlots = (ListOfCollidingNodes.size() > 0) ? ((int)std::pow((PlacementObj_CollisionPtr->_Get_Dimensions().first / ListOfCollidingNodes.at(0)->_Get_Dimensions().first), 2)) : (-1);
					bool bNodesMatchObject = ((int)ListOfCollidingNodes.size() == ObjectsNodeSlots) ? (true) : (false);

					if (bNodesMatchObject && ((int)ListOfCollidingNodes.size() == 1 || (int)ListOfCollidingNodes.size() == 4))
					{
						std::pair<float, float> coordinates;

						float Rolling_X = 0;
						float Rolling_Y = 0;

						for (auto& CollidingNode : ListOfCollidingNodes)
						{
							Entity* NodeEntityPtr = Manager_Entities->_Get_EntityById(CollidingNode->Get_OwnerId());
							TransformComponent* NodeEntity_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(NodeEntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

							Rolling_X += NodeEntity_TransformPtr->m_X;
							Rolling_Y += NodeEntity_TransformPtr->m_Y;
						}

						coordinates = std::make_pair(Rolling_X / (int)ListOfCollidingNodes.size(), Rolling_Y / (int)ListOfCollidingNodes.size());

						bool bObjectIsColliding = Manager_Systems->m_System_Collision->_CollisionCheck_AllFromLayerToLayer(PlacementObj_CollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::STATIC_OBJECTS);

						if (bObjectIsColliding == false)
						{
							TransformComponent* PlacementObj_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(PlacementObj_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
							ResourcesComponent* Player_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);

							TextComponent* GoldDisplayText = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_GoldText)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), Manager_Components->m_Components_Text);
							
							ResourcesComponent* Ballista_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_Button_Ballista)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
							ResourcesComponent* WoodenBox_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_Button_WoodenBox)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
							ResourcesComponent* TarTrap_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_Button_TarTrap)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
							ResourcesComponent* SpikeTrap_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_Button_SpikeTrap)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
						
							bool bHasFunds = true;
							switch (GameState->m_Placement)
							{
							case user::PlacementMode::PLACEMENT_BALLISTA:
								if (Manager_Systems->m_System_Resources->_Gold_CheckForSufficientFunds(Player_ResourcesPtr, Ballista_ResourcesPtr) && (int)ListOfCollidingNodes.size() == 1)
								{
									Manager_Systems->m_System_Resources->_Gold_Subtract(Player_ResourcesPtr, Ballista_ResourcesPtr, GoldDisplayText, Game->_Get_Renderer());
									Blueprints->_Create_Ballista(coordinates.first, coordinates.second + 16, Game->_Get_CurrentTickInGame());
								}
								else { bHasFunds = false; }
								break;

							case user::PlacementMode::PLACEMENT_WOODENBOX:
								if (Manager_Systems->m_System_Resources->_Gold_CheckForSufficientFunds(Player_ResourcesPtr, WoodenBox_ResourcesPtr) && (int)ListOfCollidingNodes.size() == 1)
								{
									Manager_Systems->m_System_Resources->_Gold_Subtract(Player_ResourcesPtr, WoodenBox_ResourcesPtr, GoldDisplayText, Game->_Get_Renderer());

									// Change node to 'unpassable by units'															
									NodeComponent* NodeComponentChangedToUnPassable = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(ListOfCollidingNodes.at(0)->Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::NODE), Manager_Components->m_Components_Node);
									uint64_t NodeComponentId = NodeComponentChangedToUnPassable->m_Id;
									NodeComponentChangedToUnPassable->m_bIsPassableByUnits = false;

									uint64_t box = Blueprints->_Create_WoodenBox(coordinates.first, coordinates.second + 16, NodeComponentId);
								}
								else { bHasFunds = false; }
								break;

							case user::PlacementMode::PLACEMENT_TARTRAP:
								if (Manager_Systems->m_System_Resources->_Gold_CheckForSufficientFunds(Player_ResourcesPtr, TarTrap_ResourcesPtr))
								{
									Manager_Systems->m_System_Resources->_Gold_Subtract(Player_ResourcesPtr, TarTrap_ResourcesPtr, GoldDisplayText, Game->_Get_Renderer());
									Blueprints->_Create_TarTrap(coordinates.first, coordinates.second, Game->_Get_CurrentTickInGame());
								}
								else { bHasFunds = false; }
								break;

							case user::PlacementMode::PLACEMENT_SPIKETRAP:
								if (Manager_Systems->m_System_Resources->_Gold_CheckForSufficientFunds(Player_ResourcesPtr, SpikeTrap_ResourcesPtr))
								{
									Manager_Systems->m_System_Resources->_Gold_Subtract(Player_ResourcesPtr, SpikeTrap_ResourcesPtr, GoldDisplayText, Game->_Get_Renderer());
									Blueprints->_Create_SpikeTrap(coordinates.first, coordinates.second, Game->_Get_CurrentTickInGame());
								}
								else { bHasFunds = false; }
								break;
							}
							if (bHasFunds == false)
							{								
								GameState->m_bPlacementIsApproved = false;

								bool bExitPlacementMode = true;
								
								GameState->_EXIT_PLACEMENT_MODE(bExitPlacementMode);
							}
							else { continue; }
						}
					}
				}
				else if (GameState->m_Placement == user::PlacementMode::PLACEMENT_HEALSPELL || GameState->m_Placement == user::PlacementMode::PLACEMENT_FIREBALLSPELL)
				{
					TransformComponent* PlacementObj_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(PlacementObj_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
					ResourcesComponent* Player_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
					TextComponent* ManaDisplayText = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_ManaText)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), Manager_Components->m_Components_Text);
					ResourcesComponent* HealSpell_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_Button_HealSpell)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
					ResourcesComponent* FireballSpell_ResourcesPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_UI_Button_FireballSpell)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);

					bool bHasFunds = true;
					if (GameState->m_Placement == user::PlacementMode::PLACEMENT_FIREBALLSPELL)
					{
						if (Manager_Systems->m_System_Resources->_Mana_CheckForSufficientFunds(Player_ResourcesPtr, FireballSpell_ResourcesPtr))
						{
							// Mana management
							Manager_Systems->m_System_Resources->_Mana_Subtract(Player_ResourcesPtr, FireballSpell_ResourcesPtr, ManaDisplayText, Game->_Get_Renderer());

							// Creation of fireball
							uint64_t Fireball_ID = Blueprints->_Create_Fireball(Mouse_InGame_TransformPtr->m_X, Mouse_InGame_TransformPtr->m_Y, Game->_Get_CurrentTickInGame());
							Entity* Fireball_Ptr = Manager_Entities->_Get_EntityById(Fireball_ID);
							CollisionComponent* Fireball_CollisionPtr = Manager_Components->_Get_ComponentPtrFromId(Fireball_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);
							AttackComponent* Fireball_AttackPtr = Manager_Components->_Get_ComponentPtrFromId(Fireball_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::ATTACK), Manager_Components->m_Components_Attack);

							// Check all enemies for collision - if hit, apply damage to all of them 
							Manager_Systems->m_System_Collision->_Update_AllCollisionShapePositions(Camera_InGame_TransformPtr);
							std::vector<CollisionComponent*> CollidingEnemies = Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(Fireball_CollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::UNIT_PLAYER);

							for (auto& Collider : CollidingEnemies)
							{
								TransformComponent* PlacementObj_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(PlacementObj_Ptr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

								Entity* CollidingEntityPtr = Manager_Entities->_Get_EntityById(Collider->Get_OwnerId());
								Manager_Systems->m_System_HealthAndAttack->_ApplyDamage(CollidingEntityPtr, (int)Fireball_AttackPtr->m_MagicDmg, GameState->m_EntitiesToBeDeleted, GameState, Game->_Get_Renderer());
							}
						}
						else
						{
							bHasFunds = false;
						}
					}
					else if (GameState->m_Placement == user::PlacementMode::PLACEMENT_HEALSPELL)
					{
						// We need to check if we are actually clicking any player units! Collision check!
						CollisionComponent* Mouse_CollisionPtr = Manager_Components->_Get_ComponentPtrFromId(MousePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);
						std::vector<CollisionComponent*> CollidingPlayerUnits = Manager_Systems->m_System_Collision->_CollisionList_CollidingComponentsFromLayerToLayer(Mouse_CollisionPtr, user::CollisionProfile::UNIT_PLAYER, user::CollisionProfile::STATIC_OBJECTS);

						bool bPlayerUnitsHit = ((int)CollidingPlayerUnits.size() != 0) ? (true) : (false);
						bool bOneOfUnitsNeedsHealing = false;
						int i = 0;

						if (bPlayerUnitsHit)
						{
							while (i < (int)CollidingPlayerUnits.size() && bOneOfUnitsNeedsHealing == false)
							{
								Entity* CollidingUnitPtr = Manager_Entities->_Get_EntityById(CollidingPlayerUnits.at(i)->Get_OwnerId());
								if (CollidingUnitPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH) != NULL)
								{
									HealthComponent* CollidingUnit_HealthPtr = Manager_Components->_Get_ComponentPtrFromId(CollidingUnitPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH), Manager_Components->m_Components_Health);
									if (CollidingUnit_HealthPtr->m_CurrentHealth != CollidingUnit_HealthPtr->m_MaxHealth)
									{
										bOneOfUnitsNeedsHealing = true;
									}
									else
									{
										i++;
									}
								}
							}
						}

						if (bOneOfUnitsNeedsHealing)
						{
							if (Manager_Systems->m_System_Resources->_Mana_CheckForSufficientFunds(Player_ResourcesPtr, HealSpell_ResourcesPtr))
							{
								Entity* CollidingUnitPtr = Manager_Entities->_Get_EntityById(CollidingPlayerUnits.at(i)->Get_OwnerId());

								HealthComponent* CollidingUnit_HealthPtr = Manager_Components->_Get_ComponentPtrFromId(CollidingUnitPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::HEALTH), Manager_Components->m_Components_Health);
								TransformComponent* CollidingUnit_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(CollidingUnitPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

								uint64_t Heal_ID = Blueprints->_Create_HealSpell(CollidingUnit_TransformPtr->m_X, CollidingUnit_TransformPtr->m_Y, Game->_Get_CurrentTickInGame());
								Entity* Heal_EntityPtr = Manager_Entities->_Get_EntityById(Heal_ID);
								AttackComponent* Heal_AttackPtr = Manager_Components->_Get_ComponentPtrFromId(Heal_EntityPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::ATTACK), Manager_Components->m_Components_Attack);

								Manager_Systems->m_System_HealthAndAttack->_ApplyHeal(CollidingUnitPtr, (int)Heal_AttackPtr->m_MagicDmg);

								// Mana management
								Manager_Systems->m_System_Resources->_Mana_Subtract(Player_ResourcesPtr, HealSpell_ResourcesPtr, ManaDisplayText, Game->_Get_Renderer());
							}
							else
							{
								bHasFunds = false;
							}
						}
					}

					if (bHasFunds == false)
					{					
						GameState->m_bPlacementIsApproved = false;
						GameState->m_Mode = user::GameMode::NORMAL_MODE;

						// Cancel button goes to garbage
						Entity* CancelButtonPtr = Manager_Entities->_Get_EntityById(GameState->m_UI_Button_Cancel);
						TransformComponent* CancelButton_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(CancelButtonPtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
						CancelButton_TransformPtr->m_X -= (float)GameState->m_GargabeTransform.first;
					}
				}
			}
		}

		// EXIT THE PLACEMENT MODE
		if (GameState->m_Mode == user::GameMode::PLACEMENT_MODE)
		{
			// Exit placement mode?
			bool bExitPlacementMode = false;
			if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || event.button.button == SDL_BUTTON_RIGHT)
			{
				bExitPlacementMode = true;				
			}
			else if (event.button.button == SDL_BUTTON_LEFT && GameState->_IsWithinScreen((float)Game->m_MousePos.first, (float)Game->m_MousePos.second) == false && event.type != SDL_MOUSEMOTION && event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				for (auto& ButtonComp : Manager_Components->m_Components_Button)
				{
					Entity* CollidingEntity = Manager_Entities->_Get_EntityById(ButtonComp.Get_OwnerId());
					CollisionComponent* ButtonComp_CollisionBoxPtr = Manager_Components->_Get_ComponentPtrFromId(CollidingEntity->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);
					CollisionComponent* Mouse_CollisionBoxPtr = Manager_Components->_Get_ComponentPtrFromId(MousePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);

					bool bIsColliding = Manager_Systems->m_System_Collision->_CollisionCheck(Mouse_CollisionBoxPtr, ButtonComp_CollisionBoxPtr);

					if (bIsColliding == true)
					{
						ButtonComponent* Button_Colliding = Manager_Components->_Get_ComponentPtrFromId(CollidingEntity->_Get_ComponentIdFromEntityByType(user::ComponentType::BUTTON), Manager_Components->m_Components_Button);

						if (Button_Colliding->m_ButtonType == user::UI_Button::CANCEL)
						{
							bExitPlacementMode = true;
						}
					}
				}
			}			
			GameState->_EXIT_PLACEMENT_MODE(bExitPlacementMode);	
		}

		// RETURN TO MENU
		else if (GameState->m_Mode == user::GameMode::NORMAL_MODE)
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				if (Game->_InMenu() == false)
				{					
					GameState->_RETURN_TO_MENU();
				}
			}
		}
				
		// CAMERA MOVEMENT -> ARROWS		
		if (event.type == SDL_KEYDOWN && Camera_InGame_ComponentPtr != nullptr)
		{
			mfk::NormalVector2D cameramovementvector;
			if (keyboard_state_array[SDL_SCANCODE_LEFT] && keyboard_state_array[SDL_SCANCODE_RIGHT] || keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
			{
				return;
			}
			else if (keyboard_state_array[SDL_SCANCODE_LEFT] && keyboard_state_array[SDL_SCANCODE_UP])
			{
				cameramovementvector.x = -1;
				cameramovementvector.y = -1;
			}
			else if (keyboard_state_array[SDL_SCANCODE_LEFT] && keyboard_state_array[SDL_SCANCODE_DOWN])
			{
				cameramovementvector.x = -1;
				cameramovementvector.y = 1;
			}
			else if (keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_UP])
			{
				cameramovementvector.x = 1;
				cameramovementvector.y = -1;
			}
			else if (keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_DOWN])
			{
				cameramovementvector.x = 1;
				cameramovementvector.y = 1;
			}
			else if (keyboard_state_array[SDL_SCANCODE_LEFT])
			{
				cameramovementvector.x = -1;
				cameramovementvector.y = 0;
			}
			else if (keyboard_state_array[SDL_SCANCODE_RIGHT])
			{
				cameramovementvector.x = 1;
				cameramovementvector.y = 0;
			}
			else if (keyboard_state_array[SDL_SCANCODE_UP])
			{
				cameramovementvector.x = 0;
				cameramovementvector.y = -1;
			}
			else if (keyboard_state_array[SDL_SCANCODE_DOWN])
			{
				cameramovementvector.x = 0;
				cameramovementvector.y = 1;
			}

			if (cameramovementvector.x != 0 || cameramovementvector.y != 0)
			{
				Manager_Systems->m_System_Camera->_MoveCameraInDirection(Camera_InGame_ComponentPtr, cameramovementvector, DeltaTime);


				Mouse_InGame_TransformPtr->m_PreviousFrame_X = Mouse_InGame_TransformPtr->m_X;
				Mouse_InGame_TransformPtr->m_PreviousFrame_Y = Mouse_InGame_TransformPtr->m_Y;

				Mouse_InGame_TransformPtr->m_X = (float)Game->m_MousePos.first + Camera_InGame_TransformPtr->m_X;
				Mouse_InGame_TransformPtr->m_Y = (float)Game->m_MousePos.second + Camera_InGame_TransformPtr->m_Y;
			}
		}
	}
}
void HandleLogic()
{	
	// CAMERA AND MOUSE POINTERS
	Entity* MouseEnt = Manager_Entities->_Get_EntityById(GameState->m_Mouse);
	StateComponent* MouseStatePtr = Manager_Components->_Get_ComponentPtrFromId(MouseEnt->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), Manager_Components->m_Components_State);
	Entity* CameraEnt = Manager_Entities->_Get_EntityById(GameState->m_Camera);
	CameraComponent* CameraComponentPtr = Manager_Components->_Get_ComponentPtrFromId(CameraEnt->_Get_ComponentIdFromEntityByType(user::ComponentType::CAMERA), Manager_Components->m_Components_Camera);
	TransformComponent* CameraTransformPtr = Manager_Components->_Get_ComponentPtrFromId(CameraEnt->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);


	// UPDATE REPOSE (THEY NEED UP-To-DATE TIME)
	Manager_Components->_UpdateRepositories(Game->_Get_CurrentTickInGame());


	// UPDATE THE LOGIC
	FSM->_StateMachine_All();
	Manager_Systems->m_System_Movement->_MoveAll(Game->_Get_DeltaTicksInGame());
	Manager_Systems->m_System_Collision->_Update_AllCollisionShapePositions(CameraTransformPtr);
	Manager_Systems->m_System_Animation->_NextFrame_AllSprites();
	Manager_Systems->m_System_Animation->_Update_AllAnimationsToState();
	Manager_Systems->m_System_State->_UpdateState_AllPreviousToCurrent();
		

	

	// DRAGGING LOGIC
	if (MouseStatePtr->m_CurrentSubState == user::SubState::MOVING_DRAGGING)
	{
		SDL_GetMouseState(&Game->m_MousePos.first, &Game->m_MousePos.second);
		Manager_Systems->m_System_Camera->_DraggingCameraWithMouse(MouseStatePtr, CameraComponentPtr, Game->m_CameraTransform_InGameForAnchoring.first, Game->m_CameraTransform_InGameForAnchoring.second, Game->m_MousePos.first, Game->m_MousePos.second, (int)Game->m_CameraTransform_SavedInGame.first, (int)Game->m_CameraTransform_SavedInGame.second);
	}
	

	// PLACEMENT LOGIC -> SNAPPING TO GRID OF NODES
	if (GameState->m_Mode == user::GameMode::NORMAL_MODE) { GameState->_Placement_SetAllToGarbageTransform(); }
	else if (GameState->m_Mode == user::GameMode::PLACEMENT_MODE)
	{		
		uint64_t PlacedObjectId = PlacementMapper.at(GameState->m_Placement);
		TransformComponent* PlacementObj_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(PlacedObjectId)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
		TransformComponent* Mouse_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Mouse)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

		if (GameState->m_Placement == user::PlacementMode::PLACEMENT_HEALSPELL || GameState->m_Placement == user::PlacementMode::PLACEMENT_FIREBALLSPELL)
		{
			PlacementObj_TransformPtr->m_X = Mouse_TransformPtr->m_X;
			PlacementObj_TransformPtr->m_Y = Mouse_TransformPtr->m_Y;
		}
		else
		{
			GameState->_Placement_SetAllNodesSubstate(GameState->m_Nodes, user::SubState::IDLE_NODE_AVAILABLE);
		
			CollisionComponent* PlacementObj_CollisionPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(PlacedObjectId)->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);

			int i = 0;
			bool bFound = false;
		
			for (auto& NodeId : GameState->m_Nodes)
			{
				Entity* NodePtr = Manager_Entities->_Get_EntityById(NodeId);

				CollisionComponent* Node_CollisionPtr = Manager_Components->_Get_ComponentPtrFromId(NodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);
				bool bNodeCollidesWithSth = Manager_Systems->m_System_Collision->_CollisionCheck_AllFromLayerToLayer(Node_CollisionPtr, user::CollisionProfile::UNIT_ENEMY, user::CollisionProfile::STATIC_OBJECTS);
				
				if (bNodeCollidesWithSth)
				{
					StateComponent* Node_StatePtr = Manager_Components->_Get_ComponentPtrFromId(NodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), Manager_Components->m_Components_State);
					Manager_Systems->m_System_State->_ChangeCurrentState(Node_StatePtr, user::State::IDLE, user::SubState::IDLE_NODE_UNAVAILABLE, user::Direction::Facing_RIGHT);
				}

				CollisionComponent* Mouse_CollisionPtr = Manager_Components->_Get_ComponentPtrFromId(MouseEnt->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Manager_Components->m_Components_Collision);
				TransformComponent* Mouse_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(MouseEnt->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

				if (Manager_Systems->m_System_Collision->_CollisionCheck(Mouse_CollisionPtr, Node_CollisionPtr))
				{
					TransformComponent* Node_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(NodePtr->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

					Mouse_TransformPtr->m_X = Node_TransformPtr->m_X;
					Mouse_TransformPtr->m_Y = Node_TransformPtr->m_Y;

					bFound = true;
				}
				else
				{
					i++;
				}
			}		
			if (bFound)
			{
				PlacementObj_TransformPtr->m_X = Mouse_TransformPtr->m_X + (PlacementObj_CollisionPtr->_Get_Dimensions().first / 2 - 16);
				PlacementObj_TransformPtr->m_Y = Mouse_TransformPtr->m_Y + (PlacementObj_CollisionPtr->_Get_Dimensions().second / 2 - 16);						
			}
			else
			{
				PlacementObj_TransformPtr->m_X = Mouse_TransformPtr->m_X;
				PlacementObj_TransformPtr->m_Y = Mouse_TransformPtr->m_Y;
			}
		}
	}


	// MANAGEMENT
	Manager_Systems->m_System_Resources->_CheckAllButtonsForState(GameState->m_Player);
	GameState->_Check_SpellEffects();
	GameState->_Check_SpecialEffects();
	GameState->_Check_Ballistas_All();
	GameState->_Check_Arrows();
	GameState->_Check_Traps_All();
	TimeAndSpawn->_CountDown();
	Manager_Systems->m_System_State->_CheckForDeadState_All(GameState->m_EntitiesToBeDeleted);
	GameState->_Delete_DeadEntities(Game->_Get_Renderer(), Game->_Get_WindowDimensions());
}
void HandleRendering()
{
	AnimatedSpriteComponent* Mouse_InGame_SpritePtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Mouse)->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE1), Manager_Components->m_Components_AnimatedSprite);
	TransformComponent* Camera_InGame_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

	SDL_SetRenderDrawColor(Game->_Get_Renderer(), 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game->_Get_Renderer());

	// (1) Render (send to buffer)
	Manager_Components->_SortLayerSortedSpritesByY();

	Manager_Systems->m_System_Render->_RenderAllSprites_FromLayerToLayer(Game->_Get_Renderer(), Camera_InGame_TransformPtr, user::Layer::BACKGROUND_FAR, user::Layer::UI_BACKGROUND);
	
	Manager_Systems->m_System_Render->_RenderAllTexts_FromLayerToLayer(Game->_Get_Renderer(), Camera_InGame_TransformPtr, user::Layer::BACKGROUND_FAR, user::Layer::UI_BACKGROUND);

	Manager_Systems->m_System_Render->_RenderAllSprites_FromLayerToLayer(Game->_Get_Renderer(), Camera_InGame_TransformPtr, user::Layer::UI_BACKGROUND, user::Layer::_COUNT);
	Manager_Systems->m_System_Render->_RenderAllTexts_FromLayerToLayer(Game->_Get_Renderer(), Camera_InGame_TransformPtr, user::Layer::UI_BACKGROUND, user::Layer::_COUNT);	
	Manager_Systems->m_System_Render->_RenderSprite(Game->_Get_Renderer(), Mouse_InGame_SpritePtr, Camera_InGame_TransformPtr);

	// (2) Buffer to screen
	SDL_RenderPresent(Game->_Get_Renderer());
}

void HandleMenuEvents()
{
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	SDL_Event event;

	TransformComponent* Camera_InMenu_TransformPtr = Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Menu_Components->m_Components_Transform);
	TransformComponent* Camera_InGame_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);

	TransformComponent* Mouse_InMenu_TransformPtr = Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Mouse)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Menu_Components->m_Components_Transform);
	StateComponent* Mouse_InMenu_StatePtr = Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Mouse)->_Get_ComponentIdFromEntityByType(user::ComponentType::STATE), Menu_Components->m_Components_State);

	while (SDL_PollEvent(&event))
	{
		auto DeltaTime = Game->_Get_DeltaTicksInGame();
		SDL_PumpEvents();
		SDL_GetMouseState(&Game->m_MousePos.first, &Game->m_MousePos.second);

	
		// LEFT-CLICKS IN MENU
		if (event.button.button == SDL_BUTTON_LEFT && event.type != SDL_MOUSEMOTION && event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			CollisionComponent* Mouse_InGame_CollisionPtr = Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Mouse)->_Get_ComponentIdFromEntityByType(user::ComponentType::COLLISION1), Menu_Components->m_Components_Collision);
						
			for (auto& CollisionComp : Menu_Components->m_Components_Collision)
			{
				if (CollisionComp.m_Id != Mouse_InGame_CollisionPtr->m_Id)
				{
					if (Menu_Systems->m_System_Collision->_CollisionCheck(Mouse_InGame_CollisionPtr, &CollisionComp))
					{	
						if (CollisionComp.Get_OwnerId() == MenuState->m_Button_Start)
						{
							AnimatedSpriteComponent* BackgroundPtr =Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Background)->_Get_ComponentIdFromEntityByType(user::ComponentType::ANIMATEDSPRITE1), Menu_Components->m_Components_AnimatedSprite);
							Game->_StartGame();

							std::pair<uint16_t, uint16_t> dimensions = Game->_Get_WindowDimensions();
							std::string fullpath = "Assets/Sprites/Menu/MenuBackground_Transparent_" + std::to_string(dimensions.first) + "x" + std::to_string(dimensions.second) + ".bmp";
							
							Menu_Systems->m_System_Animation->_SubstituteSprite(Game->_Get_Renderer(), BackgroundPtr, fullpath);
							Menu_Systems->m_System_Animation->_SetTextureTransparency(Game->_Get_Renderer(), BackgroundPtr, true);

							Create_Level();
							Manager_Systems->m_System_Collision->_Update_AllCollisionShapePositions(Camera_InMenu_TransformPtr);
							Manager_Systems->m_System_Pathfinding->_Set_NeighboursForNode_All(GameState->m_Nodes);
							Manager_Systems->m_System_Pathfinding->_Get_NodesFromGameState(GameState->m_Nodes);
							GameState->m_TowerNode = Manager_Systems->m_System_Pathfinding->_SelectClosestNodefromEntity(GameState->m_PlayerTower, 32);
							GameState->_Set_GamePhaseTo(user::GamePhase::PREPARATION_PHASE);

							TimeAndSpawn->_Event_StartingCountdown();

							Game->_Set_InMenu(false);							
						}
						else if (CollisionComp.Get_OwnerId() == MenuState->m_Button_Quit)
						{
							QUIT();
						}
						else if (CollisionComp.Get_OwnerId() == MenuState->m_Button_Restart)
						{
							RESTART();
						}
						else if (CollisionComp.Get_OwnerId() == MenuState->m_Button_Resume)
						{
							if (Game->_InMenu() == true && Game->_GameIsRunning() == true)
							{
								// (1) Switch the bInMenu to be FALSE
								Game->_Set_InMenu(false);

								for (auto& Sprite : Manager_Components->m_Components_AnimatedSprite)
								{
									Manager_Systems->m_System_Animation->_SetTextureTransparency(Game->_Get_Renderer(), &Sprite, false);
								}
							}
						}
						else if (CollisionComp.Get_OwnerId() == MenuState->m_Button_SelectLevel_ArrowLeft)
						{
							MenuState->_Set_MenuLayout_ChangeLevel(true);
						}
						else if (CollisionComp.Get_OwnerId() == MenuState->m_Button_SelectLevel_ArrowRight)
						{
							MenuState->_Set_MenuLayout_ChangeLevel(false);
						}
						else if (CollisionComp.Get_OwnerId() == MenuState->m_Button_SelectMotif_ArrowLeft || CollisionComp.Get_OwnerId() == MenuState->m_Button_SelectMotif_ArrowRight)
						{
							MenuState->_Set_MenuLayout_ChangeMotif();
						}
					}
				}				
			}
		}

		// MOUSE MOTION
		if (event.type == SDL_MOUSEMOTION)
		{
			Mouse_InMenu_TransformPtr->m_PreviousFrame_X = Mouse_InMenu_TransformPtr->m_X; Mouse_InMenu_TransformPtr->m_PreviousFrame_Y = Mouse_InMenu_TransformPtr->m_Y;
			Mouse_InMenu_TransformPtr->m_X = (float)Game->m_MousePos.first;	Mouse_InMenu_TransformPtr->m_Y = (float)Game->m_MousePos.second;
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1)
		{
			for (auto& Collision : Menu_Components->m_Components_Collision)
			{
				Collision.bShowShape = false;
			}
		}


		// MENU_INGAME SWITCH
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			if (Game->_InMenu() == true && Game->_GameIsRunning() == true)
			{
				// (1) Switch the bInMenu to be FALSE
				Game->_Set_InMenu(false);
			
				for (auto& Sprite : Manager_Components->m_Components_AnimatedSprite)
				{
					Manager_Systems->m_System_Animation->_SetTextureTransparency(Game->_Get_Renderer(), &Sprite, false);
				}
			}			
		}
	}
}
void HandleMenuLogic()
{
	TransformComponent* Camera_InMenu_TransformPtr = Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Menu_Components->m_Components_Transform);

	Menu_Components->_UpdateRepositories(Game->_Get_CurrentTickInMenu());
	Menu_Systems->m_System_Movement->_MoveAll(Game->_Get_DeltaTicksInGame());
	Menu_Systems->m_System_Collision->_Update_AllCollisionShapePositions(Camera_InMenu_TransformPtr);
	Menu_Systems->m_System_Animation->_NextFrame_AllSprites();
	Menu_Systems->m_System_Animation->_Update_AllAnimationsToState();
	Menu_Systems->m_System_State->_UpdateState_AllPreviousToCurrent();
}
void HandleMenuRendering()
{
	TransformComponent* Camera_Menu_TransformPtr = Menu_Components->_Get_ComponentPtrFromId(Menu_Entities->_Get_EntityById(MenuState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Menu_Components->m_Components_Transform);
	TransformComponent* Camera_InGame_TransformPtr = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Camera)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), Manager_Components->m_Components_Transform);
		
	SDL_SetRenderDrawColor(Game->_Get_Renderer(), 122, 122, 122, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game->_Get_Renderer());	
	
	// (1a) Render (send to buffer INGAME objects (behind menu)
	if (Game->_GameIsRunning() == true || GameState->m_bGameHasBeenLost || GameState->m_bGameHasBeenWon)
	{
		for (auto& Sprite : Manager_Components->m_Components_AnimatedSprite)
		{
			if (Sprite.Get_OwnerId() != GameState->m_Mouse)
			{
				Manager_Systems->m_System_Render->_RenderSprite(Game->_Get_Renderer(), &Sprite, Camera_InGame_TransformPtr);
			}
		}			
	}
		
	// (1b) Render (send to buffer menu objects)	
	Menu_Systems->m_System_Render->_RenderAllSprites(Game->_Get_Renderer(), Camera_Menu_TransformPtr);	
	//Menu_Systems->System_Render->RenderAllCollisionShapes(Game->Get_Renderer(), Camera_Menu_TransformPtr);
	Menu_Systems->m_System_Render->_RenderAllTexts_FromLayerToLayer(Game->_Get_Renderer(), Camera_Menu_TransformPtr, user::Layer::UI_BACKGROUND, user::Layer::_COUNT);
	Menu_Systems->m_System_Render->_RenderAllSprites_FromLayerToLayer(Game->_Get_Renderer(), Camera_Menu_TransformPtr, user::Layer::MOUSE, user::Layer::_COUNT);
	// (2) Buffer to screen
	SDL_RenderPresent(Game->_Get_Renderer());
}


// MAIN
int main(int argc, char* argv[])
{	
	bRestart = true;
	
		while (bRestart) // QUIT -> switches bRestart to FALSE
		{
			user::Resolution resolution = user::Resolution::r1024x768;
			Game = new MyFramework("Tower Defense", Mapper_Resolutions.at(resolution), 30, 10000);


			// INSTANCES
			Manager_Entities = new EntitiesManager(Game->m_MaxEntities);
			Manager_Components = new ComponentsManager(Game->m_MaxEntities, Manager_Entities);
			Blueprints = new UserBlueprints(Game, Manager_Components, Manager_Entities);
			Manager_Systems = new SystemsManager(Manager_Entities, Manager_Components, Blueprints);			
			Manager_Systems->m_System_Action->m_System_HealthAndAttack = Manager_Systems->m_System_HealthAndAttack;
			
			Manager_Systems->m_System_HealthAndAttack-> m_Game = Game;

			Menu_Entities = new EntitiesManager(Game->m_MaxEntities);
			Menu_Components = new ComponentsManager(Game->m_MaxEntities, Menu_Entities);
			Menu_Blueprints = new UserBlueprints(Game, Menu_Components, Menu_Entities);
			Menu_Systems = new SystemsManager(Menu_Entities, Menu_Components, Menu_Blueprints);

			GameState = new UserGameState(Game, Manager_Components, Manager_Entities, Manager_Systems, MenuState, Blueprints);
			MenuState = new UserMenuState(Game, Menu_Components, Menu_Entities, GameState); GameState->m_MenuState = MenuState;

			TimeAndSpawn = new UserTimeAndSpawn(Game, Manager_Components, Manager_Entities, Manager_Systems, GameState, Blueprints);
			GameState->_Set_TimeAndSpawnPointer(TimeAndSpawn);
			FSM = new FiniteStateMachine(Game, Manager_Components, Manager_Entities, Manager_Systems, GameState);
			Manager_Systems->m_System_HealthAndAttack->m_GameState = GameState;
			Manager_Systems->m_System_Resources->m_GameState = GameState;


			// INITS AND SETTERS
			Game->_Set_InitialMouseAndCamera(std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0));
			GameState->_Set_PlayableScreen(Game->_Get_WindowDimensions(), std::make_pair(48, 16), std::make_pair(96, 96));
			MenuState->_Set_ButtonData(20, 60, 250, 0);
			GameState->m_NumberOfLevels = Manager_Systems->m_System_ImportData->_Get_NumberOfLevels();


			// INGAME OBJECTS
			{
				GameState->m_Mouse = Blueprints->_Create_MouseCursor();
				GameState->m_Camera = Blueprints->_Create_Camera(0.5f, -500.f, 500.f, -500.f, 500.f);
				GameState->m_UI_Background = Blueprints->_Create_UI_Background(Game->m_CameraTransform_Menu.first + (int)Game->_Get_WindowDimensions().first / 2, Game->m_CameraTransform_Menu.second + (int)Game->_Get_WindowDimensions().second / 2, resolution, Mapper_Resolutions);
				GameState->m_Player = Blueprints->_Create_Player(0, GameState->m_InitialGold, GameState->m_InitialMana, 99999, 99999);

				ResourcesComponent* PlayerResources = Manager_Components->_Get_ComponentPtrFromId(Manager_Entities->_Get_EntityById(GameState->m_Player)->_Get_ComponentIdFromEntityByType(user::ComponentType::RESOURCES), Manager_Components->m_Components_Resources);
				GameState->m_UI_ScoreText = Blueprints->_Create_Text((float)Game->_Get_WindowDimensions().first / 2, 26, false, 32, std::to_string(PlayerResources->m_Score).data(), "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, user::Layer::UI_TEXT);
				GameState->m_UI_GoldText = Blueprints->_Create_Text(37, 60, false, 14, std::to_string(PlayerResources->m_Gold_Current).data(), "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_LEFT, mfk::ColourList::WHITE_OPAQUE, user::Layer::UI_TEXT);
				GameState->m_UI_ManaText = Blueprints->_Create_Text(37, 90, false, 14, std::to_string(PlayerResources->m_Mana_Current).data(), "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_LEFT, mfk::ColourList::WHITE_OPAQUE, user::Layer::UI_TEXT);
				GameState->m_UI_KillCounter = Blueprints->_Create_Text((float)Game->_Get_WindowDimensions().first - 185, 25, false, 24, std::to_string(PlayerResources->m_Mana_Current).data(), "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_LEFT, mfk::ColourList::WHITE_OPAQUE, user::Layer::UI_TEXT);

				GameState->m_UI_Button_Ballista = Blueprints->_Create_UIButton(44, 141, 63, 63, 63, 63, "Assets/Sprites/UI/UI_Button_Ballista.bmp", user::UI_Button::BALLISTA, "", 14, 300, 0, std::make_pair(0, 23));
				GameState->m_UI_Button_WoodenBox = Blueprints->_Create_UIButton(44, 224, 63, 63, 63, 63, "Assets/Sprites/UI/UI_Button_Box.bmp", user::UI_Button::WOODEN_BOX, "", 14, 1000, 0, std::make_pair(0, 23));
				GameState->m_UI_Button_TarTrap = Blueprints->_Create_UIButton(44, 307, 63, 63, 63, 63, "Assets/Sprites/UI/UI_Button_TarTrap.bmp", user::UI_Button::TAR_TRAP, "", 14, 500, 0, std::make_pair(0, 23));
				GameState->m_UI_Button_SpikeTrap = Blueprints->_Create_UIButton(44, 390, 63, 63, 63, 63, "Assets/Sprites/UI/UI_Button_SpikeTrap.bmp", user::UI_Button::SPIKE_TRAP, "", 14, 1000, 0, std::make_pair(0, 23));
				GameState->m_UI_Button_HealSpell = Blueprints->_Create_UIButton(44, 473, 63, 63, 63, 63, "Assets/Sprites/UI/UI_Button_HealSpell.bmp", user::UI_Button::HEAL_SPELL, "", 14, 0, 10, std::make_pair(0, 23));
				GameState->m_UI_Button_FireballSpell = Blueprints->_Create_UIButton(44, 556, 63, 63, 63, 63, "Assets/Sprites/UI/UI_Button_FireballSpell.bmp", user::UI_Button::FIREBALL_SPELL, "", 14, 0, 30, std::make_pair(0, 23));

				GameState->m_UI_Button_Menu = Blueprints->_Create_UIButton((float)Game->_Get_WindowDimensions().first - 46, 55, 70, 20, 70, 20, "Assets/Sprites/UI/UI_Button_Menu.bmp", user::UI_Button::MENU, "MENU", 14, 0, 0, std::make_pair(0, 2));
				GameState->m_UI_Button_Cancel = Blueprints->_Create_UIButton((float)Game->_Get_WindowDimensions().first - 46 - (float)GameState->m_GargabeTransform.first, 90, 70, 20, 70, 20, "Assets/Sprites/UI/UI_Button_Cancel.bmp", user::UI_Button::CANCEL, "CANCEL", 14, 0, 0, std::make_pair(0, 2));

				GameState->m_Placement_Ballista = Blueprints->_Create_PlacementObject((float)GameState->m_GargabeTransform.first, (float)GameState->m_GargabeTransform.second, 40, 40, "Assets/Sprites/Placement/Placement_Ballista.bmp", user::Layer::PLACEMENT_OBJECT, 32, 32, 1, Shape::m_CollisionBox);
				GameState->m_Placement_WoodenBox = Blueprints->_Create_PlacementObject((float)GameState->m_GargabeTransform.first, (float)GameState->m_GargabeTransform.second, 36, 36, "Assets/Sprites/Placement/Placement_WoodenBox.bmp", user::Layer::PLACEMENT_OBJECT, 32, 32, 1, Shape::m_CollisionBox);
				GameState->m_Placement_TarTrap = Blueprints->_Create_PlacementObject((float)GameState->m_GargabeTransform.first, (float)GameState->m_GargabeTransform.second, 68, 68, "Assets/Sprites/Placement/Placement_TarTrap.bmp", user::Layer::PLACEMENT_OBJECT, 64, 64, 1, Shape::m_CollisionBox);
				GameState->m_Placement_SpikeTrap = Blueprints->_Create_PlacementObject((float)GameState->m_GargabeTransform.first, (float)GameState->m_GargabeTransform.second, 64, 64, "Assets/Sprites/Placement/Placement_SpikeTrap.bmp", user::Layer::PLACEMENT_OBJECT, 64, 64, 1, Shape::m_CollisionBox);
				GameState->m_Placement_HealSpell = Blueprints->_Create_PlacementObject((float)GameState->m_GargabeTransform.first, (float)GameState->m_GargabeTransform.second, 35, 35, "Assets/Sprites/Placement/Placement_HealSpell.bmp", user::Layer::PLACEMENT_OBJECT, 1, 1, 2, Shape::Sphere);
				GameState->m_Placement_FireballSpell = Blueprints->_Create_PlacementObject((float)GameState->m_GargabeTransform.first, (float)GameState->m_GargabeTransform.second, 66, 66, "Assets/Sprites/Placement/Placement_FireballSpell.bmp", user::Layer::PLACEMENT_OBJECT, 1, 1, 32, Shape::Sphere);
			}


			// MENU OBJECTS
			{
				MenuState->m_Mouse = Menu_Blueprints->_Create_MouseCursor();
				MenuState->m_Camera = Menu_Blueprints->_Create_Camera(0.f, -Game->m_CameraTransform_Menu.first + (int)Game->_Get_WindowDimensions().first / 2, Game->m_CameraTransform_Menu.first + (int)Game->_Get_WindowDimensions().first / 2, -Game->m_CameraTransform_Menu.second + (int)Game->_Get_WindowDimensions().second / 2, Game->m_CameraTransform_Menu.second + (int)Game->_Get_WindowDimensions().second / 2);
				MenuState->m_Background = Menu_Blueprints->_Create_Background(Game->m_CameraTransform_Menu.first + (int)Game->_Get_WindowDimensions().first / 2, Game->m_CameraTransform_Menu.second + (int)Game->_Get_WindowDimensions().second / 2, resolution, "Assets/Sprites/Menu/MenuBackground_Default_", Mapper_Resolutions);
				MenuState->m_Button_Title = Menu_Blueprints->_Create_MenuButton(0, 0, 750, 144, 750, 144, "Assets/Sprites/Menu/Title_750x144.bmp", 72, "TOWER DEFENSE", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::DARK_BROWN, std::make_pair(0, 3));
				MenuState->m_Button_Start = Menu_Blueprints->_Create_MenuButton(0, 0, 250, 60, 250, 60, "Assets/Sprites/Menu/Button_250x120.bmp", 24, "START GAME", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_Resume = Menu_Blueprints->_Create_MenuButton(0, 0, 250, 60, 250, 60, "Assets/Sprites/Menu/Button_250x120.bmp", 24, "RESUME", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_Quit = Menu_Blueprints->_Create_MenuButton(0, 0, 150, 60, 150, 60, "Assets/Sprites/Menu/Button_150x120.bmp", 24, "QUIT", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_Level = Menu_Blueprints->_Create_MenuButton(0, 0, 250, 60, 250, 60, "Assets/Sprites/Menu/Button_250x120.bmp", 24, " LEVEL  < 1 >", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_MotifLava = Menu_Blueprints->_Create_MenuButton(0, 0, 250, 60, 250, 60, "Assets/Sprites/Menu/Button_250x120.bmp", 24, "MOTIF   < LAVA >", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_LEFT, mfk::ColourList::WHITE_OPAQUE, std::make_pair(-110, 3));
				MenuState->m_Button_MotifValley = Menu_Blueprints->_Create_MenuButton(0, 0, 250, 60, 250, 60, "Assets/Sprites/Menu/Button_250x120.bmp", 24, "MOTIF < VALLEY >", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_LEFT, mfk::ColourList::WHITE_OPAQUE, std::make_pair(-110, 3));
				MenuState->m_Button_SelectLevel_ArrowLeft = Menu_Blueprints->_Create_MenuButton(0, 0, 47, 47, 47, 47, "Assets/Sprites/Menu/Button_Arrow_Left.bmp", 24, "", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_SelectLevel_ArrowRight = Menu_Blueprints->_Create_MenuButton(0, 0, 47, 47, 47, 47, "Assets/Sprites/Menu/Button_Arrow_Right.bmp", 24, "", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_SelectMotif_ArrowLeft = Menu_Blueprints->_Create_MenuButton(0, 0, 47, 47, 47, 47, "Assets/Sprites/Menu/Button_Arrow_Left.bmp", 24, "", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_SelectMotif_ArrowRight = Menu_Blueprints->_Create_MenuButton(0, 0, 47, 47, 47, 47, "Assets/Sprites/Menu/Button_Arrow_Right.bmp", 24, "", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Button_Restart = Menu_Blueprints->_Create_MenuButton(0, 0, 250, 60, 250, 60, "Assets/Sprites/Menu/Button_150x120.bmp", 24, "RESTART", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::WHITE_OPAQUE, std::make_pair(0, 3));
				MenuState->m_Text_WinOrLose = Menu_Blueprints->_Create_Text(0, 0, false, 48, "S.T.A.G.E  C.L.E.A.R.E.D", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::DARK_BROWN, user::Layer::UI_TEXT);
				MenuState->m_Text_Score = Menu_Blueprints->_Create_Text(0, 0, false, 48, "0", "Assets/Fonts/Minecraft.ttf", user::Alignment::MIDDLE_CENTRE, mfk::ColourList::DARK_BROWN, user::Layer::UI_TEXT);
			}
						

			// Populating the placement mapper
			{
				PlacementMapper.insert(std::make_pair(user::PlacementMode::PLACEMENT_BALLISTA, GameState->m_Placement_Ballista));
				PlacementMapper.insert(std::make_pair(user::PlacementMode::PLACEMENT_WOODENBOX, GameState->m_Placement_WoodenBox));
				PlacementMapper.insert(std::make_pair(user::PlacementMode::PLACEMENT_TARTRAP, GameState->m_Placement_TarTrap));
				PlacementMapper.insert(std::make_pair(user::PlacementMode::PLACEMENT_SPIKETRAP, GameState->m_Placement_SpikeTrap));
				PlacementMapper.insert(std::make_pair(user::PlacementMode::PLACEMENT_HEALSPELL, GameState->m_Placement_HealSpell));
				PlacementMapper.insert(std::make_pair(user::PlacementMode::PLACEMENT_FIREBALLSPELL, GameState->m_Placement_FireballSpell));
			}


			//Function pointers
			{
				Game->_Set_EventCallback(HandleEvents);
				Game->_Set_LogicCallback(HandleLogic);
				Game->_Set_RenderCallback(HandleRendering);
				Game->_Set_MenuEventCallback(HandleMenuEvents);
				Game->_Set_MenuLogicCallback(HandleMenuLogic);
				Game->_Set_MenuRenderCallback(HandleMenuRendering);
			}


			//Mainloop
			MenuState->_Set_MenuLayout_StartGameMenu(Game->_Get_WindowDimensions());
			Game->_RunGameLoop(bRestart);	
			ResourceManager::_Get_Instance()._ResetResources();
			CLEAR_MEMORY();
			SDL_Quit();
		}	

	return 0;	
}
