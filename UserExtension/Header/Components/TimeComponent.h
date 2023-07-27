#pragma once

#include "SDL.h"
#include "IComponent.h"
#include "ResourceManager.h"

// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class TimeComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	TimeComponent()
	{	
		//std::cout << "	 TIME created\n";
	}
	~TimeComponent()
	{
		//std::cout << "     TIME: #" << m_Id << " deleted\n";
	}


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
		mfk::FindObjectInRepoAndKillIt(this, m_TimeRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<TimeComponent>& repo, float effectduration, uint64_t timecurrent, uint64_t timestart, bool bgetsdestroyedafteraxpiration)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_TimeRepository = &repo;
		

			// (2) DATA
			m_EffectDuration = effectduration;
			m_DurationLeft = m_EffectDuration;
			m_Time_CountStart = timecurrent;
			m_Time_Current = timecurrent;
			m_bIsDestroyedWhenDurationEnds = bgetsdestroyedafteraxpiration;
		}
	}
	
	
	

public:
	// REPOSITORY
	std::vector<TimeComponent>* m_TimeRepository;


	// DATA
	uint64_t m_Time_Current; // gets current time
	float m_EffectDuration;
	float m_DurationLeft;
	uint64_t m_Time_CountStart;
	bool m_bIsDestroyedWhenDurationEnds;
	user::TimerType m_TypeOfTimer = user::TimerType::_NONE;



	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
	friend class RenderSystem;
};

