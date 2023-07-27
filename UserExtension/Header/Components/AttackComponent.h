#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class AttackComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	AttackComponent()
	{	
		//std::cout << "	 ATTACK created\n";
	}
	~AttackComponent()
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
		mfk::FindObjectInRepoAndKillIt(this, m_AttackRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<AttackComponent> &repo, float meleedmg, float rangeddmg, float magicdmg, user::ProjectileType projectile)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_AttackRepository = &repo;

			// (2) DATA
			m_MeleeDmg = meleedmg;
			m_RangedDmg = rangeddmg;
			m_MagicDmg = magicdmg;
			m_ProjectileSpawned = projectile;
		}
	}


public:
	float m_MeleeDmg;
	float m_RangedDmg;
	float m_MagicDmg;
	user::ProjectileType m_ProjectileSpawned;

protected:
	// REPOSITORY
	std::vector<AttackComponent>* m_AttackRepository;
	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

