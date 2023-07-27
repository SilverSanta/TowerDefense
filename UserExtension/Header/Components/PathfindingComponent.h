#pragma once



#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class PathfindingComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	PathfindingComponent()
	{	
		//std::cout << "	 PATHFINDING created\n";
	}
	~PathfindingComponent()
	{
		//std::cout << "     PATHFINDING: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_PathfindingRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<PathfindingComponent> &repo)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_PathfindingRepository = &repo;

			// (2) DATA
		}
	}


private:
	std::vector<std::pair<int, int>> m_Path_Ideal; // Used if Path_WithObstacles does not allow to reach destination (blockades will be destroyed)
	std::vector<std::pair<int, int>> m_Path_WithObstacles; // Used by default - allows user to diverge the path of enemies through blockades


protected:
	// REPOSITORY
	std::vector<PathfindingComponent>* m_PathfindingRepository;
	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
	friend class PathfindingSystem;
};

