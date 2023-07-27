#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class NodeComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	NodeComponent()
	{	
		//std::cout << "	 NODE created\n";
	}
	~NodeComponent()
	{
		//std::cout << "     NODE: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_NodeRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<NodeComponent> &repo)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_NodeRepository = &repo;

			// (2) DATA
			m_bIsPassableByUnits = true;

		}
	}


public:

	bool m_bIsPassableByUnits;
	std::vector<uint64_t> m_NeighbouringNodesID;

protected:
	// REPOSITORY
	std::vector<NodeComponent>* m_NodeRepository;
	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

