#include "TextureManager.h"
#include "GameLoop.h"

SDL_Texture* TextureManager::Texture(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* surface;
	surface = IMG_Load(path);
	SDL_Texture* tex= SDL_CreateTextureFromSurface(renderer, surface);
	if (surface != NULL)
	{
		cout << "Am sters o suprafata\n";
		SDL_FreeSurface(surface);
	}
	
	return tex;
}

SDL_Texture* TextureManager::TextureFont(SDL_Color color, const char* TEXT, TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, TEXT, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (surface != NULL)
	{
		cout << "Am sters o suprafata\n";
		SDL_FreeSurface(surface);
	}

	return tex;
}