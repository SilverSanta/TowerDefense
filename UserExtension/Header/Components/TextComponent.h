#pragma once

#include "SDL.h"
#include "IComponent.h"
#include "ResourceManager.h"

// FORWARD DECLARATIONS
class Entity;
struct SDL_Renderer;


class TextComponent : public IComponent
{
	//CONSTRUCTORS
public:	
	TextComponent()
	{	
		//std::cout << "	 TEXT created\n";
	}
	~TextComponent()
	{
		//std::cout << "     TEXT: #" << m_Id << " deleted\n";
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
		SDL_RenderCopy(renderer, m_TextTexture, NULL, &m_Text_Rectangle);
	}	
	virtual void _DeleteFromRepository() override
	{
		mfk::FindObjectInRepoAndKillIt(this, m_TextRepository);
	}
	 
	// FUNCTIONS
	virtual void _Init(std::vector<TextComponent> &repo, SDL_Renderer* renderer,  std::string text,const char* fontpath, int textheight, std::pair<int, int> offset, mfk::ColourList colour, user::Alignment position, user::Layer textlayer)
	{
		if (this != nullptr)
		{
			// (1) REPOSITORY
			m_TextRepository = &repo;

			// (2) DATA
			m_Text = text;
			m_OffsetFromOrigin = offset;
			m_TextHeight = textheight;
			m_Colour = colour;
			m_TextLayer = textlayer;

			_SwitchTextTo(m_Text.data(), fontpath, m_TextHeight, m_Colour,position, renderer);
		}
	}

	void _SwitchTextTo(const char* newtext, const char* newpath, int newtextheight, mfk::ColourList newcolour,user::Alignment position, SDL_Renderer* renderer)
	{
		m_FontPath = newpath;
		m_Position = position;

		SDL_Color m_Colour{ 0,0,0,0 };
		m_Colour.r = mfk::m_Colour::Get_ColourTable(newcolour).red;
		m_Colour.g = mfk::m_Colour::Get_ColourTable(newcolour).green;
		m_Colour.b = mfk::m_Colour::Get_ColourTable(newcolour).blue;

		TTF_Font* font = ResourceManager::_Get_Instance()._Get_Font(newpath, newtextheight);
		
		SDL_Surface* textsurface = TTF_RenderText_Solid(font, newtext, m_Colour);

		m_TextTexture = SDL_CreateTextureFromSurface(renderer, textsurface);

		TTF_SizeText(font, newtext, &m_Text_Rectangle.w, &m_Text_Rectangle.h);
	}
	

public:
	// REPOSITORY
	std::vector<TextComponent>* m_TextRepository;
	std::string m_Text;
	SDL_Texture* m_TextTexture;
	SDL_Rect m_Text_Rectangle;
	std::pair<int, int> m_OffsetFromOrigin;
	int m_TextHeight;
	mfk::ColourList m_Colour;
	user::Alignment m_Position;
	user::Layer m_TextLayer;
	std::string m_FontPath;

	// DATA
	

	//FRIEND CLASSES
	friend class Entity;
	friend class EntitiesManager;
	friend class ComponentsManager;	
	friend class RenderSystem;
};

