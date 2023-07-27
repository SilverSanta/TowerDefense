#pragma once

#include <string>
#include <unordered_map>
#include "mfk.h"
#include "SDL_ttf.h"

// FORWARD DECLARATIONS
struct SDL_Surface;
struct SDL_Texture;

class ResourceManager {

public:
	static ResourceManager& _Get_Instance();
	SDL_Surface* _Get_Surface(std::string filepath);
	TTF_Font* _Get_Font(const char* fontpath, int textheight);
	int _Get_MapSize();
	void _ResetResources();

private:
	ResourceManager();
	ResourceManager(ResourceManager const&);
	ResourceManager operator=(ResourceManager const&);

	std::unordered_map < std::string, SDL_Surface* > m_surfaces;
	std::unordered_map < std::string, TTF_Font* > m_fonts;
};
