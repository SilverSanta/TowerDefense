#pragma once

#include "UserExtension.h"


// USER BLUEPRINTS
class UserBlueprints
{
public:
	UserBlueprints(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager);
	~UserBlueprints();


	// MISC
	uint64_t _Create_Player(int score, int initialgold, int initialmana, int maxgold, int maxmana);
	uint64_t _Create_MouseCursor();
	uint64_t _Create_Camera(float cameraspeed, float limitsleft, float limitsright, float limitsup, float limitsdown);
	uint64_t _Create_Text(float coordinates_x, float coordinates_y, bool cameratransformable, int textheight, const char* text, const char* fontpath, user::Alignment position, mfk::ColourList colour, user::Layer layer);
	uint64_t _Create_TimerOnScreen(float coordinates_x, float coordinates_y, int CountdownValue, int textheight, uint64_t currenttime, user::TimerType timertype);
	uint64_t _Create_HitEffect(float coordinates_x, float coordinates_y, uint64_t currenttime);


	// UNITS
	uint64_t _Create_EnemyUnit(float coordinates_x, float coordinates_y, user::EnemyType enemytype, uint64_t);


	// GRID
	uint64_t _Create_Grid(float coordinates_x, float coordinates_y, int cellson_x, int cellson_y, int cellwidth, int cellheight);
		

	// LANDSCAPE
	void _Create_Landscape(std::vector<std::vector<char>>& data, std::vector<std::vector<char>>& celldata, user::Motif motif, std::unordered_map<char, user::TileType>& mapper, std::pair<int, int> offsetfrombeginning, std::vector<uint64_t>& portalrepo, uint64_t& tower, std::vector<uint64_t>& noderepo);
	void _Create_Mountains(user::Motif motif, std::vector<std::vector<char>>& data, std::unordered_map<char, user::TileType> mapper, std::pair<int, int> offsetfrombeginning);
	uint64_t _Create_InnerTile(float coordinates_x, float coordinates_y, user::Motif motif, char* character, std::unordered_map<char, user::TileType>& mapper);
	uint64_t _Create_Tile_Land(float coordinates_x, float coordinates_y, user::Motif motif);
	uint64_t _Create_Tile_Flowing(float coordinates_x, float coordinates_y, user::Motif motif);
	uint64_t _Create_OuterTile(float coordinates_x, float coordinates_y, user::Motif motif, std::vector<std::vector<char>> data, int pos_row, int pos_col, std::unordered_map<char, user::TileType> mapper);
	uint64_t _Create_Rock_Big(float coordinates_x, float coordinates_y, user::Motif motif);
	uint64_t _Create_Rock_Small(float coordinates_x, float coordinates_y, user::Motif motif);
	uint64_t _Create_Portal(float coordinates_x, float coordinates_y, user::Motif motif, std::vector<uint64_t>& portalrepo );
	uint64_t _Create_Tower(float coordinates_x, float coordinates_y, uint64_t& tower, user::Motif motif);
	uint64_t _Create_Node(float coordinates_x, float coordinates_y, std::vector<uint64_t>& NodeRepo, user::Motif motif);


	// PLACEMENT OBJECTS
	uint64_t _Create_Ballista(float coordinates_x, float coordinates_y, uint64_t currenttime);
	uint64_t _Create_BallistaArrow(float ballistacoordinates_x, float ballistacoordinates_y, float ballistaanglex, float ballistaangley, int arrowlength, int arrowdmg, int CountdownValue, uint64_t currenttime, user::TimerType timertype);
	uint64_t _Create_WoodenBox(float coordinates_x, float coordinates_y, uint64_t nodecomponentid);
	uint64_t _Create_TarTrap(float coordinates_x, float coordinates_y, uint64_t currenttime);
	uint64_t _Create_SpikeTrap(float coordinates_x, float coordinates_y, uint64_t currenttime);
	uint64_t _Create_Fireball(float coordinates_x, float coordinates_y, uint64_t currenttime);
	uint64_t _Create_HealSpell(float coordinates_x, float coordinates_y, uint64_t currenttime);

	
	// MENU
	uint64_t _Create_MenuButton(float coordinates_x, float coordinates_y, int buttonwwidth, int buttonheight, int spritewidth, int spriteheight, std::string spritefilepath, int textheight, const char* text, const char* fontpath, user::Alignment position, mfk::ColourList colour, std::pair<int,int> textoffset);
	uint64_t _Create_Background(float coordinates_x, float coordinates_y, user::Resolution resolution, std::string incompletefilepath, std::unordered_map < user::Resolution, std::pair<uint16_t, uint16_t>> mapper_resolution);
	

	// UI
	uint64_t _Create_UIButton(float coordinates_x, float coordinates_y, int buttonwwidth, int buttonheight, int spritewidth, int spriteheight, std::string spritefilepath, user::UI_Button buttontype, const char* text, int textheight, int goldcost, int manacost, std::pair<int,int> textoffset);
	uint64_t _Create_UI_Background(float coordinates_x, float coordinates_y, user::Resolution resolution, std::unordered_map < user::Resolution, std::pair<uint16_t, uint16_t>> mapper_resolution);
	uint64_t _Create_PlacementObject(float coordinates_x, float coordinates_y, int spritewidth, int spriteheight, std::string spritefilepath, user::Layer spritelayer, int collisionwidth, int collisionheight, int collisionradius, Shape shape);
	

private:
	EntitiesManager* m_Manager_Entities;
	ComponentsManager* m_Manager_Components;
	MyFramework* m_Game;
};











