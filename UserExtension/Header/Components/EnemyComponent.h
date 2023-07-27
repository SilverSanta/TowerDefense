#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class EnemyComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	EnemyComponent()
	{	
		//std::cout<< "Enemy created\n";
	}
	~EnemyComponent()
	{
		//std::cout << "     Enemy: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_EnemyRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<EnemyComponent> &repo, user::EnemyType typeofenemy)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_EnemyRepository = &repo;

			// (2) DATA
			m_TypeOfEnemy = typeofenemy;
		}
	}


public:
	user::EnemyType m_TypeOfEnemy;

protected:
	// REPOSITORY
	std::vector<EnemyComponent>* m_EnemyRepository;
	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

