#pragma once

#include "IComponent.h"


// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class ButtonComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	ButtonComponent()
	{			
		//std::cout << "	 BUTTON created\n";
	}
	~ButtonComponent()
	{
		//std::cout << "     BUTTON: #" << m_Id << " deleted\n";
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
		mfk::FindObjectInRepoAndKillIt(this, m_ButtonRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<ButtonComponent> &repo, user::UI_Button buttontype)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_ButtonRepository = &repo;

			// (2) DATA
			m_ButtonType = buttontype;
		}
	}


public:
	user::UI_Button m_ButtonType;

protected:
	// REPOSITORY
	std::vector<ButtonComponent>* m_ButtonRepository;
		

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
};

