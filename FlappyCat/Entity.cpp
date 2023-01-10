#include "Entity.h"
#include "TextureManager.h"
#include "Definers.h"
#include <iostream>
using namespace std;
void Coin::Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(renderer, Tex, &src, &dest);
}

void Pwr_Mul::Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest)
{
	if (CurrentChange - LastChange > 100)
	{
		tex = frames[frame_number%3];
		frame_number++;
		LastChange = CurrentChange;
	}
	SDL_RenderCopy(renderer, Tex, &src, &dest);
}

void Coin::LoadFrames(SDL_Renderer* renderer)
{
	SDL_Surface * surface= IMG_Load("Sprites/Coin0.png");
	for (size_t i = 0; i < 6; i++)
	{
		switch (i)
		{

		case 0:
			surface = IMG_Load("Sprites/Coin0.png");
			break;
		case 1:
			surface = IMG_Load("Sprites/Coin1.png");
			break;
		case 2:
			surface = IMG_Load("Sprites/Coin2.png");
			break;
		case 3:
			surface = IMG_Load("Sprites/Coin3.png");
			break;
		case 4:
			surface = IMG_Load("Sprites/Coin4.png");
			break;
		case 5:
			surface = IMG_Load("Sprites/Coin5.png");
			break;
		default:break;
			
		}
		frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
	}
}

/*
void Coin::LoadFrame(SDL_Renderer* renderer)
{
	SDL_Surface * surface= IMG_Load("Sprites/Coin0.png");
	static SDL_Texture* temptex = 0;
	for (size_t i = 0; i < 6; i++)
	{
		switch (i)
		{

		case 0:
			surface = IMG_Load("Sprites/Coin0.png");
			break;
		case 1:
			surface = IMG_Load("Sprites/Coin1.png");
			break;
		case 2:
			surface = IMG_Load("Sprites/Coin2.png");
			break;
		case 3:
			surface = IMG_Load("Sprites/Coin3.png");
			break;
		case 4:
			surface = IMG_Load("Sprites/Coin4.png");
			break;
		case 5:
			surface = IMG_Load("Sprites/Coin5.png");
			break;
		default:break;
			
		}
		temptex = SDL_CreateTextureFromSurface(renderer, surface);
		frame[i] = temptex;
	}
}
*/

void Coin::Update()
{
	if (CurrentChange - LastChange > 100)
	{
		tex = frames[frame_number%6];
		frame_number++;
		LastChange = CurrentChange;
	}


	CurrentChange = SDL_GetTicks64();
	this->setdest_x(this->get_dest().x - speed);
	int x;
	if (this->get_dest().x <= -(this->get_dest().w))
	{
		this->setdest_x(SCREEN_W);
			x = rand() % (max_coin_bands - min_coin_bands + 1) + min_coin_bands; // nr de generare a benzii 1-5
		//cout << nextPos;
		nextPos = x;
		this->setdest_y((nextPos) * COIN_BAND_VAL);
	}


}


void Pwr_Mul::Update()
{
	int x;
	time_t temp;

	
	temp = time(0);

	if (temp > Duration + 7)//Daca au trecut 7 secunde
	{
		Duration = 0;
		reset_mul();
	}


	CurrentChange = SDL_GetTicks64();
	this->setdest_x(this->get_dest().x - speed);
	
	if (this->get_dest().x <= -(this->get_dest().w))
	{	
		frequency = SDL_GetTicks64();
		if (frequency - last_time_spawned > 5000)
		{
			last_time_spawned = frequency;
			this->setdest_x(SCREEN_W);
				x = rand() % (max_coin_bands - min_coin_bands + 1) + min_coin_bands;
			//cout << nextPos;
			nextPos = x;
			this->setdest_y((nextPos) * COIN_BAND_VAL);
		}

	}
}


void Pwr_Mul::LoadFrames(SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load("Sprites/coinmul0.png");
	for (size_t i = 0; i < 3; i++)
	{
		switch (i)
		{

		case 0:
			surface = IMG_Load("Sprites/coinmul0.png");
			break;
		case 1:
			surface = IMG_Load("Sprites/coinmul1.png");
			break;
		case 2:
			surface = IMG_Load("Sprites/coinmul2.png");
			break;
		default:break;

		}
		frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
	}
}