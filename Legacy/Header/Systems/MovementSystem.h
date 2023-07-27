#pragma once
#include <iostream>
#include "mfk.h"
#include "UserNamespace.h"

// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class TransformComponent;
class AnimatedSpriteComponent;
class MovementComponent;
class StateComponent;
class StateSystem;
class ActionSystem;


class MovementSystem
{
public:
	MovementSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, StateSystem* statesystem, ActionSystem* actionsystem);
	~MovementSystem();


public:
	void _MoveAll(uint64_t deltaTime);
	static float _Get_AngleBetweenPoints(float x1, float y1, float x2, float y2);
	static void _Set_Angle(TransformComponent* TransformPtr, AnimatedSpriteComponent* SpritePtr, float angle);
	static void _Set_Angle(TransformComponent* TransformPtr, AnimatedSpriteComponent* SpritePtr, mfk::NormalVector2D vectorangle);


private:
	user::Direction _Get_DirectionFromMovementVector(uint64_t movementcomponentid);
	void _ApplyMovement(MovementComponent* MovementPtr, TransformComponent* TransformPtr, StateComponent* StatePtr, uint64_t deltaTime);
	void _Update_MovementParameters(MovementComponent* MovementPtr, user::SubState substate);
	
	
private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	StateSystem* m_System_State;
	ActionSystem* m_System_Action;
};
