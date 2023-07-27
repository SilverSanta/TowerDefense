#pragma once

#include <algorithm>

#include "UserMenuState.h"
#include "EntitiesManager.h"
#include "UserGameState.h"
#include "UserExtension.h"
#include "ECS_Framework.h"
#include "ImportDataSystem.h"


UserMenuState::UserMenuState(MyFramework* game, ComponentsManager* componentsmanager, EntitiesManager* entitiesmanager, UserGameState* gamestate)
{
	m_Menu_Entities = entitiesmanager;
	m_Menu_Components = componentsmanager;
	m_Game = game;
	m_GameState = gamestate;
}
UserMenuState::~UserMenuState() {}


void UserMenuState::_Set_ButtonData(int gapbetweenbuttons, int buttonheight, int horizontaloffset, int verticaloffset)
{
	m_GapBetweenButtons = gapbetweenbuttons;
	m_ButtonHeight = buttonheight;
	m_HorizontalOffset = horizontaloffset;
	m_VerticalOffset = verticaloffset;
}
void UserMenuState::_Set_MenuLayout_StartGameMenu(std::pair<uint16_t, uint16_t> Resolution)
{
	TransformComponent* TitleButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Title)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* StartButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Start)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* ResumeButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Resume)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* QuitButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Quit)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* LevelButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Level)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* LavaButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_MotifLava)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* ValleyButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_MotifValley)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectLevelArrowLeftButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectLevel_ArrowLeft)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectLevelArrowRightButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectLevel_ArrowRight)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectMotifArrowLeftButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectMotif_ArrowLeft)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectMotifArrowRightButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectMotif_ArrowRight)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* PlayAgainButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Restart)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* Score_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Text_Score)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* WinOrLose_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Text_WinOrLose)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	
	//=======LAYOUT========
	//		  TITLE
	//        START
	//  << LEVEL < 1 >  >>
	//  << MOTIF < LAVA >  >>
	//        QUIT
	//=======LAYOUT========

	// Located in garbagetransform
	ResumeButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	ResumeButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	PlayAgainButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	PlayAgainButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	Score_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	Score_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	WinOrLose_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	WinOrLose_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;


	// On screen
	TitleButton_TransformPtr->m_X = (float)Resolution.first / 2; TitleButton_TransformPtr->m_Y = (float)Resolution.second / 2 - 200;
	StartButton_TransformPtr->m_X = (float)Resolution.first / 2;	StartButton_TransformPtr->m_Y = (float)(Resolution.second / 2 - 0.0 * m_GapBetweenButtons - 0.0 * m_ButtonHeight);
	SelectLevelArrowLeftButton_TransformPtr->m_X = (float)Resolution.first / 2 - 160.f;	SelectLevelArrowLeftButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 1.0 * m_GapBetweenButtons + 1.0 * m_ButtonHeight);
	SelectLevelArrowRightButton_TransformPtr->m_X = (float)Resolution.first / 2 + 160.f;	SelectLevelArrowRightButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 1.0 * m_GapBetweenButtons + 1.0 * m_ButtonHeight);
	SelectMotifArrowLeftButton_TransformPtr->m_X = (float)Resolution.first / 2 - 160.f;	SelectMotifArrowLeftButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 2.0 * m_GapBetweenButtons + 2.0 * m_ButtonHeight);
	SelectMotifArrowRightButton_TransformPtr->m_X = (float)Resolution.first / 2 + 160.f;	SelectMotifArrowRightButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 2.0 * m_GapBetweenButtons + 2.0 * m_ButtonHeight);
	QuitButton_TransformPtr->m_X = (float)Resolution.first / 2;	QuitButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 3.0f * m_GapBetweenButtons + 3.0f * m_ButtonHeight);
	LevelButton_TransformPtr->m_X = (float)Resolution.first / 2;	LevelButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 1.0 * m_GapBetweenButtons + 1.0 * m_ButtonHeight);
			

	// MOTIF (variable)
	if (m_GameState->m_LevelMotif == user::Motif::VALLEY)
	{
		ValleyButton_TransformPtr->m_X = (float)Resolution.first / 2; ValleyButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 2.0 * m_GapBetweenButtons + 2.0 * m_ButtonHeight);
		LavaButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	LavaButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	}
	else if (m_GameState->m_LevelMotif == user::Motif::LAVA_CHAMBER)
	{
		LavaButton_TransformPtr->m_X = (float)Resolution.first / 2; LavaButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 2.0 * m_GapBetweenButtons + 2.0 * m_ButtonHeight);
		ValleyButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	ValleyButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	}
}
void UserMenuState::_Set_MenuLayout_DuringGameMenu(std::pair<uint16_t, uint16_t> Resolution)
{
	//=======LAYOUT========
	// RESUME
	// QUIT
	// RESTART
	//=======LAYOUT========
	
	TransformComponent* ResumeButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Resume)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* QuitButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Quit)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* PlayAgainButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Restart)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);

	// What is seen on screen
	ResumeButton_TransformPtr->m_X = (float)Resolution.first / 2;	ResumeButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 1.0 * m_GapBetweenButtons + 1.0 * m_ButtonHeight);
	QuitButton_TransformPtr->m_X = (float)Resolution.first / 2;	QuitButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 2.0 * m_GapBetweenButtons + 2.0 * m_ButtonHeight);
	PlayAgainButton_TransformPtr->m_X = (float)Resolution.first / 2; PlayAgainButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 3.0 * m_GapBetweenButtons + 3.0 * m_ButtonHeight);

	_Set_Menu_RelocateButtonsNoLongerInUse(Resolution);
}
void UserMenuState::_Set_MenuLayout_EndGameMenu(std::pair<uint16_t, uint16_t> Resolution)
{
	// TITLE
	// WIN OR LOSE
	// SCORE
	// PLAY AGAIN?		
	// QUIT
	
	TransformComponent* ResumeButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Resume)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* QuitButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Quit)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* PlayAgainButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Restart)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* Score_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Text_Score)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* WinOrLose_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Text_WinOrLose)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);

	TextComponent* Score_TextPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Text_Score)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), m_Menu_Components->m_Components_Text);
	std::string NewScoreText = "Score: " + std::to_string(m_GameState->m_Score_AfterEndGame);
	Score_TextPtr->_SwitchTextTo(NewScoreText.data(), (Score_TextPtr->m_FontPath).data(), Score_TextPtr->m_TextHeight, mfk::ColourList::DARKBLUE_OPAQUE, Score_TextPtr->m_Position, m_Game->_Get_Renderer());

	TextComponent* WinOrLose_TextPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Text_WinOrLose)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), m_Menu_Components->m_Components_Text);

	if (m_GameState->m_bGameHasBeenWon)
	{
		WinOrLose_TextPtr->_SwitchTextTo("S.T.A.G.E  C.L.E.A.R.E.D", (Score_TextPtr->m_FontPath).data(), Score_TextPtr->m_TextHeight, mfk::ColourList::DARKBLUE_OPAQUE, Score_TextPtr->m_Position, m_Game->_Get_Renderer());
	}
	else if (m_GameState->m_bGameHasBeenLost)
	{
		WinOrLose_TextPtr->_SwitchTextTo("D.E.F.E.A.T", (Score_TextPtr->m_FontPath).data(), Score_TextPtr->m_TextHeight, mfk::ColourList::RED_OPAQUE, Score_TextPtr->m_Position, m_Game->_Get_Renderer());
	}

	// On screen
	WinOrLose_TransformPtr->m_X = (float)Resolution.first / 2; WinOrLose_TransformPtr->m_Y = (float)(Resolution.second / 2 - 1.0 * m_GapBetweenButtons - 1.0 * m_ButtonHeight);
	Score_TransformPtr->m_X = (float)Resolution.first / 2; Score_TransformPtr->m_Y = (float)(Resolution.second / 2 + 0.0 * m_GapBetweenButtons + 0.0 * m_ButtonHeight);
	PlayAgainButton_TransformPtr->m_X = (float)Resolution.first / 2; PlayAgainButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 1.0 * m_GapBetweenButtons + 1.0 * m_ButtonHeight);
	QuitButton_TransformPtr->m_X = (float)Resolution.first / 2;	QuitButton_TransformPtr->m_Y = (float)(Resolution.second / 2 + 2.0 * m_GapBetweenButtons + 2.0 * m_ButtonHeight);

	// Located in garbagetransform
	ResumeButton_TransformPtr->m_X += (float)m_GameState->m_GargabeTransform.first;	ResumeButton_TransformPtr->m_Y += (float)m_GameState->m_GargabeTransform.second;
	_Set_Menu_RelocateButtonsNoLongerInUse(Resolution);


	// LOGIC
	m_Game->_Set_InMenu(true);
	m_Game->_EndGame();
}
void UserMenuState::_Set_MenuLayout_ChangeLevel(bool LeftArrowHit)
{
	TransformComponent* LevelButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Level)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);

	//=======LAYOUT========
	// START
	// LEVEL < 1 >     <->     // LEVEL SELECT < 1 >
	// MOTIF < VALLEY> // MOTIF < LAVA >
	// QUIT
	//=======LAYOUT========


	// Logic

	if (LeftArrowHit == true)
	{
		m_GameState->m_CurrentLevel = std::clamp(m_GameState->m_CurrentLevel - 1, 1, m_GameState->m_NumberOfLevels);


		if (m_GameState->m_CurrentLevel > 1)
		{
			m_GameState->m_CurrentLevel-- ;
		}
	}
	else
	{
		if (m_GameState->m_CurrentLevel < m_GameState->m_NumberOfLevels)
		{
			m_GameState->m_CurrentLevel++;
		}
	}

	std::string m_Text = "LEVEL  < " + std::to_string(m_GameState->m_CurrentLevel) + " >";

	TextComponent* LevelButton_TextPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Level)->_Get_ComponentIdFromEntityByType(user::ComponentType::TEXT), m_Menu_Components->m_Components_Text);
	LevelButton_TextPtr->_SwitchTextTo(m_Text.data(), (LevelButton_TextPtr->m_FontPath).data(), LevelButton_TextPtr->m_TextHeight, LevelButton_TextPtr->m_Colour, LevelButton_TextPtr->m_Position, m_Game->_Get_Renderer());
	
	
}
void UserMenuState::_Set_MenuLayout_ChangeMotif()
{
	TransformComponent* LavaMotifButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_MotifLava)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* ValleyMotifButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_MotifValley)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);

	if (m_GameState->m_LevelMotif == user::Motif::LAVA_CHAMBER)
	{
		m_GameState->m_LevelMotif = user::Motif::VALLEY;

		ValleyMotifButton_TransformPtr->m_X = LavaMotifButton_TransformPtr->m_X; ValleyMotifButton_TransformPtr->m_Y = LavaMotifButton_TransformPtr->m_Y;
		LavaMotifButton_TransformPtr->m_X = (float)m_GarbageTransform.first; LavaMotifButton_TransformPtr->m_Y = (float)m_GarbageTransform.second;
	}
	else if (m_GameState->m_LevelMotif == user::Motif::VALLEY)
	{
		m_GameState->m_LevelMotif = user::Motif::LAVA_CHAMBER;

		LavaMotifButton_TransformPtr->m_X = ValleyMotifButton_TransformPtr->m_X; LavaMotifButton_TransformPtr->m_Y = ValleyMotifButton_TransformPtr->m_Y;
		ValleyMotifButton_TransformPtr->m_X = (float)m_GarbageTransform.first; ValleyMotifButton_TransformPtr->m_Y = (float)m_GarbageTransform.second;
	}
}
void UserMenuState::_Set_Menu_RelocateButtonsNoLongerInUse(std::pair<uint16_t, uint16_t> Resolution)
{
	TransformComponent* StartButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Start)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* LevelButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_Level)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* LavaButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_MotifLava)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* ValleyButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_MotifValley)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectLevelArrowLeftButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectLevel_ArrowLeft)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectLevelArrowRightButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectLevel_ArrowRight)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectMotifArrowLeftButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectMotif_ArrowLeft)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);
	TransformComponent* SelectMotifArrowRightButton_TransformPtr = m_Menu_Components->_Get_ComponentPtrFromId(m_Menu_Entities->_Get_EntityById(m_Button_SelectMotif_ArrowRight)->_Get_ComponentIdFromEntityByType(user::ComponentType::TRANSFORM), m_Menu_Components->m_Components_Transform);

	StartButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	StartButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	LevelButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	LevelButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	LevelButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	LevelButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	LavaButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	LavaButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	ValleyButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	ValleyButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	SelectLevelArrowLeftButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	SelectLevelArrowLeftButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	SelectLevelArrowRightButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	SelectLevelArrowRightButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	SelectMotifArrowLeftButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	SelectMotifArrowLeftButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;
	SelectMotifArrowRightButton_TransformPtr->m_X = (float)m_GameState->m_GargabeTransform.first;	SelectMotifArrowRightButton_TransformPtr->m_Y = (float)m_GameState->m_GargabeTransform.second;

}