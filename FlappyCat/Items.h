#pragma once
#include "TextureManager.h"
#include "Object.h"
class item : public Object
{
protected:
	Uint32 price;
	bool status; //0 locked      1 unlocked
public:
	item()
	{
		price = 0;
		status = 0;
	}
	item(SDL_Renderer* _renderer ,Uint32 price, bool status, const char* path)
	{
		this->price = price;
		this->status = status;
		CreateTexture(path, _renderer);
	}
	void Render(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
		SDL_RenderCopy(renderer, tex, &src, &dest);
	}
	void setprice(Uint32 x) { price = x; }

	Uint32& operator !(void) { return price; }
	bool operator ~(void) { return status; }
	bool operator++(int a) { status = true; return status; }
	bool operator--(int a) { status = false; return status; }
	item& operator=(Uint16 x) { status = x % 2; return *this; }
	//! return price
	//~ return status
	//++ unlocked +return
	//-- locked +return
};