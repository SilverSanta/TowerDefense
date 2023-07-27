#pragma once

#include "IComponent.h"

// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class BarricadeComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	BarricadeComponent()
	{			
		//td::cout << "BARRICADE created\n";
	}
	~BarricadeComponent()
	{
		//std::cout << "BARRICADE: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_BarricadeRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<BarricadeComponent> &repo, uint64_t nodecomponentid)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_BarricadeRepository = &repo;

			// (2) DATA
			m_NodeComponentId = nodecomponentid;
		}
	}


public:
	uint64_t m_NodeComponentId;

protected:
	// REPOSITORY
	std::vector<BarricadeComponent>* m_BarricadeRepository;
	
	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

