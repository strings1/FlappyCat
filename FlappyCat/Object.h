#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"

//class->objext


class Object {
private:

	
protected:
	SDL_Rect src;
	SDL_Texture* tex=nullptr;
	SDL_Rect dest;
public:
	Object();
/*	virtual ~Object()
	{
		if (tex)
			SDL_DestroyTexture(tex);
	}
	*/
	void virtual Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest) = 0; /// functie abstracta
	void CreateTexture(const char* path, SDL_Renderer* renderer);
	SDL_Texture** get_texture(void);
	SDL_Rect& get_src(void);
	SDL_Rect& get_dest(void);
	void setSource(int x, int y, int w, int h);
	void setdest_y(int y);
	void Center(SDL_Rect);
	void setdest_x(int x);
	void setDest(int x, int y, int w, int h);
	bool setTex(SDL_Texture** tex);

};