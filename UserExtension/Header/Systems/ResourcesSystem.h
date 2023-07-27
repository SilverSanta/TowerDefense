#pragma once
#include <iostream>
#include "mfk.h"
#include "UserNamespace.h"
#include <unordered_map>

// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class StateSystem;
class StateComponent;
class ResourcesComponent;
class TextComponent;
struct SDL_Renderer;
class UserGameState;

class ResourcesSystem
{
public:
	ResourcesSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem);
	~ResourcesSystem();

	void _Score_AddOrSubtract(ResourcesComponent* PlayerResources, ResourcesComponent* ScorerResources, TextComponent* ScoreDisplayText, SDL_Renderer* renderer);

	void _Gold_Add(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* GoldDisplayText, SDL_Renderer* renderer);
	bool _Gold_Subtract(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* GoldDisplayText, SDL_Renderer* renderer);
	void _Mana_Add(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* ManaDisplayText, SDL_Renderer* renderer);
	bool _Mana_Subtract(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources, TextComponent* ManaDisplayText, SDL_Renderer* renderer);

	void _MaxMana_AddOrSubtract(ResourcesComponent* PlayerResources, int increasevalue, SDL_Renderer* renderer);

	bool _Gold_CheckForSufficientFunds(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources);
	bool _Mana_CheckForSufficientFunds(ResourcesComponent* PlayerResources, ResourcesComponent* ObjectResources);

	void _Score_UpdateDisplayText(ResourcesComponent* PlayerResources, TextComponent* ScoreDisplayText, SDL_Renderer* renderer);
	void _Gold_UpdateDisplayText(ResourcesComponent* PlayerResources, TextComponent* GoldDisplayText, SDL_Renderer* renderer);
	void _Mana_UpdateDisplayText(ResourcesComponent* PlayerResources, TextComponent* ManaDisplayText, SDL_Renderer* renderer);


	void _CheckAllButtonsForState(uint64_t m_Player);

public:
	UserGameState* m_GameState;

private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	StateSystem* m_System_State;

};
