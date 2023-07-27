#pragma once

#include <algorithm>

#include "UserBlueprints.h"
#include "UserExtension.h"
#include "ECS_Framework.h"
#include "ImportDataSystem.h"


// MAPPERS (STATE TO ANIMATION INDEX)
std::unordered_map<int, int> Mapper_MonsterUnit{

std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT),1),
std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_LEFT),2),
std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_DOWN),3),
std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_UP),4),

std::make_pair(StateSystem::_GenerateTotalState(user::State::MOVING, user::SubState::MOVING_WALKING, user::Direction::Facing_RIGHT),5),
std::make_pair(StateSystem::_GenerateTotalState(user::State::MOVING, user::SubState::MOVING_WALKING, user::Direction::Facing_LEFT),6),
std::make_pair(StateSystem::_GenerateTotalState(user::State::MOVING, user::SubState::MOVING_WALKING, user::Direction::Facing_DOWN),7),
std::make_pair(StateSystem::_GenerateTotalState(user::State::MOVING, user::SubState::MOVING_WALKING, user::Direction::Facing_UP),8),

std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_ATTACKING, user::Direction::Facing_RIGHT),9),
std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_ATTACKING, user::Direction::Facing_LEFT),10),
std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_ATTACKING, user::Direction::Facing_DOWN),11),
std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_ATTACKING, user::Direction::Facing_UP),12),

std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_RIGHT),13),
std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_LEFT),14),
std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_DOWN),13),
std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_UP),14),

std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_RIGHT),15),
std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_LEFT),16),
std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_DOWN),15),
std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_UP),16)
};
std::unordered_map<int, int> Mapper_Spiketrap{

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_LEFT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_DOWN),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_UP),1),

	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SPRINGING_TRAP, user::Direction::Facing_RIGHT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SPRINGING_TRAP, user::Direction::Facing_LEFT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SPRINGING_TRAP, user::Direction::Facing_DOWN),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SPRINGING_TRAP, user::Direction::Facing_UP),2),
};
std::unordered_map<int, int> Mapper_UIButton{

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_RIGHT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_LEFT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_DOWN),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_UP),1),

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_RIGHT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_LEFT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_DOWN),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_INPHASE, user::Direction::Facing_UP),2),

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_RIGHT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_LEFT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_DOWN),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_SUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_UP),3),

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_RIGHT),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_LEFT),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_DOWN),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_INSUFFICIENTFUNDS_AND_OUTOFPHASE, user::Direction::Facing_UP),4),
};
std::unordered_map<int, int> Mapper_PassiveAnimation{

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT),1),
};
std::unordered_map<int, int> Mapper_Node{

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_NODE_INVISIBLE, user::Direction::Facing_RIGHT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_NODE_AVAILABLE, user::Direction::Facing_RIGHT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_NODE_UNAVAILABLE, user::Direction::Facing_RIGHT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_NODE_PATH, user::Direction::Facing_RIGHT),4),
};
std::unordered_map<int, int> Mapper_Ballista{

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_LEFT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_UP),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_DOWN),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SHOOTING, user::Direction::Facing_RIGHT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SHOOTING, user::Direction::Facing_LEFT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SHOOTING, user::Direction::Facing_UP),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::TAKING_ACTION, user::SubState::ACTION_SHOOTING, user::Direction::Facing_DOWN),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::STATUS_EFFECT, user::SubState::STATUS_RELOADING, user::Direction::Facing_RIGHT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::STATUS_EFFECT, user::SubState::STATUS_RELOADING, user::Direction::Facing_LEFT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::STATUS_EFFECT, user::SubState::STATUS_RELOADING, user::Direction::Facing_UP),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::STATUS_EFFECT, user::SubState::STATUS_RELOADING, user::Direction::Facing_DOWN),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_RIGHT),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_LEFT),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_UP),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_DOWN),4),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_RIGHT),5),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_LEFT),5),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_UP),5),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_DOWN),5),
};
std::unordered_map<int, int> Mapper_WoodenBox{

	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_LEFT),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_UP),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_DOWN),1),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_RIGHT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_LEFT),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_UP),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DYING, user::SubState::DYING_NORMAL, user::Direction::Facing_DOWN),2),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_RIGHT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_LEFT),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_UP),3),
	std::make_pair(StateSystem::_GenerateTotalState(user::State::DEAD, user::SubState::DEAD_NORMAL, user::Direction::Facing_DOWN),3)
};
std::unordered_map<int, int> Mapper_NONE;


// FRAMES PER ANIMATION
std::vector<uint8_t> NoAnimation(2, 1);
std::vector<uint8_t> UnitAnimation(17, 4);
std::vector<uint8_t> HealthBarAnimation(12, 1);
std::vector<uint8_t> WaterTileAnimation(2, 16);
std::vector<uint8_t> PortalAnimation(2, 5);
std::vector<uint8_t> TowerAnimation(2, 4);
std::vector<uint8_t> ArrowAnimation(2, 4);
std::vector<uint8_t> PlacementAnimation(2, 4);
std::vector<uint8_t> TarTrapAnimation(2, 5);
std::vector<uint8_t> SpellAnimation(2, 8);
std::vector<uint8_t> HitAnimation(2, 4);
std::vector<uint8_t> SpiketrapAnimation(3, 5);
std::vector<uint8_t> UIButtonAnimation(5, 1);
std::vector<uint8_t> WoodenBoxAnimation(4, 1);
std::vector<uint8_t> NodeAnimation(5, 1);
std::vector<uint8_t> BallistaAnimation{

	1,
	6,
	2,
	6,
	1,
	1
};


// MOTIF MAPPER
std::unordered_map<user::Motif, std::string> MotifMapper{
	std::make_pair(user::Motif::VALLEY, "Valley"),
	std::make_pair(user::Motif::LAVA_CHAMBER, "LavaChamber")
};


// CONSTRUCTOR
UserBlueprints::UserBlueprints(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager)
{
	m_Manager_Entities = entitiesmanager;
	m_Manager_Components = componentsmanager;
	m_Game = game;
}
UserBlueprints::~UserBlueprints() {}


