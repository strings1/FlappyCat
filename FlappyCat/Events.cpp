#include "Events.h"
#include "Definers.h"
extern bool only_once;
void check_for_collision(enemy* v, Player* cat, Coin* coin, Pwr_Mul* pow)//TO DO: add collision for score, hitbox 3% smaller
{
		for (size_t i = 0; i < num_of_dogs; i++)
		{
			if (SDL_HasIntersection(&(v + i)->get_hbox(), &cat->get_dest()))
				if (!cat->isInvulnerable() && cat->isAlive())
				{
					only_once = false;
					cat->RIP();
				}
					
		}

		for(size_t i=0; i<num_of_coins;i++)
		if (SDL_HasIntersection(&(coin+i)->get_dest(), &cat->get_dest()))
		{
			(coin+i)->setdest_x(-COIN_SIZE);
			cat->SetScore(cat->GetScore()+(coin->GetValue()<<pow->get_mul()));
		}


		if (SDL_HasIntersection(&pow->get_dest(), &cat->get_dest()))
		{
			pow->Duration=time(0);
			pow->setdest_x(-MUL_SIZE);
			pow->inc_mul();
		}

		
}