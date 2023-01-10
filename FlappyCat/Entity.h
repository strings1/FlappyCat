#pragma once
#include "Object.h"
#include "Definers.h"
#include <ctime>
class Coin : public Object 
{
private:
	int speed;
	unsigned short nextPos;
	size_t frame_number=0;

	Uint64 LastChange;
	Uint64 CurrentChange;
	Uint16 CoinMul = 1;
	Uint32 value = 1;
	
	SDL_Texture* frames[6];
	//static SDL_Texture* frame[6];
public:

	Coin()
	{
		LastChange=SDL_GetTicks64();
		CurrentChange=SDL_GetTicks64();
		frame_number = 0;
		speed = 5; //~=Background speed
		setSource(0, 0, 30, 30);
		setDest(-COIN_SIZE, -COIN_SIZE, COIN_SIZE, COIN_SIZE);
	}
	void Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest);
	void Update(void);
	Uint32 GetValue(void) const { return value; }
	//static void LoadFrame(SDL_Renderer* renderer);
	//static 	SDL_Texture** get_frame(size_t);
	void LoadFrames(SDL_Renderer* renderer);
	void DestroyTex()
	{
		for (size_t i = 0; i < 6; i++)
			SDL_DestroyTexture(frames[i]);
	}
//	Uint16 IncScore();
};


class Pwr_Mul : public Object
{
	int speed;
	unsigned short nextPos;
	size_t frame_number = 0;

	Uint64 LastChange;
	Uint64 CurrentChange;
	Uint64 frequency;
	Uint64 last_time_spawned;
	Uint32 multiplier = 0; // score= coinvalue*(1<<multiplier)

	SDL_Texture* frames[3];
	//static SDL_Texture* frame[6];
public:
	time_t Duration;

	Pwr_Mul()
	{
		Duration = 0;
		multiplier = 0;
		LastChange = SDL_GetTicks64();
		frequency = 0;
		last_time_spawned = 0;
		CurrentChange = SDL_GetTicks64();
		frame_number = 0;
		speed = 10;
		setSource(0, 0, 30, 30);
		setDest(-MUL_SIZE, -MUL_SIZE, MUL_SIZE, MUL_SIZE);
	}
	void Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest);
	void Update(void);
	void LoadFrames(SDL_Renderer* renderer);
	void reset_mul(void) { multiplier = 0; }
	void inc_mul(void) { multiplier++; }
	Uint32 get_mul(void) { return multiplier; }
	void DestroyTex()
	{
		for (size_t i = 0; i < 3; i++)
			SDL_DestroyTexture(frames[i]);
	}
};