// MISC
uint64_t UserBlueprints::_Create_Player(int score, int initialgold, int initialmana, int maxgold, int maxmana)
{
	uint64_t m_Player = m_Manager_Entities->_CreateEntity();

	if (m_Player != NULL)
	{
		ResourcesComponent* Player_Resources = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Player), m_Manager_Components->m_Components_Resources, user::ComponentType::RESOURCES);
		Player_Resources->_Init(m_Manager_Components->m_Components_Resources, score, initialgold, initialmana, maxgold, maxmana);
	}

	return m_Player;
}
uint64_t UserBlueprints::_Create_MouseCursor()
{
	uint64_t m_Mouse = m_Manager_Entities->_CreateEntity();

	if (m_Mouse != NULL)
	{
		TransformComponent* Mouse_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Mouse), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Mouse_Transform->_Init(0, 0, true, m_Manager_Components->m_Components_Transform);
		//Mouse_Transform->bIsMouse = true;

		AnimatedSpriteComponent* Mouse_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Mouse), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Mouse_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, "Assets/Sprites/Sheets/Mouse.bmp", NoAnimation, Mapper_NONE, 32, 32, 32, 32, 0, 0, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::MOUSE, false, false);

		CollisionComponent* Mouse_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Mouse), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Mouse_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::Sphere, mfk::ColourList::GREY_OPAQUE, user::CollisionProfile::MOUSE, 1, 1, 3, -3, -3);

		StateComponent* Mouse_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Mouse), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		Mouse_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);


		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}
	return m_Mouse;
}
uint64_t UserBlueprints::_Create_Camera(float cameraspeed, float limitsleft, float limitsright, float limitsup, float limitsdown)
{
	uint64_t m_Camera = m_Manager_Entities->_CreateEntity();

	if (m_Camera != NULL)
	{
		TransformComponent* Camera_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Camera), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Camera_Transform->_Init(0, 0, false, m_Manager_Components->m_Components_Transform);

		CameraComponent* Camera_Camera = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Camera), m_Manager_Components->m_Components_Camera, user::ComponentType::CAMERA);
		Camera_Camera->_Init(m_Manager_Components->m_Components_Camera, 1.f, 0.25f, 4.0f, 0.5f, cameraspeed, limitsleft, limitsright, limitsup, limitsdown);
	}

	return m_Camera;
}
uint64_t UserBlueprints::_Create_Text(float coordinates_x, float coordinates_y, bool cameratransformable, int textheight, const char* text, const char* fontpath, user::Alignment position, mfk::ColourList colour, user::Layer layer)
{
	uint64_t m_Text = m_Manager_Entities->_CreateEntity();

	if (m_Text != NULL)
	{
		TransformComponent* Text_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Text), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Text_Transform->_Init(coordinates_x, coordinates_y, cameratransformable,  m_Manager_Components->m_Components_Transform);

		TextComponent* Text_TextComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Text), m_Manager_Components->m_Components_Text, user::ComponentType::TEXT);
		Text_TextComponent->_Init(m_Manager_Components->m_Components_Text, m_Game->_Get_Renderer(), text, fontpath, textheight, std::make_pair(0, 0), colour, position, layer);

		m_Manager_Components->_SortTextByLayer();
	}

	return m_Text;
}
uint64_t UserBlueprints::_Create_TimerOnScreen(float coordinates_x, float coordinates_y, int CountdownValue, int textheight, uint64_t currenttime, user::TimerType timertype)
{
	uint64_t Timer = m_Manager_Entities->_CreateEntity();

	if (Timer != NULL)
	{
		TextComponent* Timer_TextComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Timer), m_Manager_Components->m_Components_Text, user::ComponentType::TEXT);
		Timer_TextComponent->_Init(m_Manager_Components->m_Components_Text, m_Game->_Get_Renderer(), std::to_string(CountdownValue).data(), "Assets/Fonts/Minecraft.ttf", textheight, std::make_pair(0, 0), mfk::ColourList::WHITE_OPAQUE, user::Alignment::MIDDLE_CENTRE, user::Layer::UI_TEXT);
		
		TransformComponent* Timer_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Timer), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Timer_Transform->_Init(coordinates_x, coordinates_y, false, m_Manager_Components->m_Components_Transform);

		TimeComponent* Timer_TimerComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Timer), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		Timer_TimerComponent->_Init(m_Manager_Components->m_Components_Time, (float)CountdownValue, currenttime, currenttime, true);
		Timer_TimerComponent->m_TypeOfTimer = timertype;
	}	

	m_Manager_Components->_SortTextByLayer();

	return Timer;
}
uint64_t UserBlueprints::_Create_HitEffect(float coordinates_x, float coordinates_y, uint64_t currenttime)
{
	uint64_t HitEffect = m_Manager_Entities->_CreateEntity();

	if (HitEffect != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/HitEffect.bmp";

		TransformComponent* HitEffect_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(HitEffect), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		HitEffect_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* HitEffect_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(HitEffect), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		HitEffect_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, HitAnimation, Mapper_PassiveAnimation, 16, 16, 32, 32, -16, -16, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::VISUAL_EFFECTS, false, false);
				
		TimeComponent* HitEffect_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(HitEffect), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		HitEffect_Timer->_Init(m_Manager_Components->m_Components_Time,0.5f, currenttime, currenttime, true);
		HitEffect_Timer->m_TypeOfTimer = user::TimerType::TIMER_SPECIAL_EFFECT;

		// SORTING
		m_Manager_Components->_SortSpritesByLayer();
	}

	return HitEffect;
}


// UNITS
uint64_t UserBlueprints::_Create_EnemyUnit(float coordinates_x, float coordinates_y, user::EnemyType enemytype, uint64_t currenttime)
{
	// MOVEMENT
	float MovementSpeed = 50.f;


	 // SPRITE
	std::string UnitSpriteFilepath;
	std::pair<int, int> SpriteSheetDimensions;
	std::pair<int, int> SpriteSheetOffset;

	// HEALTH
	int UnitHealth;

	// HEALTH SPRITE
	int HHealthbarVerticalOffset;

	// RESOURCES
	int m_Score = 100;
	int Gold = 100;
	int Mana;

	 // COLLISION BOX
	int w;
	int h;
	int w_off;
	int h_off;

	// AI
	float m_IntervalBetweenDecisions = 2.f;

	// ATTACK
	float m_Damage;
	float AttackInterval;

	// CASES
	switch (enemytype)
	{
	case user::EnemyType::GOBLIN_WARRIOR:

		

		UnitSpriteFilepath = "Assets/Sprites/Sheets/EnemyUnit_Goblin.bmp";
		SpriteSheetDimensions = std::make_pair(16, 16);
		SpriteSheetOffset = std::make_pair(-24, -48);		
		
		UnitHealth = 100;

		HHealthbarVerticalOffset = -44;

		
		Mana = 0;

		w = 24;
		h = 34;
		w_off = -12;
		h_off = - 34;

		m_Damage = 10;
		AttackInterval = 0.5f; // DPS 20/s

		break;
	case user::EnemyType::SKELETON_WARRIOR:

	

		UnitSpriteFilepath = "Assets/Sprites/Sheets/EnemyUnit_SkellyWarrior.bmp";
		SpriteSheetDimensions = std::make_pair(16, 16);
		SpriteSheetOffset = std::make_pair(-24, -48);

		UnitHealth = 150;

		HHealthbarVerticalOffset = -44;


		Mana = 10;

		w = 24;
		h = 40;
		w_off = -12;
		h_off = -40;

		m_Damage = 35;
		AttackInterval = 1.0f; // DPS 35/2

		break;

	case user::EnemyType::ORC_WARRIOR:

	

		UnitSpriteFilepath = "Assets/Sprites/Sheets/EnemyUnit_OrcWarrior.bmp";
		SpriteSheetDimensions = std::make_pair(16, 16);
		SpriteSheetOffset = std::make_pair(-24, -48);

		UnitHealth = 200;

		HHealthbarVerticalOffset = -44;


		Mana = 0;

		w = 24;
		h = 40;
		w_off = -12;
		h_off = -40;

		m_Damage = 60;
		AttackInterval = 1.5f; // DPS 40/s
		break;
	case user::EnemyType::MUMMY:

		

		UnitSpriteFilepath = "Assets/Sprites/Sheets/EnemyUnit_Mummy.bmp";
		SpriteSheetDimensions = std::make_pair(16, 16);
		SpriteSheetOffset = std::make_pair(-24, -48);

		UnitHealth = 300;

		HHealthbarVerticalOffset = -44;


		Mana = 25;

		w = 24;
		h = 40;
		w_off = -12;
		h_off = -40;

		m_Damage = 60;
		AttackInterval = 2.0f; // DPS 30/s

		break;

	case user::EnemyType::DRAGON:

		

		UnitSpriteFilepath = "Assets/Sprites/Sheets/EnemyUnit_Dragon.bmp";
		SpriteSheetDimensions = std::make_pair(32, 32);
		SpriteSheetOffset = std::make_pair(-48, -87);

		UnitHealth = 600;

		HHealthbarVerticalOffset = -90;


		Mana = 25;

		w = 32;
		h = 64;
		w_off = -16;
		h_off = -64;

		m_Damage = 100;
		AttackInterval = 2.0f; // DPS 50/s

		break;

	case user::EnemyType::OGRE:

	

		UnitSpriteFilepath = "Assets/Sprites/Sheets/EnemyUnit_Dragon.bmp";
		SpriteSheetDimensions = std::make_pair(32, 32);
		SpriteSheetOffset = std::make_pair(-22, -42);

		UnitHealth = 600;

		HHealthbarVerticalOffset = -35;


		Mana = 25;

		w = 20;
		h = 40;
		w_off = -10;
		h_off = -35;

		m_Damage = 80;
		AttackInterval = 2.0f; // DPS 40/s
		break;
	}

	uint64_t EnemyUnit = m_Manager_Entities->_CreateEntity();

	if (EnemyUnit != NULL)
	{
		TransformComponent* EnemyUnit_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		EnemyUnit_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		MovementComponent* EnemyUnit_Movement = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Movement, user::ComponentType::MOVEMENT);
		EnemyUnit_Movement->_Init(1, 1, MovementSpeed, MovementSpeed, MovementSpeed, MovementSpeed, m_Manager_Components->m_Components_Movement);

		StateComponent* EnemyUnit_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		EnemyUnit_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);

		AnimatedSpriteComponent* EnemyUnit_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		EnemyUnit_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, UnitSpriteFilepath, UnitAnimation, Mapper_MonsterUnit, SpriteSheetDimensions.first, SpriteSheetDimensions.second, 3 * SpriteSheetDimensions.first, 3 * SpriteSheetDimensions.second, SpriteSheetOffset.first, SpriteSheetOffset.second, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, false, true);

		HealthComponent* EnemyUnit_HealthComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Health, user::ComponentType::HEALTH);
		EnemyUnit_HealthComponent->_Init(m_Manager_Components->m_Components_Health, UnitHealth);

		AnimatedSpriteComponent* EnemyUnit_HealthBarSprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE2);
		EnemyUnit_HealthBarSprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, "Assets/Sprites/Sheets/HealthBar.bmp", HealthBarAnimation, Mapper_MonsterUnit, 42, 8, 32, 6, -16, HHealthbarVerticalOffset, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_ABOVE_GROUND, false, false);

		CollisionComponent* EnemyUnit_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		EnemyUnit_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::GREEN_OPAQUE, user::CollisionProfile::UNIT_ENEMY, w, h, 1, w_off, h_off);
		
		CollisionComponent* EnemyUnit_AttackZone = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION3);
		EnemyUnit_AttackZone->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::DARKBLUE_OPAQUE, user::CollisionProfile::ATTACK_ZONE, 40, 40, 1, -20, -36);

		ActionComponent* EnemyUnit_Action = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Action, user::ComponentType::ACTION);
		EnemyUnit_Action->_Init(m_Manager_Components->m_Components_Action);

		PathfindingComponent* EnemyUnit_Pathfinding = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Pathfinding, user::ComponentType::PATHFINDING);
		EnemyUnit_Pathfinding->_Init(m_Manager_Components->m_Components_Pathfinding);

		ResourcesComponent* EnemyUnit_Resources = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Resources, user::ComponentType::RESOURCES);
		EnemyUnit_Resources->_Init(m_Manager_Components->m_Components_Resources, m_Score,Gold, Mana, Gold, Mana);

		EnemyComponent* EnemyUnit_Enemy = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Enemy, user::ComponentType::ENEMY);
		EnemyUnit_Enemy->_Init(m_Manager_Components->m_Components_Enemy, enemytype);

		AttackComponent* EnemyUnit_Attack = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Attack, user::ComponentType::ATTACK);
		EnemyUnit_Attack->_Init(m_Manager_Components->m_Components_Attack, m_Damage, 0, 0, user::ProjectileType::_NONE);
	
		AIComponent* EnemyUnit_AI = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_AI, user::ComponentType::AI);
		EnemyUnit_AI->_Init(m_Manager_Components->m_Components_AI, m_IntervalBetweenDecisions);

		TimeComponent* EnemyAttack_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(EnemyUnit), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);		
		EnemyAttack_Timer->_Init(m_Manager_Components->m_Components_Time, AttackInterval, currenttime, currenttime, false);


		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return EnemyUnit;
}


