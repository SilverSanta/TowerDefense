#pragma once

//#include "UserExtension.h"

class UserGameState;

class EntitiesManager;
class ComponentsManager;
class MyFramework;
class UserGameState;



class UserMenuState
{
public:
	UserMenuState(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, UserGameState* gamestate);
	~UserMenuState();
	 
public:


	void _Set_ButtonData(int gapbetweenbuttons, int buttonheight, int horizontaloffset, int verticaloffset);
	void _Set_MenuLayout_StartGameMenu(std::pair<uint16_t, uint16_t> Resolution);
	void _Set_MenuLayout_DuringGameMenu(std::pair<uint16_t, uint16_t> Resolution);
	void _Set_MenuLayout_EndGameMenu(std::pair<uint16_t, uint16_t> Resolution);
	void _Set_MenuLayout_ChangeLevel(bool LeftArrowHit);
	void _Set_MenuLayout_ChangeMotif();
	void _Set_Menu_RelocateButtonsNoLongerInUse(std::pair<uint16_t, uint16_t> Resolution);



public:
	std::pair<int, int> m_GarbageTransform = std::make_pair(-100000, -100000);


	int m_GapBetweenButtons;
	int m_ButtonHeight;
	int m_HorizontalOffset;
	int m_VerticalOffset;


	uint64_t m_Mouse;
	uint64_t m_Camera;

	uint64_t m_Background;

	uint64_t m_Button_Title;
	uint64_t m_Button_Start;
	uint64_t m_Button_Resume;
	uint64_t m_Button_Quit;
	uint64_t m_Button_Restart;

	uint64_t m_Button_Level;

	uint64_t m_Button_MotifValley;
	uint64_t m_Button_MotifLava;

	uint64_t m_Button_SelectLevel_ArrowLeft;
	uint64_t m_Button_SelectLevel_ArrowRight;

	uint64_t m_Button_SelectMotif_ArrowLeft;
	uint64_t m_Button_SelectMotif_ArrowRight;

	uint64_t m_Text_WinOrLose;
	uint64_t m_Text_Score;


private:
	EntitiesManager* m_Menu_Entities;
	ComponentsManager* m_Menu_Components;
	MyFramework* m_Game;	
	UserGameState* m_GameState;
};











