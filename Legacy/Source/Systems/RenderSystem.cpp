#pragma once

#include "RenderSystem.h"

#include "EntitiesManager.h"
#include "UserExtension.h"


RenderSystem::RenderSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
}
RenderSystem::~RenderSystem(){}


void RenderSystem::_RenderSprite(SDL_Renderer* renderer, AnimatedSpriteComponent* Sprite, TransformComponent* CameraTransform)
{	
	Entity* Owner = m_Manager_Entities->_Get_EntityById(Sprite->Get_OwnerId());
	TransformComponent* Transform = m_Manager_Components->_Get_ComponentPtrFromId(Owner->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	if (Transform != nullptr)
	{
		if (Transform->m_bSusceptibleToCameraMovement == true)
		{
			Sprite->m_FrameInGame.x = (int)Transform->m_X + Sprite->m_OffsetFromOrigin.first - (int)CameraTransform->m_X;
			Sprite->m_FrameInGame.y = (int)Transform->m_Y + Sprite->m_OffsetFromOrigin.second - (int)CameraTransform->m_Y;

			Sprite->_Render(renderer);

			Sprite->m_FrameInGame.x += (int)CameraTransform->m_X;
			Sprite->m_FrameInGame.y += (int)CameraTransform->m_Y;
		}	
		else
		{
			Sprite->m_FrameInGame.x = (int)Transform->m_X + Sprite->m_OffsetFromOrigin.first;
			Sprite->m_FrameInGame.y = (int)Transform->m_Y + Sprite->m_OffsetFromOrigin.second;

			Sprite->_Render(renderer);
		}
	}
}
void RenderSystem::_RenderAllSprites(SDL_Renderer* renderer, TransformComponent* CameraTransform)
{
	for (auto& SpriteObj : m_Manager_Components->m_Components_AnimatedSprite)
	{
		_RenderSprite(renderer, &SpriteObj, CameraTransform);
	}
}
void RenderSystem::_RenderAllSpritesByLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform)
{
	for (int i = 0; i < (int)user::Layer::_COUNT; i++)
	{
		for (auto& SpriteObj : m_Manager_Components->m_Components_AnimatedSprite)
		{
			if ((int)SpriteObj.m_SpriteLayer == i)
			{
				_RenderSprite(renderer, &SpriteObj, CameraTransform);
			}
		}
	}
}
void RenderSystem::_RenderAllSprites_UpToLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer spritelayer)
{
	// render all until the specified layer is found -> stop then

	for (auto& SpriteObj : m_Manager_Components->m_Components_AnimatedSprite)
	{
		if ((int)SpriteObj.m_SpriteLayer < (int)spritelayer)
		{
			_RenderSprite(renderer, &SpriteObj, CameraTransform);
		}
		else
		{
			return;
		}
	}	
}
void RenderSystem::_RenderAllSprites_FromLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer spritelayer)
{
	// locate the correct layer and go from there until the end
	int currentspriteindex = 0;

	for (int i = 0; i < (int)m_Manager_Components->m_Components_AnimatedSprite.size(); i++)
	{
		if ((int)m_Manager_Components->m_Components_AnimatedSprite.at(i).m_SpriteLayer < (int)spritelayer)
		{
			currentspriteindex++;
		}
		else
		{
			break;
		}
	} 
	// render from there
	for (int i = currentspriteindex; i < (int)m_Manager_Components->m_Components_AnimatedSprite.size(); i++)
	{
		_RenderSprite(renderer, &m_Manager_Components->m_Components_AnimatedSprite.at(i), CameraTransform);
	}
}
void RenderSystem::_RenderAllSprites_FromLayerToLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer firstlayer, user::Layer limitinglayer)
{
	// locate the correct layer and go from there until the end
	int currentspriteindex = 0;

	for (int i = 0; i < (int)m_Manager_Components->m_Components_AnimatedSprite.size(); i++)
	{
		if ((int)m_Manager_Components->m_Components_AnimatedSprite.at(i).m_SpriteLayer < (int)firstlayer)
		{
			currentspriteindex++;
		}
		else
		{
			break;
		}
	}

	// render from there up to
	for (int i = currentspriteindex; i < (int)m_Manager_Components->m_Components_AnimatedSprite.size(); i++)
	{
		if ((int)m_Manager_Components->m_Components_AnimatedSprite.at(i).m_SpriteLayer < (int)limitinglayer)
		{
			_RenderSprite(renderer, &m_Manager_Components->m_Components_AnimatedSprite.at(i), CameraTransform);
		}		
		else
		{
			return;
		}
	}
}