// GRID
uint64_t UserBlueprints::_Create_Grid(float coordinates_x, float coordinates_y, int cellson_x, int cellson_y, int cellwidth, int cellheight)
{
	uint64_t Grid = m_Manager_Entities->_CreateEntity();

	if (Grid != NULL)
	{
		TransformComponent* Grid_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Grid), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Grid_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		CellGridComponent* Grid_Grid = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Grid), m_Manager_Components->m_Components_CellGrid, user::ComponentType::CELLGRID);
		Grid_Grid->_Init(m_Manager_Components->m_Components_CellGrid, cellson_x, cellson_y, cellwidth, cellheight, 0, 0);
	}

	return Grid;
}


// LANDSCAPE
void UserBlueprints::_Create_Landscape(std::vector<std::vector<char>>& leveldata, std::vector<std::vector<char>>& celldata, user::Motif motif, std::unordered_map<char, user::TileType>& mapper, std::pair<int, int> offsetfrombeginning, std::vector<uint64_t>& portalrepo, uint64_t& tower, std::vector<uint64_t>& noderepo)
{
	// CREATE INNER TILES
	for (int i = 0; i < leveldata.size(); i++)
	{
		for (int j = 0; j < leveldata[i].size(); j++)
		{
			_Create_InnerTile((float)offsetfrombeginning.first + j * 64.f, (float)offsetfrombeginning.second + i * 64.f, motif, &leveldata[i][j], mapper);
		}
	}
	// CREATE LAND BORDERS
	for (int i = 0; i < leveldata.size(); i++)
	{
		for (int j = 0; j < leveldata[i].size(); j++)
		{
			_Create_OuterTile((float)offsetfrombeginning.first + j * 64.f, (float)offsetfrombeginning.second + i * 64.f, motif, leveldata, i, j, mapper);
		}
	}

	// CREATE MOUNTAINS
	_Create_Mountains(motif, celldata, mapper, offsetfrombeginning);

	// CREATE SPAWN POINTS (PORTALS)
	for (int i = 0; i < leveldata.size(); i++)
	{
		for (int j = 0; j < leveldata[i].size(); j++)
		{
			if (ImportAndProcessDataSystem::_InterpretData(&leveldata[i][j], mapper) == user::TileType::SPAWN_POINT)
			{
				_Create_Portal((float)offsetfrombeginning.first + j * 64.f, (float)offsetfrombeginning.second + i * 64.f, motif, portalrepo);
			}
		}
	}

	// CREATE TOWERS		
	bool onetower = false;
	int k = 0;
	while (k < leveldata.size() && onetower == false)
	{
		int l = 0;

		while (l < leveldata[0].size() && onetower == false)
		{

			if (ImportAndProcessDataSystem::_InterpretData(&leveldata[k][l], mapper) == user::TileType::TOWER)
			{
				_Create_Tower((float)offsetfrombeginning.first + (l + 1) * 64.f, (float)offsetfrombeginning.second + (k + 1) * 64.f, tower, motif);
				onetower = true;
			}
			l++;
		}
		k++;
	}


	// CREATE NODES
	for (int i = 0; i < celldata.size(); i++)
	{
		for (int j = 0; j < celldata[0].size(); j++)
		{
			if (ImportAndProcessDataSystem::_InterpretData(&celldata[i][j], mapper) == user::TileType::LAND || ImportAndProcessDataSystem::_InterpretData(&celldata[i][j], mapper) == user::TileType::SPAWN_POINT || ImportAndProcessDataSystem::_InterpretData(&celldata[i][j], mapper) == user::TileType::TOWER)
			{
				_Create_Node((float)offsetfrombeginning.first + (j + 0.5f) * 32.f, (float)offsetfrombeginning.second + (i + 0.5f) * 32.f, noderepo, motif);
				
			}
		}
	}
	
}
void UserBlueprints::_Create_Mountains(user::Motif motif, std::vector<std::vector<char>>& data, std::unordered_map<char, user::TileType> mapper, std::pair<int, int> offsetfrombeginning)
{
	std::unordered_map<int, int> RemainingPositionsMap;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			if (ImportAndProcessDataSystem::_InterpretData(&data[i][j], mapper) == user::TileType::MOUNTAIN)
			{
				int position = ImportAndProcessDataSystem::_Get_Position(i, j, (int)data[i].size());
				RemainingPositionsMap.insert(std::make_pair(position, position));
			}
		}
	}

	bool jobisdone = false;
	while (jobisdone == false)
	{
		int rowwidth = (int)data[0].size();
		std::unordered_map<int, int> BufferPositionsMap = RemainingPositionsMap;

		bool validpositionfound = false;

		while (validpositionfound == false)
		{
			for (auto& position : BufferPositionsMap)
			{
				int i = ImportAndProcessDataSystem::_Get_Row(position.first, rowwidth);
				int j = ImportAndProcessDataSystem::_Get_Column(position.first, rowwidth);

				int row_up = i - 1;
				int row_down = i + 1;
				int row_current = i;

				int column_left = j - 1;
				int column_right = j + 1;
				int column_current = j;

				float coordinates_x;
				float coordinates_y;

				bool bigrockcreated = false;

				// MM-
				// M?-
				// ---
				if (ImportAndProcessDataSystem::_InterpretData(&data[row_up][column_left], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_up][column_current], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_current][column_left], mapper) == user::TileType::MOUNTAIN)
				{
					if (RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_up, column_left, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_up, column_current, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_current, column_left, rowwidth)) != RemainingPositionsMap.end())
					{
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_up, column_left, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_up, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_left, rowwidth));

						bigrockcreated = true;
						coordinates_x = (float)(column_left) * 32.f;
						coordinates_y = (float)(row_up) * 32.f;
					}
				}

				// -MM
				// -?M
				// ---
				else if (ImportAndProcessDataSystem::_InterpretData(&data[row_up][column_current], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_up][column_right], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_current][column_right], mapper) == user::TileType::MOUNTAIN)
				{
					if (RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_up, column_current, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_up, column_right, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_current, column_right, rowwidth)) != RemainingPositionsMap.end())
					{
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_up, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_up, column_right, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_right, rowwidth));

						bigrockcreated = true;
						coordinates_x = (float)(column_current) * 32.f;
						coordinates_y = (float)(row_up) * 32.f;
					}
				}

				// ---
				// M?-
				// MM-
				else if (ImportAndProcessDataSystem::_InterpretData(&data[row_current][column_left], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_down][column_left], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_down][column_current], mapper) == user::TileType::MOUNTAIN)
				{
					if (RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_current, column_left, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_down, column_left, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_down, column_current, rowwidth)) != RemainingPositionsMap.end())
					{
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_left, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_down, column_left, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_down, column_current, rowwidth));

						bigrockcreated = true;
						coordinates_x = (float)(column_left) * 32.f;
						coordinates_y = (float)(row_current) * 32.f;
					}
				}

				// ---
				// -?M
				// -MM
				else if (ImportAndProcessDataSystem::_InterpretData(&data[row_current][column_right], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_down][column_current], mapper) == user::TileType::MOUNTAIN &&
					ImportAndProcessDataSystem::_InterpretData(&data[row_down][column_right], mapper) == user::TileType::MOUNTAIN)
				{
					if (RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_current, column_right, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_down, column_current, rowwidth)) != RemainingPositionsMap.end() &&
						RemainingPositionsMap.find(ImportAndProcessDataSystem::_Get_Position(row_down, column_right, rowwidth)) != RemainingPositionsMap.end())
					{
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_current, column_right, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_down, column_current, rowwidth));
						RemainingPositionsMap.erase(ImportAndProcessDataSystem::_Get_Position(row_down, column_right, rowwidth));

						bigrockcreated = true;
						coordinates_x = (float)(column_current) * 32.f;
						coordinates_y = (float)(row_current) * 32.f;
					}
				}

				if (bigrockcreated == true)
				{
					_Create_Rock_Big(coordinates_x + offsetfrombeginning.first + 32.f, coordinates_y + offsetfrombeginning.second + 64.f, motif);
					validpositionfound = true;
				}
			}

			if (validpositionfound == false)
			{
				jobisdone = true;
				validpositionfound = true;
			}
		}
	}

	for (auto& position : RemainingPositionsMap)
	{
		int rowwidth = (int)data[0].size();
		float coordinate_x = ImportAndProcessDataSystem::_Get_Column(position.first, rowwidth) * 32.f;
		float coordinate_y = ImportAndProcessDataSystem::_Get_Row(position.first, rowwidth) * 32.f;

		_Create_Rock_Small(coordinate_x + offsetfrombeginning.first + 16.f, coordinate_y + offsetfrombeginning.second + 32.f, motif);
	}
}
uint64_t UserBlueprints::_Create_Rock_Big(float coordinates_x, float coordinates_y, user::Motif motif)
{
	uint64_t Rock = m_Manager_Entities->_CreateEntity();

	if (Rock != NULL)
	{	
		int generatedint;
		Random::GenerateRandomNumber(generatedint, 1, 2);
		std::string restoffilepath;

		switch (generatedint)
		{
		case 1:
			restoffilepath = "/Rocks/Rock_4x4_1.bmp";
			break;
		case 2:
			restoffilepath = "/Rocks/Rock_4x4_2.bmp";
			break;
		}

	std::string filepath;
		filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + restoffilepath;

		TransformComponent* Rock_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Rock), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Rock_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Rock_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Rock), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Rock_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, WaterTileAnimation, Mapper_PassiveAnimation, 64, 64, 89, 89, -46, -84, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, false, false);
				
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}
	return Rock;
}
uint64_t UserBlueprints::_Create_Rock_Small(float coordinates_x, float coordinates_y, user::Motif motif)
{
	uint64_t Rock = m_Manager_Entities->_CreateEntity();

	if (Rock != NULL)
	{
		int generatedint;
		Random::GenerateRandomNumber(generatedint, 1, 2);
		std::string restoffilepath;

		switch (generatedint)
		{
		case 1:
			restoffilepath = "/Rocks/Rock_2x2_1.bmp";
			break;
		case 2:
			restoffilepath = "/Rocks/Rock_2x2_2.bmp";
			break;
		}

		std::string filepath;
		filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + restoffilepath;

		TransformComponent* Rock_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Rock), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Rock_Transform->_Init(coordinates_x, coordinates_y, true,  m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Rock_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Rock), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Rock_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, WaterTileAnimation, Mapper_PassiveAnimation, 32, 32, 36, 36, -19, -35, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, false, false);

		//CollisionComponent* Rock_CollisionBox = Manager_Components->_CreateComponent(Manager_Entities->Get_EntityById(Rock), Manager_Components->Components_Collision, user::ComponentType::COLLISION1);
		//Rock_CollisionBox->_Init(Manager_Components->Components_Collision, Shape::CollisionBox, mfk::ColourList::WHITE_OPAQUE, user::CollisionProfile::STATIC_OBJECTS, 32, 32, 1, -16, -32);
		 
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}
	return Rock;
}
uint64_t UserBlueprints::_Create_Portal(float coordinates_x, float coordinates_y, user::Motif motif, std::vector<uint64_t>& portalrepo)
{
	uint64_t Portal = m_Manager_Entities->_CreateEntity();

	if (Portal != NULL)
	{			
		std::string filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + "/Portal/Portal.bmp";

		TransformComponent* Portal_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Portal), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Portal_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Portal_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Portal), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Portal_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, PortalAnimation, Mapper_PassiveAnimation, 64, 68, 64, 68, 0, -64, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, false, false);
				
		CollisionComponent* Portal_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Portal), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Portal_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::WHITE_OPAQUE, user::CollisionProfile::STRUCTURE, 64, 32, 1, 0, 0);

		m_Manager_Components->_SortSpritesByLayer();
	}

	portalrepo.push_back(Portal);

	return Portal;
}
uint64_t UserBlueprints::_Create_InnerTile(float coordinates_x, float coordinates_y, user::Motif motif, char* character, std::unordered_map<char, user::TileType>& mapper)
{
	uint64_t Tile;

	user::TileType Type = ImportAndProcessDataSystem::_InterpretData(character, mapper);

	if (ImportAndProcessDataSystem::_IsWater(Type) == true)
	{
		Tile = _Create_Tile_Flowing(coordinates_x, coordinates_y, motif);
	}
	else if (ImportAndProcessDataSystem::_IsLand(Type) == true)
	{
		Tile = _Create_Tile_Land(coordinates_x, coordinates_y, motif);
	}
	else
	{
		Tile = NULL;
		std::cout << "==== ERROR ====\n";
	}

	return Tile;
}
uint64_t UserBlueprints::_Create_Tile_Land(float coordinates_x, float coordinates_y, user::Motif motif)
{
	uint64_t Tile = m_Manager_Entities->_CreateEntity();

	if (Tile != NULL)
	{
		int generatedint;
		Random::GenerateRandomNumber(generatedint, 1, 12);

		std::string restoffilepath;
		switch (generatedint)
		{
		case 1:case 9:
			restoffilepath = "/Tile_Inner/Tile_Inner_1.bmp";
			break;
		case 2:case 10:
			restoffilepath = "/Tile_Inner/Tile_Inner_2.bmp";
			break;
		case 3:
			restoffilepath = "/Tile_Inner/Tile_Inner_3.bmp";
			break;
		case 4:
			restoffilepath = "/Tile_Inner/Tile_Inner_4.bmp";
			break;
		case 5:case 11:
			restoffilepath = "/Tile_Inner/Tile_Inner_5.bmp";
			break;
		case 6: case 12:
			restoffilepath = "/Tile_Inner/Tile_Inner_6.bmp";
			break;
		case 7:
			restoffilepath = "/Tile_Inner/Tile_Inner_7.bmp";
			break;
		case 8:
			restoffilepath = "/Tile_Inner/Tile_Inner_8.bmp";
			break;
		}

		std::string filepath;
		filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + restoffilepath;

		TransformComponent* Tile_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Tile_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Tile_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Tile_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, WaterTileAnimation, Mapper_PassiveAnimation, 64, 64, 64, 64, 0, 0, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::TILE_GROUND_FAR, false, false);

		m_Manager_Components->_SortSpritesByLayer();
	}

	return Tile;
}
uint64_t UserBlueprints::_Create_Tile_Flowing(float coordinates_x, float coordinates_y, user::Motif motif)
{
	uint64_t Tile = m_Manager_Entities->_CreateEntity();

	if (Tile != NULL)
	{
		std::string filepath;
		filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + "/Tile_Inner/Tile_Flowing.bmp";

		TransformComponent* Tile_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Tile_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Tile_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Tile_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, WaterTileAnimation, Mapper_PassiveAnimation, 64, 64, 64, 64, 0, 0, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::TILE_GROUND_FAR, false, false);

		m_Manager_Components->_SortSpritesByLayer();
	}

	return Tile;
}
uint64_t UserBlueprints::_Create_OuterTile(float coordinates_x, float coordinates_y, user::Motif motif, std::vector<std::vector<char>> data, int pos_row, int pos_col, std::unordered_map<char, user::TileType> mapper)
{
	uint64_t Tile = m_Manager_Entities->_CreateEntity();

	if (Tile != NULL && ImportAndProcessDataSystem::_InterpretData(&data[pos_row][pos_col], mapper) == user::TileType::FLOWING_BORDER)
	{
		bool bIsValid = false;
		std::string remainingfilepath;
		// Filepath is decided upon where datapoint is located in relation to surrounding datapoints and their respective tile types.

		// depending of land edges and land corners counters -> different bracket

		uint8_t EdgeCounter = 0;
		uint8_t CornerCounter = 0;

		bool N, S, W, E, NW, NE, SW, SE;

		// EDGES
		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row - 1][pos_col], mapper)))
		{
			N = true;
			EdgeCounter++;
		}
		else
		{
			N = false;
		}

		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row + 1][pos_col], mapper)))
		{
			S = true;
			EdgeCounter++;
		}
		else
		{
			S = false;
		}

		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row][pos_col - 1], mapper)))
		{
			W = true;
			EdgeCounter++;
		}
		else
		{
			W = false;
		}

		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row][pos_col + 1], mapper)))
		{
			E = true;
			EdgeCounter++;
		}
		else
		{
			E = false;
		}

		// CORNERS
		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row - 1][pos_col - 1], mapper)))
		{
			NW = true;
			CornerCounter++;
		}
		else
		{
			NW = false;
		}

		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row - 1][pos_col + 1], mapper)))
		{
			NE = true;
			CornerCounter++;
		}
		else
		{
			NE = false;
		}

		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row + 1][pos_col - 1], mapper)))
		{
			SW = true;
			CornerCounter++;
		}
		else
		{
			SW = false;
		}

		if (ImportAndProcessDataSystem::_IsLand(ImportAndProcessDataSystem::_InterpretData(&data[pos_row + 1][pos_col + 1], mapper)))
		{
			SE = true;
			CornerCounter++;
		}
		else
		{
			SE = false;
		}


	
		if (EdgeCounter == 4)
		{
			remainingfilepath = "Tile_4-Edges.bmp";
			bIsValid = true;
		}
		else if (EdgeCounter == 3)
		{
			if (N == false){ remainingfilepath = "Tile_3-Edges_WSE.bmp"; }
			else if (S == false) { remainingfilepath = "Tile_3-Edges_WNE.bmp"; }
			else if (W == false) { remainingfilepath = "Tile_3-Edges_NES.bmp"; }
			else { remainingfilepath = "Tile_3-Edges_NWS.bmp"; }
			bIsValid = true;
		}
		else if (EdgeCounter == 2)
		{
			// PARALLEL EDGES
			if (N == false && S == false) { remainingfilepath = "Tile_2-Edges_WE.bmp"; bIsValid = true;	}
			else if (W == false && E == false) { remainingfilepath = "Tile_2-Edges_NS.bmp"; bIsValid = true;}
			
			// EDGES IN THE CORNERS - NO ADDITIONAL CORNER
			else if (N == true && W == true && SE == false) { remainingfilepath = "Tile_2-Edges_NW.bmp"; bIsValid = true; }
			else if (N == true && E == true && SW == false) { remainingfilepath = "Tile_2-Edges_NE.bmp"; bIsValid = true; }
			else if (S == true && W == true && NE == false) { remainingfilepath = "Tile_2-Edges_SW.bmp"; bIsValid = true; }
			else if (S == true && E == true && NW == false) { remainingfilepath = "Tile_2-Edges_SE.bmp"; bIsValid = true; }

			// EDGES IN THE CORNERS - EXTRA CORNER
			else if (N == true && W == true && SE == true) { remainingfilepath = "Tile_2-EwC_Edges_NW_Corner_SE.bmp"; bIsValid = true; }
			else if (N == true && E == true && SW == true) { remainingfilepath = "Tile_2-EwC_Edges_NE_Corner_NW.bmp"; bIsValid = true; }
			else if (S == true && W == true && NE == true) { remainingfilepath = "Tile_2-EwC_Edges_SW_Corner_NE.bmp"; bIsValid = true; }
			else if (S == true && E == true && NW == true) { remainingfilepath = "Tile_2-EwC_Edges_SE_Corner_NW.bmp"; bIsValid = true; }

		}
		else if (EdgeCounter == 1)
		{
			// NO CORNERS
			if (N == true && SW == false && SE == false) { remainingfilepath = "Tile_Edge_N.bmp"; bIsValid = true;}
			else if (S == true && NW == false && NE == false) { remainingfilepath = "Tile_Edge_S.bmp"; bIsValid = true;}
			else if (W == true && NE == false && SE == false ) { remainingfilepath = "Tile_Edge_W.bmp"; bIsValid = true;}
			else if (E == true && NW == false && SW == false) { remainingfilepath = "Tile_Edge_E.bmp"; bIsValid = true;}

			// 1 CORNER
			else if (N == true && SW == true && SE == false) { remainingfilepath = "Tile_1-EwC_Edge_N_Corner_SW.bmp"; bIsValid = true; }
			else if (N == true && SW == false && SE == true) { remainingfilepath = "Tile_1-EwC_Edge_N_Corner_SE.bmp"; bIsValid = true; }
			else if (S == true && NW == true && NE == false) { remainingfilepath = "Tile_1-EwC_Edge_S_Corner_NW.bmp"; bIsValid = true; }
			else if (S == true && NW == false && NE == true) { remainingfilepath = "Tile_1-EwC_Edge_S_Corner_NE.bmp"; bIsValid = true; }
			else if (W == true && NE == true && SE == false) { remainingfilepath = "Tile_1-EwC_Edge_W_Corner_NE.bmp"; bIsValid = true; }
			else if (W == true && NE == false && SE == true) { remainingfilepath = "Tile_1-EwC_Edge_W_Corner_SE.bmp"; bIsValid = true; }
			else if (E == true && NW == true && SW == false) { remainingfilepath = "Tile_1-EwC_Edge_E_Corner_NW.bmp"; bIsValid = true; }
			else if (E == true && NW == false && SW == true) { remainingfilepath = "Tile_1-EwC_Edge_E_Corner_SW.bmp"; bIsValid = true; }

			// 2 CORNERS
			else if (N == true && SW == true && SE == true) { remainingfilepath = "Tile_1-Ew2C_Edge_N_Corner_SW-SE.bmp"; bIsValid = true; }
			else if (S == true && NW == true && NE == true) { remainingfilepath = "Tile_1-Ew2C_Edge_S_Corner_NW-NE.bmp"; bIsValid = true; }
			else if (W == true && NE == true && SE == true) { remainingfilepath = "Tile_1-Ew2C_Edge_W_Corner_SE-NE.bmp"; bIsValid = true; }
			else if (E == true && NW == true && SW == true) { remainingfilepath = "Tile_1-Ew2C_Edge_E_Corner_NW-SW.bmp"; bIsValid = true; }

		}
		else if (EdgeCounter == 0)
		{
			if (CornerCounter == 4)
			{
				remainingfilepath = "Tile_CornersOnly_4-Corners.bmp";
				bIsValid = true;
			}
			else if (CornerCounter == 3)
			{
				if(NW == false) { remainingfilepath = "Tile_CornersOnly_3-Corners_NE-SW-SE.bmp"; bIsValid = true; }
				else if (NE == false) { remainingfilepath = "Tile_CornersOnly_3-Corners_NW-SW-SE.bmp"; bIsValid = true; }
				else if (SW == false) { remainingfilepath = "Tile_CornersOnly_3-Corners_NW-NE-SE.bmp"; bIsValid = true; }
				else if (SE == false) { remainingfilepath = "Tile_CornersOnly_3-Corners_NW-NE-SW.bmp"; bIsValid = true; }
			}
			else if (CornerCounter == 2)
			{
				if (NW == true && NE == true) { remainingfilepath = "Tile_CornersOnly_2-Corners_NW-NE.bmp"; bIsValid = true; }
				else if (SW == true && SE == true) { remainingfilepath = "Tile_CornersOnly_2-Corners_SW-SE.bmp"; bIsValid = true; }
				else if (NW == true && SW == true) { remainingfilepath = "Tile_CornersOnly_2-Corners_NW_SW.bmp"; bIsValid = true; }
				else if (NE == true && SE == true) { remainingfilepath = "Tile_CornersOnly_2-Corners_NE-SE.bmp"; bIsValid = true; }
				else if (NW == true && SE == true) { remainingfilepath = "Tile_CornersOnly_2-Corners_NW-SE.bmp"; bIsValid = true; }
				else if (NE == true && SW == true) { remainingfilepath = "Tile_CornersOnly_2-Corners_NE-SW.bmp"; bIsValid = true; }
			}
			else if (CornerCounter == 1)
			{
				if (NW == true) { remainingfilepath = "Tile_CornersOnly_1-Corner_NW.bmp"; bIsValid = true; }
				else if (NE == true) { remainingfilepath = "Tile_CornersOnly_1-Corner_NE.bmp"; bIsValid = true; }
				else if (SW == true) { remainingfilepath = "Tile_CornersOnly_1-Corner_SW.bmp"; bIsValid = true; }
				else if (SE == true) { remainingfilepath = "Tile_CornersOnly_1-Corner_SE.bmp"; bIsValid = true; }
			}
		}


		if (bIsValid == true)
		{
			std::string filepath;
			filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + "/Tile_Border/" + remainingfilepath;
			
			TransformComponent* Tile_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
			Tile_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

			AnimatedSpriteComponent* Tile_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
			Tile_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, WaterTileAnimation, Mapper_PassiveAnimation, 64, 64, 64, 64, 0, 0, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::TILE_GROUND_CLOSE, false, false);

			CollisionComponent* Tile_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tile), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
			Tile_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::GREEN_OPAQUE, user::CollisionProfile::STATIC_OBJECTS, 64, 64, 1, 0, 0);

			m_Manager_Components->_SortSpritesByLayer();
			m_Manager_Components->_SortCollisionShapesByProfile();
		}
	}

	return Tile;
}
uint64_t UserBlueprints::_Create_Tower(float coordinates_x, float coordinates_y, uint64_t& tower, user::Motif motif)
{
	uint64_t Tower = m_Manager_Entities->_CreateEntity();
		
	std::string filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + "/Tower/Tower.bmp";
	std::string filepathhealthbar = "Assets/Sprites/Sheets/HealthBar.bmp";


	if (Tower != NULL)
	{
		TransformComponent* Tower_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tower), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Tower_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);
				
		AnimatedSpriteComponent* Tower_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tower), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Tower_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, TowerAnimation, Mapper_PassiveAnimation, 64, 106, 128, 212, -64, -212, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, false, true);

		HealthComponent* Tower_HealthComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tower), m_Manager_Components->m_Components_Health, user::ComponentType::HEALTH);
		Tower_HealthComponent->_Init(m_Manager_Components->m_Components_Health, 1000);

		AnimatedSpriteComponent* Tower_HealthBarSprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tower), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE2);
		Tower_HealthBarSprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepathhealthbar, HealthBarAnimation, Mapper_MonsterUnit, 42, 8, 84, 16, -42, -40, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_ABOVE_GROUND, false, false);

		CollisionComponent* Tower_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tower), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Tower_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::PURPLE_OPAQUE, user::CollisionProfile::TOWER, 128, 64, 1, -64, -64);


		// SORTING
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	tower = Tower;
	return Tower;
}
uint64_t UserBlueprints::_Create_Node(float coordinates_x, float coordinates_y, std::vector<uint64_t>& NodeRepo, user::Motif motif)
{
	uint64_t Node = m_Manager_Entities->_CreateEntity();

	std::string restofthefilepath = "/Node/NodeAvailability.bmp";
	std::string filepath = "Assets/Sprites/Motifs/" + MotifMapper.at(motif) + restofthefilepath;

	if (Node != NULL)
	{
		TransformComponent* Node_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Node), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Node_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		CollisionComponent* Node_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Node), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Node_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::PURPLE_OPAQUE, user::CollisionProfile::NODE, 32, 32, 1, -16, -16);

		AnimatedSpriteComponent* Node_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Node), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Node_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, NodeAnimation, Mapper_Node, 32, 32, 32, 32, -16, -16, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::PLACEMENT_NODE_AVAILABILITY, false, true);

		StateComponent* Node_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Node), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		Node_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);

		NodeComponent* Node_Node = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Node), m_Manager_Components->m_Components_Node, user::ComponentType::NODE);
		Node_Node->_Init(m_Manager_Components->m_Components_Node);


		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	NodeRepo.push_back(Node);
	return Node;
}


