#pragma once
#include <iostream>

// FORWARD DECLARATIONS
class EntitiesManager;
class ComponentsManager;
class AnimatedSpriteComponent;
struct SDL_Renderer;

class AnimationSystem
{
public:
	AnimationSystem(ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager);
	~AnimationSystem();


public:
	void _Update_AllAnimationsToState();
	void _NextFrame_AllSprites();
	void _SubstituteSprite(SDL_Renderer* renderer, AnimatedSpriteComponent* Sprite, std::string filepath);
	void _SetTextureTransparency(SDL_Renderer* renderer, AnimatedSpriteComponent* Sprite, bool istransparent);
private:
	void _NextFrame(AnimatedSpriteComponent* Sprite);
	void _ChangeAnimationTo(AnimatedSpriteComponent* SpritePtr, int animationindex);
	void _MapAnimationToState(AnimatedSpriteComponent* Sprite);
	void _Set_FrameIndex(AnimatedSpriteComponent* SpritePtr, uint8_t index);
	void _Set_AnimationIndex(AnimatedSpriteComponent* SpritePtr, uint8_t index);


private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;

	friend class HealthAndAttackSystem;
};
