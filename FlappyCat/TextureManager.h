#pragma once
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* Texture(const char* path, SDL_Renderer *render);
};