// PLACEMENT OBJECTS
uint64_t UserBlueprints::_Create_Ballista(float coordinates_x, float coordinates_y, uint64_t currenttime)
{
	int DAMAGE = 30;
	float SHOOTING_INTERVAL = 2.0f;	

	uint64_t Ballista = m_Manager_Entities->_CreateEntity();

	if (Ballista != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/Ballista.bmp";
		std::string filepathhealthbar = "Assets/Sprites/Sheets/HealthBar.bmp";

		TransformComponent* Ballista_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Ballista_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Ballista_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Ballista_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, BallistaAnimation, Mapper_Ballista, 37, 37, 100, 100, -50, -50 -16, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, true, true);
		
		StateComponent* Ballista_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		Ballista_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);

		AnimatedSpriteComponent* Ballista_HealthBarSprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE2);
		Ballista_HealthBarSprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepathhealthbar, HealthBarAnimation, Mapper_NONE, 42, 8, 32, 6, -16, -36, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_ABOVE_GROUND, false, false);

		HealthComponent* Ballista_HealthComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Health, user::ComponentType::HEALTH);
		Ballista_HealthComponent->_Init(m_Manager_Components->m_Components_Health, 100);

		CollisionComponent* Ballista_CollisionSphere = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Ballista_CollisionSphere->_Init(m_Manager_Components->m_Components_Collision, Shape::Sphere, mfk::ColourList::ORANGE_OPAQUE, user::CollisionProfile::STRUCTURE, 1, 1, 10, -10, -26);

		AttackComponent* Ballista_Attack = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Attack, user::ComponentType::ATTACK);
		Ballista_Attack->_Init(m_Manager_Components->m_Components_Attack, 0, 50, 0, user::ProjectileType::Arrow_Ballista);

		ActionComponent* Ballista_Action = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Action, user::ComponentType::ACTION);
		Ballista_Action->_Init(m_Manager_Components->m_Components_Action);

		BallistaComponent* Ballista_BallistaComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Ballista, user::ComponentType::BALLISTA);
		Ballista_BallistaComponent->_Init(m_Manager_Components->m_Components_Ballista, DAMAGE);

		TimeComponent* Ballista_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);		
		Ballista_Timer->_Init(m_Manager_Components->m_Components_Time, SHOOTING_INTERVAL, currenttime, currenttime, false);

		CollisionComponent* Ballista_DetectionZone = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Ballista), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION2);
		Ballista_DetectionZone->_Init(m_Manager_Components->m_Components_Collision, Shape::Sphere, mfk::ColourList::ORANGE_OPAQUE, user::CollisionProfile::DETECTION_ZONE, 1, 1, 320, -320, -336);


		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return Ballista;
}
uint64_t UserBlueprints::_Create_BallistaArrow(float ballistacoordinates_x, float ballistacoordinates_y, float ballistaanglex, float ballistaangley, int arrowlength, int arrowdmg, int CountdownValue, uint64_t currenttime, user::TimerType timertype)
{	
	int OffsetFromBallista_X = 0;
	int OffsetFromBallista_Y = -16;
		
	int COLLISION_RADIUS = 8;
	float SPEED = 150.f;
	mfk::NormalVector2D VECTOR = mfk::NormalVector2D(ballistaanglex, ballistaangley);


	float Coordinate_X = ballistacoordinates_x + OffsetFromBallista_X + 1.25f * ballistaanglex * arrowlength;
	float Coordinate_Y = ballistacoordinates_y + OffsetFromBallista_Y + 1.25f * ballistaangley * arrowlength;

	int CollisionOffset_X = (int)(0.2f * ballistaanglex * arrowlength);
	int CollisionOffset_Y = (int)(0.2f * ballistaangley * arrowlength);

	
	uint64_t Arrow = m_Manager_Entities->_CreateEntity();

	if (Arrow != NULL)
	{
		TransformComponent* Arrow_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Arrow_Transform->_Init(Coordinate_X, Coordinate_Y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Arrow_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Arrow_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, "Assets/Sprites/Sheets/Ballista_Arrow.bmp", ArrowAnimation, Mapper_PassiveAnimation, 15, 15, 46, 46, -23, -23, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_ABOVE_GROUND, true, false);
		
		MovementSystem::_Set_Angle(Arrow_Transform, Arrow_Sprite, VECTOR);

		CollisionComponent* Arrow_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Arrow_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::Sphere, mfk::ColourList::ORANGE_OPAQUE, user::CollisionProfile::PROJECTILE, 1, 1, COLLISION_RADIUS, CollisionOffset_X - COLLISION_RADIUS, CollisionOffset_Y - COLLISION_RADIUS);

		MovementComponent* Arrow_Movement = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_Movement, user::ComponentType::MOVEMENT);
		Arrow_Movement->_Init(1, 1, SPEED, SPEED, SPEED, SPEED, m_Manager_Components->m_Components_Movement);
		Arrow_Movement->m_NormalVector = mfk::NormalVector2D(ballistaanglex, ballistaangley);

		StateComponent* Arrow_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		Arrow_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);
		Arrow_State->m_CurrentState = user::State::MOVING; Arrow_State->m_CurrentSubState = user::SubState::MOVING_FLYING; Arrow_State->m_CurrentDirection = user::Direction::Facing_RIGHT;

		ProjectileComponent* Arrow_Projectile = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_Projectile, user::ComponentType::PROJECTILE);
		Arrow_Projectile->_Init(m_Manager_Components->m_Components_Projectile, user::ProjectileType::Arrow_Ballista, arrowdmg);

		TimeComponent* Arrow_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Arrow), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		Arrow_Timer->_Init(m_Manager_Components->m_Components_Time, 3.f, currenttime, currenttime, true);
		Arrow_Timer->m_TypeOfTimer = user::TimerType::TIMER_ARROW_VANISHING;

		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return Arrow;
}
uint64_t UserBlueprints::_Create_WoodenBox(float coordinates_x, float coordinates_y, uint64_t nodecomponentid)
{
	uint64_t WoodenBox = m_Manager_Entities->_CreateEntity();

	if (WoodenBox != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/Barricade.bmp";
		std::string filepathhealthbar = "Assets/Sprites/Sheets/HealthBar.bmp";

		TransformComponent* WoodenBox_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		WoodenBox_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* WoodenBox_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		WoodenBox_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, WoodenBoxAnimation, Mapper_WoodenBox, 32, 48, 32, 48, -16, -48, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_GROUND, false, true);

		StateComponent* WoodenBox_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		WoodenBox_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);

		AnimatedSpriteComponent* WoodenBox_HealthBarSprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE2);
		WoodenBox_HealthBarSprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepathhealthbar, HealthBarAnimation, Mapper_NONE, 42, 8, 32, 6, -16, -16, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::LEVEL_ABOVE_GROUND, false, false);

		HealthComponent* WoodenBox_HealthComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_Health, user::ComponentType::HEALTH);
		WoodenBox_HealthComponent->_Init(m_Manager_Components->m_Components_Health, 100);

		CollisionComponent* WoodenBox_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		WoodenBox_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::ORANGE_OPAQUE, user::CollisionProfile::STRUCTURE, 32, 32, 1, -16, -32);		

		BarricadeComponent* WoodenBox_Barricade = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(WoodenBox), m_Manager_Components->m_Components_Barricade, user::ComponentType::BARRICADE);
		WoodenBox_Barricade->_Init(m_Manager_Components->m_Components_Barricade, nodecomponentid);


		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return WoodenBox;
}
uint64_t UserBlueprints::_Create_TarTrap(float coordinates_x, float coordinates_y, uint64_t currenttime)
{

	float SLOW = 0.5;
	uint64_t Tartrap = m_Manager_Entities->_CreateEntity();

	if (Tartrap != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/TarTrap.bmp";

		TransformComponent* Tartrap_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tartrap), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Tartrap_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Tartrap_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tartrap), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Tartrap_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, PortalAnimation, Mapper_PassiveAnimation, 64, 64, 64, 64, -32, -32, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::TILE_GROUND_TRAP, false, false);

		CollisionComponent* Tartrap_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tartrap), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Tartrap_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::ORANGE_OPAQUE, user::CollisionProfile::TRAP, 64, 64, 1, -32, -32);

		TrapComponent* TarTrap_Trap = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tartrap), m_Manager_Components->m_Components_Trap, user::ComponentType::TRAP);
		TarTrap_Trap->_Init(m_Manager_Components->m_Components_Trap, 0.f, SLOW, user::TrapType::TAR_TRAP, true);

		TimeComponent* Tartrap_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Tartrap), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		float duration = 0.5f;
		Tartrap_Timer->_Init(m_Manager_Components->m_Components_Time, duration, currenttime, currenttime, false);

		// SORTING
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return Tartrap;
}
uint64_t UserBlueprints::_Create_SpikeTrap(float coordinates_x, float coordinates_y, uint64_t currenttime)
{

	float DAMAGE = 20.f;
	uint64_t Spiketrap = m_Manager_Entities->_CreateEntity();

	if (Spiketrap != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/SpikeTrap.bmp";

		TransformComponent* Spiketrap_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Spiketrap_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Spiketrap_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Spiketrap_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, SpiketrapAnimation, Mapper_Spiketrap, 64, 88, 64, 88, -32, -58, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::TILE_GROUND_TRAP, false, true);

		CollisionComponent* Spiketrap_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Spiketrap_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::ORANGE_OPAQUE, user::CollisionProfile::TRAP, 64, 64, 1, -32, -32);

		TrapComponent* Spiketrap_Trap = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_Trap, user::ComponentType::TRAP);
		Spiketrap_Trap->_Init(m_Manager_Components->m_Components_Trap, DAMAGE, 1.f, user::TrapType::SPIKE_TRAP, true);

		StateComponent* Spiketrap_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		Spiketrap_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_RIGHT, m_Manager_Components->m_Components_State);
		
		TimeComponent* Spiketrap_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		float interval = 1.5f;
		Spiketrap_Timer->_Init(m_Manager_Components->m_Components_Time, interval, currenttime, currenttime, false);

		AttackComponent* Spiketrap_Attack = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Spiketrap), m_Manager_Components->m_Components_Attack, user::ComponentType::ATTACK);
		Spiketrap_Attack->_Init(m_Manager_Components->m_Components_Attack, DAMAGE, 0, 0, user::ProjectileType::_NONE);


		// SORTING
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return Spiketrap;
}
uint64_t UserBlueprints::_Create_Fireball(float coordinates_x, float coordinates_y, uint64_t currenttime)
{
	uint64_t Firespell = m_Manager_Entities->_CreateEntity();

	if (Firespell != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/Firespell.bmp";


		TransformComponent* Firespell_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Firespell), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Firespell_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Firespell_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Firespell), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Firespell_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, SpellAnimation, Mapper_PassiveAnimation, 40, 36, 80, 72, -40, -36, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::VISUAL_EFFECTS, false, false);
		
		CollisionComponent* Firespell_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Firespell), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Firespell_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::Sphere, mfk::ColourList::PURPLE_OPAQUE, user::CollisionProfile::DETECTION_ZONE, 1, 1, 32, -32, -32);

		TimeComponent* Firespell_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Firespell), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		Firespell_Timer->_Init(m_Manager_Components->m_Components_Time, 1.f, currenttime, currenttime, true);
		Firespell_Timer->m_TypeOfTimer = user::TimerType::TIMER_SPELL_EFFECT;

		AttackComponent* Fireball_Attack = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Firespell), m_Manager_Components->m_Components_Attack, user::ComponentType::ATTACK);
		Fireball_Attack->_Init(m_Manager_Components->m_Components_Attack, 0, 0, 75, user::ProjectileType::_NONE);

		// SORTING
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}
	return Firespell;
}
uint64_t UserBlueprints::_Create_HealSpell(float coordinates_x, float coordinates_y, uint64_t currenttime)
{
	uint64_t Heal = m_Manager_Entities->_CreateEntity();

	if (Heal != NULL)
	{
		std::string filepath = "Assets/Sprites/Sheets/HealSpell.bmp";


		TransformComponent* Heal_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Heal), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Heal_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Heal_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Heal), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Heal_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, filepath, SpellAnimation, Mapper_PassiveAnimation, 35, 35, 35, 35, -17, -33, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::VISUAL_EFFECTS, false, false);

		CollisionComponent* Heal_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Heal), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Heal_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::Sphere, mfk::ColourList::PURPLE_OPAQUE, user::CollisionProfile::DETECTION_ZONE, 1, 1, 1, -1, -1);

		TimeComponent* Heal_Timer = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Heal), m_Manager_Components->m_Components_Time, user::ComponentType::TIME);
		Heal_Timer->_Init(m_Manager_Components->m_Components_Time, 1.f, currenttime, currenttime, true);
		Heal_Timer->m_TypeOfTimer = user::TimerType::TIMER_SPELL_EFFECT;

		AttackComponent* Heal_Attack = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Heal), m_Manager_Components->m_Components_Attack, user::ComponentType::ATTACK);
		Heal_Attack->_Init(m_Manager_Components->m_Components_Attack, 0, 0, 150, user::ProjectileType::_NONE);

		// SORTING
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}
	return Heal;
}


