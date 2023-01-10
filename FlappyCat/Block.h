#pragma once
#include "Object.h"
class block : public Object
{
public:

	block(int srcx, int srcy, int srcw, int srch, int destx, int desty, int destw, int desth)
	{
		setSource(srcx, srcy, srcw, srch);
		setDest(destx, desty, destw, desth);
	}

	void Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest)
	{
		SDL_RenderCopy(renderer, Tex, &src, &dest);
	}
};