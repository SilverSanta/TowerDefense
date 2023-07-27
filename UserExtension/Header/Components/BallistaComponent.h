#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class BallistaComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	BallistaComponent()
	{	
		//std::cout << "	 ATTACK created\n";
	}
	~BallistaComponent()
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
		mfk::FindObjectInRepoAndKillIt(this, m_BallistaRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<BallistaComponent> &repo, int dmg)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_BallistaRepository = &repo;

			// (2) DATA
			m_Damage = dmg;
		}
	}


public:
	// DATA
	int m_Damage;
	bool m_bActivated = true;

protected:
	// REPOSITORY
	std::vector<BallistaComponent>* m_BallistaRepository;
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

