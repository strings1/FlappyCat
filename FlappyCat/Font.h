#pragma once
#include "Object.h"
#include <SDL_ttf.h>
class TEXT :public obj_interface
{
	int texW = 0;
	int texH = 0;
	SDL_Rect dstrect;
	SDL_Texture* texture;
	int size;
	SDL_Color color;
	TTF_Font* font = nullptr;
public:
	TEXT(SDL_Color color, int size)
	{
		this->size = size;
		this->color = color;
	}

	void setdest_y(int y) {
		this->dstrect.y = y;
	}

	void destroy()
	{
		if (texture)
			SDL_DestroyTexture(texture);
		if (font)
			TTF_CloseFont(font);
	}

	void Center(SDL_Rect);

	void setdest_x(int x)
	{
		this->dstrect.x = x;
	}

	void setDest(int x, int y, int w, int h)
	{
		this->dstrect.w=w;
		this->dstrect.h=h;
		this->dstrect.y=y;
		this->dstrect.x=x;
	}

	bool setText(SDL_Renderer* _renderer, const char* text)
	{
		if(texture)
			SDL_DestroyTexture(texture);
		texture = TextureManager::TextureFont(color, text, font, _renderer);
		if (!texture)
		{
			return 0;
		}
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		dstrect = {dstrect.x, dstrect.y, texW, texH };
		printf("Am SETAT TEXTURA!!!\n\n");
		return 1;
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	void initialize(const char* font_name)
	{
		font = TTF_OpenFont(font_name, size);
		if (font == nullptr)
		{
			printf("NU AM GASIT FONTUL %s!\n\n", font_name);
		}
		this->color = color;
	}

};


char* toArray(int number);