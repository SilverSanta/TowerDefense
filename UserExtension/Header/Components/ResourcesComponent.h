#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class ResourcesComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	ResourcesComponent()
	{	
		//std::cout << "	 RESOURCES created\n";
	}
	~ResourcesComponent()
	{
		//std::cout << "     RESOURCES: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_ResourcesRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<ResourcesComponent> &repo, int score, int goldcurrent, int manacurrent, int goldmax, int manamax)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_ResourcesRepository = &repo;

			// (2) DATA
			m_Score = score;

			m_Gold_Max = goldmax;
			m_Mana_Max = manamax;

			m_Gold_Current = std::clamp(goldcurrent, 0, m_Gold_Max);
			m_Mana_Current = std::clamp(manacurrent, 0, m_Mana_Max);			
		}
	}

public:
	// DATA
	int m_Score;
	int m_Gold_Current;
	int m_Gold_Max;
	int m_Mana_Current;
	int m_Mana_Max;

protected:
	// REPOSITORY
	std::vector<ResourcesComponent>* m_ResourcesRepository;



	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
	friend class ResourcesSystem;
};

