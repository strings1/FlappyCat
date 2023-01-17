#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class TextureManager
{
public:
	static SDL_Texture* Texture(const char* path, SDL_Renderer *render);
	static SDL_Texture* TextureFont(SDL_Color color,const char* TEXT, TTF_Font* font, SDL_Renderer* renderer);
};