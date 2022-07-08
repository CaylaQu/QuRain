#pragma once
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public: // Public methods.
	static void Init();
	static void Load(const char* path, const std::string key);
	static void Unload(const std::string key);
	static SDL_Texture* GetTexture(const std::string key);
	static void Quit();

private: // Private properties.
	static std::map<std::string, SDL_Texture*> s_textures;

private: // Private methods.
	TextureManager();
};

typedef TextureManager TEMA;

#endif