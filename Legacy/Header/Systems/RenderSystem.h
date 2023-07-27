#pragma once

#include "UserNamespace.h"

// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class AnimatedSpriteComponent;
class TransformComponent;
class CollisionComponent;
class TextComponent;
struct SDL_Renderer;

class RenderSystem
{
public:
	RenderSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager);
	~RenderSystem();
	void _RenderSprite(SDL_Renderer* renderer, AnimatedSpriteComponent* Sprite, TransformComponent* CameraTransform);
	void _RenderAllSprites(SDL_Renderer* renderer, TransformComponent* CameraTransform);
	void _RenderAllSpritesByLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform);
	void _RenderAllSprites_UpToLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer spritelayer);
	void _RenderAllSprites_FromLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer spritelayer);
	void _RenderAllSprites_FromLayerToLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer firstlayer, user::Layer limitinglayer);

	void _RenderCollisionShape(SDL_Renderer* renderer, CollisionComponent* m_CollisionShape, TransformComponent* CameraTransform);
	void _RenderAllCollisionShapes(SDL_Renderer* renderer, TransformComponent* CameraTransform);

	void _RenderText(SDL_Renderer* renderer, TextComponent* m_Text, TransformComponent* CameraTransform);
	void _RenderAllTexts(SDL_Renderer* renderer, TransformComponent* CameraTransform);
	void _RenderAllTexts_FromLayerToLayer(SDL_Renderer* renderer, TransformComponent* CameraTransform, user::Layer firstlayer, user::Layer limitinglayer);

	void _RenderAllGrids(SDL_Renderer* renderer, TransformComponent* CameraTransform);
	

private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
};
