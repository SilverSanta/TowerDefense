// INCLUDES
#include "ComponentsManager.h"


// FUNCTION DEFINITIONS
void LegacyComponentsManager::_SortSpritesByLayer()
{
	if ((int)m_Components_AnimatedSprite.size() <= 1) { return; }

	auto* SpritesPtr = &m_Components_AnimatedSprite;
		
	for (int i = 1; i < (int)SpritesPtr->size(); i++)
	{
		auto key = SpritesPtr->at(i);
		int keyLayerIndex = (int)key.m_SpriteLayer;
		int j = i - 1;

		while (j >= 0 && (int)SpritesPtr->at(j).m_SpriteLayer > keyLayerIndex)
		{
			SpritesPtr->at(j + 1) = SpritesPtr->at(j);
			j = j - 1;
		}
		SpritesPtr->at(j + 1) = key;
	}
}
void LegacyComponentsManager::_SortLayerSortedSpritesByY()
{
	if ((int)m_Components_AnimatedSprite.size() <= 1) { return; }

	auto* SpritesPtr = &m_Components_AnimatedSprite;

	for (int i = 1; i < (int)SpritesPtr->size(); i++)
	{
		int j = i - 1;

		auto key = SpritesPtr->at(i);
		float keyYTransform = _Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(key.Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Components_Transform)->m_Y;
		bool conditions = (j >= 0 && _Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(SpritesPtr->at(j).Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Components_Transform)->m_Y > keyYTransform && SpritesPtr->at(j).m_SpriteLayer == key.m_SpriteLayer) ? (true) : (false);

		while (conditions == true) 
		{
			SpritesPtr->at(j + 1) = SpritesPtr->at(j);
			j = j - 1;
			conditions = (j >= 0 && _Get_ComponentPtrFromId(m_Manager_Entities->_Get_EntityById(SpritesPtr->at(j).Get_OwnerId())->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Components_Transform)->m_Y > keyYTransform && SpritesPtr->at(j).m_SpriteLayer == key.m_SpriteLayer) ? (true) : (false);
		}
		SpritesPtr->at(j + 1) = key;						
	}
}

void LegacyComponentsManager::_SortCollisionShapesByProfile()
{
	if ((int)m_Components_Collision.size() <= 1) { return; }

	auto* PtrToCollisions = &m_Components_Collision;

	for (int i = 1; i < (int)PtrToCollisions->size(); i++)
	{
		auto key = PtrToCollisions->at(i);
		int keyLayerIndex = (int)key.m_Profile;
		int j = i - 1;

		while (j >= 0 && (int)PtrToCollisions->at(j).m_Profile > keyLayerIndex)
		{
			PtrToCollisions->at(j + 1) = PtrToCollisions->at(j);
			j = j - 1;
		}
		PtrToCollisions->at(j + 1) = key;
	}
}


// USER-DEFINED
void LegacyComponentsManager::_DeleteComponents(std::unordered_map<user::ComponentType, uint64_t> IDsOfComponentsToBeDeleted)
{
	for (const auto& component : IDsOfComponentsToBeDeleted)
	{
		switch (component.first)
		{
		case user::ComponentType::ACTION:
			_RemoveComponent(m_Components_Action, component.second);
			break;
		case user::ComponentType::ANIMATEDSPRITE1:
		case user::ComponentType::ANIMATEDSPRITE2:
		case user::ComponentType::ANIMATEDSPRITE3:
		case user::ComponentType::ANIMATEDSPRITE4:
		case user::ComponentType::ANIMATEDSPRITE5:
			_RemoveComponent(m_Components_AnimatedSprite, component.second);
			break;
		case user::ComponentType::CELLGRID:
			_RemoveComponent(m_Components_CellGrid, component.second);
			break;
		case user::ComponentType::COLLISION1:
		case user::ComponentType::COLLISION2:
		case user::ComponentType::COLLISION3:
		case user::ComponentType::COLLISION4:
		case user::ComponentType::COLLISION5:
			_RemoveComponent(m_Components_Collision, component.second);
			break;
		case user::ComponentType::MOVEMENT:
			_RemoveComponent(m_Components_Movement, component.second);
			break;
		case user::ComponentType::STATE:
			_RemoveComponent(m_Components_State, component.second);
			break;
		case user::ComponentType::TRANSFORM:
			_RemoveComponent(m_Components_Transform, component.second);
			break;
		}
	}
}
void LegacyComponentsManager::_UpdateRepositories(uint64_t currenttime)
{
	_UpdateComponents(m_Components_Action, currenttime);
	_UpdateComponents(m_Components_AnimatedSprite, currenttime);
	_UpdateComponents(m_Components_CellGrid, currenttime);
	_UpdateComponents(m_Components_Collision, currenttime);
	_UpdateComponents(m_Components_Movement, currenttime);
	_UpdateComponents(m_Components_State, currenttime);
	_UpdateComponents(m_Components_Transform, currenttime);
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
	// USER-DEFINED
}