// MENU
uint64_t UserBlueprints::_Create_MenuButton(float coordinates_x, float coordinates_y, int buttonwwidth, int buttonheight, int spritewidth, int spriteheight, std::string spritefilepath, int textheight, const char* text, const char* fontpath, user::Alignment position, mfk::ColourList colour, std::pair<int,int> textoffset)
{
	uint64_t Button = m_Manager_Entities->_CreateEntity();

	if (Button != NULL)
	{
		TransformComponent* Button_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Button), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Button_Transform->_Init(coordinates_x, coordinates_y, true,m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Button_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Button), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Button_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, spritefilepath, NoAnimation, Mapper_NONE, spritewidth, spriteheight, buttonwwidth, buttonheight, -buttonwwidth / 2, -buttonheight / 2, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::UI_OBJECTS, false, false);

		CollisionComponent* Button_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Button), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		Button_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::GREEN_OPAQUE, user::CollisionProfile::STATIC_OBJECTS, buttonwwidth - 10, buttonheight, 1, -(buttonwwidth - 10) / 2, -buttonheight / 2);

		TextComponent* Button_TextComponent = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(Button), m_Manager_Components->m_Components_Text, user::ComponentType::TEXT);
		Button_TextComponent->_Init(m_Manager_Components->m_Components_Text, m_Game->_Get_Renderer(), text, fontpath, textheight, textoffset, colour, position, user::Layer::UI_TEXT);

		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}	

	return Button;
}
uint64_t UserBlueprints::_Create_Background(float coordinates_x, float coordinates_y, user::Resolution resolution, std::string incompletefilepath, std::unordered_map<user::Resolution, std::pair<uint16_t, uint16_t>> mapper_resolution)
{
	//calculate actual filepath based on resolution

	std::pair<uint16_t, uint16_t> dimensions = mapper_resolution.at(resolution);
	std::string fullpath = incompletefilepath + std::to_string(dimensions.first) + "x" + std::to_string(dimensions.second) + ".bmp";	

	uint64_t m_Background = m_Manager_Entities->_CreateEntity();

	if (m_Background != NULL)
	{
		TransformComponent* Background_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Background), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		Background_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* Background_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_Background), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		Background_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, fullpath, NoAnimation, Mapper_NONE, dimensions.first, dimensions.second, dimensions.first, dimensions.second, -dimensions.first / 2, -dimensions.second / 2, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::BACKGROUND_FAR, false, false);

		m_Manager_Components->_SortSpritesByLayer();
	}

	return m_Background;
}


