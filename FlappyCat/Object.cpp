#include "Object.h"
#include <iostream>
using namespace std;
Object::Object()
{
	tex = NULL;
}

void Object::CreateTexture(const char* path, SDL_Renderer* renderer)
{
	tex=TextureManager::Texture(path, renderer);
}

bool Object::setTex(SDL_Texture** tex)
{
	bool diferite = false;
	if (tex)
	{
			if (this->tex != *tex)
			{
				//SDL_DestroyTexture(this->tex);
				diferite = true;
			}
			this->tex = *tex;
	}
	return diferite;
}

void Object::setSource(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}
void Object::setDest(int x, int y, int w, int h){
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}

void Object::setdest_y(int y)
{
	dest.y = y;
}

void Object::setdest_x(int x)
{
	dest.x = x;
}

SDL_Texture** Object::get_texture(void) {
	return &tex;
}

SDL_Rect& Object::get_src(void) {
	return src;
}

SDL_Rect& Object::get_dest(void){
	return dest;
}

void Object::Center(SDL_Rect rect)
{
	//centrul obiectului
	dest.x = rect.x + (rect.w >>1);
	dest.y =rect.y+(rect.h>>1);

	dest.x -= (dest.w >>1);
	dest.y -= (dest.h >>1);
}
