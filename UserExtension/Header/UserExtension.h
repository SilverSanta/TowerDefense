#pragma once

class MyFramework;



// LEGACY INCLUDES
#include "ComponentsManager.h"
#include "SystemsManager.h"
#include "UserNamespace.h"


// USER COMPONENTS
#include "AIComponent.h"
#include "AttackComponent.h"
#include "BallistaComponent.h"
#include "BarricadeComponent.h"
#include "ButtonComponent.h"
#include "CameraComponent.h"
#include "EnemyComponent.h"
#include "HealthComponent.h"
#include "NodeComponent.h"
#include "PathfindingComponent.h"
#include "ProjectileComponent.h"
#include "ResourcesComponent.h"
#include "TestComponent.h"
#include "TextComponent.h"
#include "TimeComponent.h"
#include "TrapComponent.h"


// USER SYSTEMS
#include "TestSystem.h"
#include "CameraSystem.h"
#include "ImportDataSystem.h"
#include "ResourcesSystem.h"
#include "HealthAndAttackSystem.h"
#include "PathfindingSystem.h"



// USER COMPONENTS MANAGER
class ComponentsManager :public LegacyComponentsManager
{
public:
	ComponentsManager(uint16_t maxentities, EntitiesManager* entitiesmanager) : LegacyComponentsManager(maxentities, entitiesmanager)
	{
		m_MaxEntities = maxentities;

		m_Components_Test.reserve(m_MaxEntities);
		m_Components_Camera.reserve(m_MaxEntities);
		m_Components_Attack.reserve(m_MaxEntities);
		m_Components_Trap.reserve(m_MaxEntities);
		m_Components_Text.reserve(m_MaxEntities);
		m_Components_Button.reserve(m_MaxEntities);
		m_Components_Resources.reserve(m_MaxEntities);
		m_Components_Pathfinding.reserve(m_MaxEntities);
		m_Components_Barricade.reserve(m_MaxEntities);

		// USER-DEFINED
		// USER-DEFINED		
		// USER-DEFINED		
		// USER-DEFINED		
		// USER-DEFINED		
		// USER-DEFINED		
		// USER-DEFINED		
	}
	~ComponentsManager()
	{
		m_Components_AI.clear();
		m_Components_Action.clear();
		m_Components_AnimatedSprite.clear();
		m_Components_CellGrid.clear();
		m_Components_Collision.clear();
		m_Components_Movement.clear();
		m_Components_State.clear();
		m_Components_Transform.clear();
		m_Components_Attack.clear();
		m_Components_Button.clear();
		m_Components_Camera.clear();
		m_Components_Health.clear();
		m_Components_Node.clear();
		m_Components_Pathfinding.clear();
		m_Components_Resources.clear();
		m_Components_Test.clear();
		m_Components_Trap.clear();
		m_Components_Text.clear();
		m_Components_Barricade.clear();	
		m_Components_Enemy.clear();	
		m_Components_Time.clear();	
		m_Components_Ballista.clear();	
		m_Components_Projectile.clear();	
	}

	template <class T>
	T* _CreateComponent(Entity* owner, std::vector<T>& TComponents, user::ComponentType comptype)
	{
		// (1) Check if this is available in entity;		
		uint64_t ComponentID = owner->_GenerateComponentId(comptype);
		bool bIsAvailable = (owner->_Get_ComponentIdFromEntityByType(comptype) == NULL) ? (true) : (false);

		// (2) if available - emplace in repository, then create an interfaced pointer to that location in memory 
		if (bIsAvailable)
		{
			T* NewComponent = new T;
			IComponent* NewComponentInterfaced = static_cast<IComponent*>(NewComponent);

			NewComponentInterfaced->m_OwnerId = owner->_Get_EntityId();
			NewComponentInterfaced->m_Id = ComponentID;
			NewComponentInterfaced->m_ComponentsManager = this;
			NewComponentInterfaced->m_Type = comptype;

			// (3) Place in the repository
			TComponents.emplace_back(*NewComponent);
			owner->_AddComponentToEntity(NewComponentInterfaced);

			T* ValidPtr = this->_Get_ComponentPtrFromId(ComponentID, TComponents);

			NewComponentInterfaced->~IComponent();
			return ValidPtr;
		}
		else
		{
			return nullptr;
		}
	}

	void _DeleteComponents(std::unordered_map<user::ComponentType, uint64_t> IDsOfComponentsToBeDeleted) override;
	void _UpdateRepositories(uint64_t currenttime) override;

	void _SortTextByLayer();

public:
	std::vector<AIComponent> m_Components_AI;
	std::vector<AttackComponent> m_Components_Attack;
	std::vector<BallistaComponent> m_Components_Ballista;
	std::vector<BarricadeComponent> m_Components_Barricade;
	std::vector<ButtonComponent> m_Components_Button;
	std::vector<CameraComponent> m_Components_Camera;
	std::vector<EnemyComponent> m_Components_Enemy;
	std::vector<HealthComponent> m_Components_Health;
	std::vector<NodeComponent> m_Components_Node;
	std::vector<PathfindingComponent> m_Components_Pathfinding;
	std::vector<ProjectileComponent> m_Components_Projectile;
	std::vector<ResourcesComponent> m_Components_Resources;
	std::vector<TestComponent> m_Components_Test;
	std::vector<TextComponent> m_Components_Text;
	std::vector<TimeComponent> m_Components_Time;
	std::vector<TrapComponent> m_Components_Trap;


	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
};

// USER SYSTEMS MANAGER
class SystemsManager : public LegacySystemsManager
{
public:
	SystemsManager(EntitiesManager* entitiesmanager, ComponentsManager* componentsmanager, UserBlueprints* blueprints);
	~SystemsManager(){}

private:


public:
	TestSystem* m_System_Test;
	CameraSystem* m_System_Camera;
	ImportAndProcessDataSystem* m_System_ImportData;
	ResourcesSystem* m_System_Resources;
	HealthAndAttackSystem* m_System_HealthAndAttack;
	PathfindingSystem* m_System_Pathfinding;

	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED
	// USED-DEFINED

	UserBlueprints* m_Blueprints;
	
};



