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