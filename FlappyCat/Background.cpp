#include "Background.h"

void background::Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(renderer, Tex, &src, &dest);
}

void background::Update()
{
	this->setdest_x(this->get_dest().x - bkgspeed);
	if (this->get_dest().x <= -(this->get_dest().w))
	{
		//il teleportez fix inaintea ecranului
		//this->setdest_x(this->get_dest().w, this->get_dest().y, this->get_dest().w, this->get_dest().h);
		this->setdest_x(this->get_dest().w);
	}
}