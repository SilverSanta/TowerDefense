#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class ProjectileComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	ProjectileComponent()
	{	
		//std::cout << "	 ATTACK created\n";
	}
	~ProjectileComponent()
	{
		//std::cout << "     ATTACK: #" << m_Id << " deleted\n";
	}


	//OVERRIDES
public:
	virtual void _Update(uint64_t currentTime) override
	{
		if (this != nullptr)
		{

		}
	}
	virtual void _Render(SDL_Renderer* renderer) override
	{
		if (this != nullptr)
		{

		}
	}
	virtual void _DeleteFromRepository() override
	{
		mfk::FindObjectInRepoAndKillIt(this, m_ProjectileRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<ProjectileComponent> &repo, user::ProjectileType projectiletype, int dmg)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_ProjectileRepository = &repo;

			// (2) DATA
			m_TypeOfProjectile = projectiletype;
			m_Damage = dmg;
		}
	}


public:
	// DATA
	user::ProjectileType m_TypeOfProjectile;
	int m_Damage;

protected:
	// REPOSITORY
	std::vector<ProjectileComponent>* m_ProjectileRepository;


	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