void RenderSystem::_RenderCollisionShape(SDL_Renderer* renderer, CollisionComponent* m_CollisionShape, TransformComponent* CameraTransform)
{		
	Entity* Owner = m_Manager_Entities->_Get_EntityById(m_CollisionShape->Get_OwnerId());
	TransformComponent* Transform = m_Manager_Components->_Get_ComponentPtrFromId(Owner->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	if (m_CollisionShape->m_CollisionShape == Shape::m_CollisionBox)
	{
		m_CollisionShape->m_CollisionBox.x -= (int)CameraTransform->m_X;
		m_CollisionShape->m_CollisionBox.y -= (int)CameraTransform->m_Y;

		if (m_CollisionShape->bShowShape == true)
		{
			m_CollisionShape->_Render(renderer);
		}

		m_CollisionShape->m_CollisionBox.x += (int)CameraTransform->m_X;
		m_CollisionShape->m_CollisionBox.y += (int)CameraTransform->m_Y;
	}
	else if (m_CollisionShape->m_CollisionShape == Shape::Sphere)
	{
		m_CollisionShape->m_CollisionSphere.m_X -= (int)CameraTransform->m_X;
		m_CollisionShape->m_CollisionSphere.m_Y -= (int)CameraTransform->m_Y;
		m_CollisionShape->m_CollisionSphere.Update();

		if (m_CollisionShape->bShowShape == true)
		{
			m_CollisionShape->_Render(renderer);
		}

		m_CollisionShape->m_CollisionSphere.m_X += (int)CameraTransform->m_X;
		m_CollisionShape->m_CollisionSphere.m_Y += (int)CameraTransform->m_Y;
		m_CollisionShape->m_CollisionSphere.Update();
	}
	
}
void RenderSystem::_RenderAllCollisionShapes(SDL_Renderer* renderer, TransformComponent* CameraTransform)
{
	for (auto& Shape : m_Manager_Components->m_Components_Collision) { _RenderCollisionShape(renderer, &Shape, CameraTransform); }
}

void RenderSystem::_RenderText(SDL_Renderer* renderer, TextComponent* m_Text, TransformComponent* CameraTransform)
{
	Entity* Owner = m_Manager_Entities->_Get_EntityById(m_Text->Get_OwnerId());
	TransformComponent* Transform = m_Manager_Components->_Get_ComponentPtrFromId(Owner->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Manager_Components->m_Components_Transform);

	if (Transform != nullptr)
	{
		std::pair<int, int> AlignmentOffset;
		int w = m_Text->m_Text_Rectangle.w;
		int h = m_Text->m_Text_Rectangle.h;

		switch (m_Text->m_Position)
		{
		case user::Alignment::TOP_LEFT:
			AlignmentOffset = std::make_pair(0, 0);
			break;
		case user::Alignment::TOP_CENTRE:
			AlignmentOffset = std::make_pair(-w / 2, 0);
			break;
		case user::Alignment::TOP_RIGHT:
			AlignmentOffset = std::make_pair(- w, 0);
			break;
		case user::Alignment::MIDDLE_LEFT:
			AlignmentOffset = std::make_pair(0, - h / 2);
			break;
		case user::Alignment::MIDDLE_CENTRE:
			AlignmentOffset = std::make_pair(-w / 2, -h / 2);
			break;
		case user::Alignment::MIDDLE_RIGHT:
			AlignmentOffset = std::make_pair(-w, -h / 2);
			break;
		case user::Alignment::BOT_LEFT:
			AlignmentOffset = std::make_pair(0, -h);
			break;
		case user::Alignment::BOT_CENTRE:
			AlignmentOffset = std::make_pair(-w / 2, -h);
			break;
		case user::Alignment::BOT_RIGHT:
			AlignmentOffset = std::make_pair(-w, -h);
			break;
		}

		if (Transform->m_bSusceptibleToCameraMovement == true)
		{
			m_Text->m_Text_Rectangle.x = (int)Transform->m_X + m_Text->m_OffsetFromOrigin.first + AlignmentOffset.first - (int)CameraTransform->m_X;
			m_Text->m_Text_Rectangle.y = (int)Transform->m_Y + m_Text->m_OffsetFromOrigin.second + AlignmentOffset.second - (int)CameraTransform->m_Y;

			m_Text->_Render(renderer);

			m_Text->m_Text_Rectangle.x += (int)CameraTransform->m_X;
			m_Text->m_Text_Rectangle.y += (int)CameraTransform->m_Y;
		}		
		else
		{
			m_Text->m_Text_Rectangle.x = (int)Transform->m_X + m_Text->m_OffsetFromOrigin.first + AlignmentOffset.first;
			m_Text->m_Text_Rectangle.y = (int)Transform->m_Y + m_Text->m_OffsetFromOrigin.second + AlignmentOffset.second;

			m_Text->_Render(renderer);
		}
	}
}
void RenderSystem::_RenderAllTexts(SDL_Renderer* renderer, TransformComponent* CameraTransform)
{
	for (auto& TextObj : m_Manager_Components->m_Components_Text)
	{
		_RenderText(renderer, &TextObj, CameraTransform);
	}
}
void RenderSystem::_RenderAllTexts_FromLayerToLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer firstlayer, user::Layer limitinglayer)
{
	// locate the correct layer and go from there until the end
	int currentspriteindex = 0;

	for (int i = 0; i < (int)m_Manager_Components->m_Components_Text.size(); i++)
	{
		if ((int)m_Manager_Components->m_Components_Text.at(i).m_TextLayer < (int)firstlayer)
		{
			currentspriteindex++;
		}
		else
		{
			break;
		}
	}

	// render from there up to
	for (int i = currentspriteindex; i < (int)m_Manager_Components->m_Components_Text.size(); i++)
	{
		if ((int)m_Manager_Components->m_Components_Text.at(i).m_TextLayer < (int)limitinglayer)
		{
			_RenderText(renderer, &m_Manager_Components->m_Components_Text.at(i), CameraTransform);
		}
		else
		{
			return;
		}
	}
}

void RenderSystem::_RenderAllGrids(SDL_Renderer* renderer, TransformComponent* CameraTransform)
{
	for (auto& Grid : m_Manager_Components->m_Components_CellGrid)
	{
		Entity* Ent = m_Manager_Entities->_Get_EntityById(Grid.Get_OwnerId());
		uint64_t TransformId = Ent->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM);
		if (TransformId != NULL)
		{
			TransformComponent* TransformPtr = m_Manager_Components->_Get_ComponentPtrFromId(TransformId, m_Manager_Components->m_Components_Transform);

			Grid.m_X = TransformPtr->m_X - (int)CameraTransform->m_X;
			Grid.m_Y = TransformPtr->m_Y - (int)CameraTransform->m_Y;

			Grid._Render(renderer);

			Grid.m_X += (int)CameraTransform->m_X;
			Grid.m_Y += (int)CameraTransform->m_Y;
		}
	}
}