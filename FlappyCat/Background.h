#pragma once
#include "Object.h"
#include "Definers.h"
/*
class Object {
private:
	SDL_Rect src, dest;
	SDL_Texture* tex;
public:
	Object();
	void virtual Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest) = 0; /// functie abstracta
	void CreateTexture(const char* path, SDL_Renderer* renderer);
	SDL_Texture* get_texture(void);
	SDL_Rect& get_src(void);
	SDL_Rect& get_dest(void);
	void setSource(int x, int y, int w, int h);
	void setDest(int x, int y, int w, int h);

};
*/




class background : public Object
{
private: 
	int bkgspeed;
public:
	void Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest);
	void Update();
	background()
	{
		bkgspeed = 1;
		this->setSource(0, 0, SCREEN_W, SCREEN_H);
		this->setDest(0, 0, SCREEN_W, SCREEN_H);
	}

};