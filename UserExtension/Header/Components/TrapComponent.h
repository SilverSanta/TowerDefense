#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class TrapComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	TrapComponent()
	{	
		//std::cout << "	 ATTACK created\n";
	}
	~TrapComponent()
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
		mfk::FindObjectInRepoAndKillIt(this, m_TrapRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<TrapComponent> &repo, float trapdmg, float trapslow, user::TrapType trap, bool bactivated)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_TrapRepository = &repo;

			// (2) DATA
			m_TrapDmg = trapdmg;
			m_TrapSlow = trapslow;
			m_Trap = trap;
			m_bActivated = bactivated;
		}
	}


public:
	float m_TrapDmg;
	float m_TrapSlow;
	user::TrapType m_Trap;
	bool m_bActivated;

protected:
	// REPOSITORY
	std::vector<TrapComponent>* m_TrapRepository;
	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

