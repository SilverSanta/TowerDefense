#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class AIComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	AIComponent(){}
	~AIComponent(){}


	//OVERRIDES
public:
	virtual void _Update(uint64_t currentTime) override
	{
		if (this != nullptr)
		{
			m_Time_Current = currentTime;
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
		mfk::FindObjectInRepoAndKillIt(this, m_AIRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<AIComponent> &repo, float intervalbetweendecisions)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_AIRepository = &repo;

			// (2) DATA
			m_IntervalBetweenDecisions = intervalbetweendecisions;
		}
	}


public:

protected:
	// REPOSITORY
	std::vector<AIComponent>* m_AIRepository;
	// DATA

	std::pair<int, int> m_TargetNodeCoordinates = std::make_pair(0, 0);
	bool m_bAIIsNeededInGame = true;
	uint64_t m_TargetEntityId = NULL;

	uint64_t m_Time_Current;
	uint64_t m_Time_LastDecisionStartTime;
	float m_IntervalBetweenDecisions;

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
	friend class FiniteStateMachine;
};