// UI
uint64_t UserBlueprints::_Create_UIButton(float coordinates_x, float coordinates_y, int buttonwwidth, int buttonheight, int spritewidth, int spriteheight, std::string spritefilepath, user::UI_Button buttontype, const char* text, int textheight, int goldcost, int manacost, std::pair<int,int> textoffset)
{
	uint64_t UIButton = m_Manager_Entities->_CreateEntity();

	if (UIButton != NULL)
	{
		int valuetobepassed = 0;

		if (goldcost > 0) { valuetobepassed = goldcost; }
		else if (manacost > 0) { valuetobepassed = manacost; }

		std::string textfromvalue = std::to_string(valuetobepassed);

		const char* texttobepassed = (text == "") ? (textfromvalue.data()) : (text);

		TransformComponent* UIButton_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		UIButton_Transform->_Init(coordinates_x, coordinates_y, false, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* UIButton_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		UIButton_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, spritefilepath, UIButtonAnimation, Mapper_UIButton, spritewidth, spriteheight, buttonwwidth, buttonheight, -buttonwwidth / 2, -buttonheight / 2, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::UI_OBJECTS, false, true);

		CollisionComponent* UIButton_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		UIButton_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, Shape::m_CollisionBox, mfk::ColourList::GREEN_OPAQUE, user::CollisionProfile::STATIC_OBJECTS, buttonwwidth, buttonheight, 1, -buttonwwidth / 2, -buttonheight / 2);

		TextComponent* UIButton_Text = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_Text, user::ComponentType::TEXT);
		UIButton_Text->_Init(m_Manager_Components->m_Components_Text, m_Game->_Get_Renderer(), texttobepassed, "Assets/Fonts/Minecraft.ttf", textheight, textoffset, mfk::ColourList::WHITE_OPAQUE, user::Alignment::MIDDLE_CENTRE, user::Layer::UI_TEXT);

		ButtonComponent* UIButton_Button = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_Button, user::ComponentType::BUTTON);
		UIButton_Button->_Init(m_Manager_Components->m_Components_Button, buttontype);

		ResourcesComponent* UIButton_Resources = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_Resources, user::ComponentType::RESOURCES);
		UIButton_Resources->_Init(m_Manager_Components->m_Components_Resources,0, goldcost, manacost, goldcost, manacost);

		StateComponent* UIButton_State = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(UIButton), m_Manager_Components->m_Components_State, user::ComponentType::STATE);
		UIButton_State->_Init(user::State::IDLE, user::SubState::IDLE_DEFAULT, user::Direction::Facing_DOWN, m_Manager_Components->m_Components_State);


		m_Manager_Components->_SortTextByLayer();
		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}

	return UIButton;
}
uint64_t UserBlueprints::_Create_UI_Background(float coordinates_x, float coordinates_y, user::Resolution resolution, std::unordered_map<user::Resolution, std::pair<uint16_t, uint16_t>> mapper_resolution)
{
	//calculate actual filepath based on resolution

	std::pair<uint16_t, uint16_t> dimensions = mapper_resolution.at(resolution);
	std::string fullpath = "Assets/Sprites/UI/UI_Background_" + std::to_string(dimensions.first) + "x" + std::to_string(dimensions.second) + ".bmp";

	uint64_t m_UI_Background = m_Manager_Entities->_CreateEntity();

	if (m_UI_Background != NULL)
	{
		TransformComponent* UI_Background_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_UI_Background), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		UI_Background_Transform->_Init(coordinates_x, coordinates_y, false,m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* UI_Background_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(m_UI_Background), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		UI_Background_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, fullpath, NoAnimation, Mapper_MonsterUnit, dimensions.first, dimensions.second, dimensions.first, dimensions.second, -dimensions.first / 2, -dimensions.second / 2, m_Game->_Get_CurrentTickInGame(), 0.125f, user::Layer::UI_BACKGROUND, false, false);

		m_Manager_Components->_SortSpritesByLayer();
	}

	return m_UI_Background;

}
uint64_t UserBlueprints::_Create_PlacementObject(float coordinates_x, float coordinates_y, int spritewidth, int spriteheight, std::string spritefilepath, user::Layer spritelayer, int collisionwidth, int collisionheight, int collisionradius, Shape shape)
{	
	uint64_t PlacementObject = m_Manager_Entities->_CreateEntity();

	int collisionoffsetx = (shape == Shape::m_CollisionBox) ? (-collisionwidth / 2) : (-collisionradius);
	int collisionoffsety = (shape == Shape::m_CollisionBox) ? (-collisionheight / 2) : (-collisionradius);

	if (PlacementObject != NULL)
	{
		TransformComponent* PlacementObject_Transform = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(PlacementObject), m_Manager_Components->m_Components_Transform, user::ComponentType::TRANSFORM);
		PlacementObject_Transform->_Init(coordinates_x, coordinates_y, true, m_Manager_Components->m_Components_Transform);

		AnimatedSpriteComponent* PlacementObject_Sprite = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(PlacementObject), m_Manager_Components->m_Components_AnimatedSprite, user::ComponentType::ANIMATEDSPRITE1);
		PlacementObject_Sprite->_Init(m_Game->_Get_Renderer(), m_Manager_Components->m_Components_AnimatedSprite, spritefilepath, PlacementAnimation, Mapper_NONE, spritewidth, spriteheight, spritewidth, spriteheight, -spritewidth/2, -spriteheight/2, m_Game->_Get_CurrentTickInGame(), 0.125f, spritelayer, false, false);

		CollisionComponent* PlacementObject_CollisionBox = m_Manager_Components->_CreateComponent(m_Manager_Entities->_Get_EntityById(PlacementObject), m_Manager_Components->m_Components_Collision, user::ComponentType::COLLISION1);
		PlacementObject_CollisionBox->_Init(m_Manager_Components->m_Components_Collision, shape, mfk::ColourList::BLUE_OPAQUE, user::CollisionProfile::STATIC_OBJECTS, collisionwidth, collisionheight, collisionradius, collisionoffsetx, collisionoffsety);

		m_Manager_Components->_SortSpritesByLayer();
		m_Manager_Components->_SortCollisionShapesByProfile();
	}
	
	return PlacementObject;







}
