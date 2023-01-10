#pragma once
#include "Object.h"
#include <iostream>
using namespace std;
//ADD LASER
//ADD NAVETUTA
//ADD MORE CHARACTERS
class Player : public Object
{
private:
	Uint32 score=0;
	bool alive;
	bool godmode;
	short int grav_f;
	double accelerator1;
	double accelerator2;
	bool is_jumping;
	double jump_h;
	Uint64 jumpTimer;
	Uint64 lastJump = 0; // il folosim pentru delta_T pentru a determina daca putem sau nu sari;



public:	
	Uint64 godtime_s = 0;
	Uint64 godtime_f = 0;
	Player() {
		jump_h = -20;
		grav_f = 2;
		accelerator1 = 0;
		accelerator2 = 0;
		is_jumping = false;
		alive = true;
		godmode = false;
	}
	void resetJGAA(void);
	void Render(SDL_Renderer* renderer, SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
	void gravity(void);
	void Update(bool spacePressed);
	void GetJumpTime(void);
	Uint32 GetScore(void) const { return score; }
	void SetScore(Uint32 NewValue) { score = NewValue; cout << "\nSCORUL A FOST SETAT LA VALOAREA " << score; }
	bool JumpState(void) const {return is_jumping;}
	bool isAlive(void) const {return alive;}
	bool isInvulnerable(void) const {return godmode;}
	void RIP(void);
	void death(void);
	void jump();
	void setgodmode(bool x) { godmode = x;}
	void respawn() { alive = true; };
	short int get_grav_f(void) const { return grav_f; }
};