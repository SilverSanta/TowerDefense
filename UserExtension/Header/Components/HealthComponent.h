#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class HealthComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	HealthComponent()
	{	
		//std::cout << "	 HEALTH created\n";
	}
	~HealthComponent()
	{
		//std::cout << "     HEALTH: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_HealthRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<HealthComponent> &repo, int maxhealth)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_HealthRepository = &repo;

			// (2) DATA
			m_MaxHealth = maxhealth;
			m_CurrentHealth = maxhealth;
		}
	}


public:
	int m_CurrentHealth;
	int m_MaxHealth;

protected:
	// REPOSITORY
	std::vector<HealthComponent>* m_HealthRepository;
	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

