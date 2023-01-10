#include "Enemy.h"
#include <ctime>
#include <iostream>
#include "Definers.h"
using namespace std;

//620/5 benzi = 130

void enemy::setHitbox(int x, int y)
{
	Hitbox.x = x;
	Hitbox.y = y;
}

bool vitdif(int speed, enemy* v, int n)
{
	bool ok = true;
	for (size_t i = 0; i < n; i++)
		if (v[i].speed == speed)
		{	ok = false;
			break;
		}
	return ok;
}
bool posdif(int pos, enemy* v, int n,size_t index_enemy) //fct ret 0 sau 1 daca gaseste sau nu un element din 'v'
{															//cu pos==v[i].poz
	bool same_caine_pos = false;
	for (size_t i = 0; i < n; i++)
		if (i == index_enemy)
			i++; //skip el. la care suntem
		else
			if (v[i].get_dest().y == pos)
			{	
				same_caine_pos = true;
				break;
			}
	return same_caine_pos;
}

void enemy::Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(renderer, Tex, &src, &dest);
}

void enemy::Update(enemy* v,size_t index_enemy)
{
	this->setdest_x(this->get_dest().x - speed);

	if (this->get_dest().x <= -(this->get_dest().w))
	{
		//il teleportez fix inaintea ecranului
		//this->setdest_x(this->get_dest().w, this->get_dest().y, this->get_dest().w, this->get_dest().h);
		this->setdest_x(SCREEN_W);
		
		//to do: 5 benzi cu fiecare un Y-pos atribuit
		// ^FACEM ASTA DIRECt RAND(0-5)*130 = x
		
		//nextpos alege un nr random de la 1 la 5 si pune cainele pe banda respectiva



		do
		{
			nextPos = rand() % (max_dog_bands - min_dog_bands + 1) + min_dog_bands; // nr de generare a benzii 1-5
		} while (posdif(nextPos*DOG_BAND_VAL, v, 4,index_enemy));
		//cout << nextPos;
		this->setdest_y((nextPos)*DOG_BAND_VAL);
		
		do
		{
			this->speed= rand() % (maxs - mins + 1) + mins;
		} while (vitdif(speed,v, 4));

	}
	setHitbox(this->get_dest().x + 30, this->get_dest().y + 30);

}