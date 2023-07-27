#pragma once
#include <iostream>
#include "mfk.h"
#include "UserNamespace.h"
#include <unordered_map>
#include <vector>
// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class StateSystem;
class AnimationSystem;
class StateComponent;
class ResourcesComponent;
class TextComponent;
struct SDL_Renderer;
class Entity;
class UserGameState;
class ResourcesSystem;
class MyFramework;


class HealthAndAttackSystem
{
public:
	HealthAndAttackSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem, AnimationSystem* animationsystem, ResourcesSystem* resourcessystem);
	~HealthAndAttackSystem();

	void _ApplyDamage(Entity* DamagedObject, int dmgvalue, std::vector<uint64_t> &m_EntitiesToBeDeleted, UserGameState* gamestate, SDL_Renderer* renderer);
	void _ApplyHeal(Entity* HealedObject, int healvalue);
	
private:
	void _Update_HealthBar(Entity* entity);

public:
	UserGameState* m_GameState;
	MyFramework* m_Game;
private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	StateSystem* m_System_State;
	AnimationSystem* m_System_Animation;
	ResourcesSystem* m_System_Resources;
};
