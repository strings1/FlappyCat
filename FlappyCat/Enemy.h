#pragma once
#include "Object.h"
#include <ctime>
#include "Definers.h"

class enemy : public Object
{
private:
	int speed;
	unsigned short int nextPos; //after death
	SDL_Rect Hitbox;

public:

	void Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest);
	void Update(enemy* v, size_t index_enemy);
	enemy()
	{
		speed = rand() % (maxs - mins + 1) + mins;
		nextPos = 0;
		this->setSource(0, 0, Enemy_W, Enemy_H);
		this->setDest(-Enemy_WD, 0, Enemy_WD, Enemy_HD);
		Hitbox.w = Enemy_WD / 2;
		Hitbox.h = Enemy_HD / 2;
	}
	friend bool vitdif(int speed, enemy* v, int n);
	void setHitbox(int x, int y);
	SDL_Rect& get_hbox() {return Hitbox;}
	void setdest_x(int x);
};