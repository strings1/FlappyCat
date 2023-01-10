#include "Player.h"
#include <iostream>
#include "Definers.h"
#include <Windows.h>
using namespace std;
bool only_once = false;
void Player::Render(SDL_Renderer* renderer, SDL_Texture* Tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(renderer, Tex, &src, &dest);
}

void Player::gravity(void)
{
    //trage playerul in jos la fiecare frame

    if (is_jumping)
    {
        if (!only_once &&alive)
        {
            //PlaySound(TEXT("Sounds/jump"), NULL, SND_ASYNC);
            only_once = true;
        }
        accelerator1 = accelerator1 + 0.0035;
        jump_h = jump_h + grav_f;
        double JMP=this->dest.y+accelerator1+jump_h;
        if (this->dest.y < -this->dest.h)
        {
            if (alive)
                this->setdest_y(JMP / 1.76); //fix pt jump out of bound
        }
        else
            this->setdest_y(JMP);

       
        if (jump_h > 0)
        {
            if(alive)
                only_once = false;
            is_jumping = false;
            jump_h = -20;
        }

    }
    else
    {

        accelerator2 = accelerator2 - 0.729;

        if (alive) {

            if ((this->dest.y + this->dest.h) + grav_f <= SCREEN_H) {
                this->setdest_y(this->dest.y + grav_f - accelerator2);
            }
            else {
                int dif_inaltime;
                dif_inaltime = SCREEN_H - (this->dest.y + this->dest.h);
                this->setdest_y(this->dest.y + dif_inaltime);
            }
        }
        else
        {
            if (this->dest.y < SCREEN_H + this->dest.h)
                this->setdest_y(this->dest.y + grav_f - accelerator2);
        }


    }
   
}
//Jump grav_F ac,ac
void Player::resetJGAA(void)
{
    jump_h = -20;
    grav_f = 2;
    accelerator1 = 0;
    accelerator2 = 0;
}

void Player::RIP(void)
{
    alive = false;
    
}

void Player::Update(bool spacePressed)
{
    this->GetJumpTime();
    this->godtime_f = SDL_GetTicks64();
    if (spacePressed && alive)
    {

        this->jump();
    }

    if (godtime_f - godtime_s > 800)
    {
        godtime_s = godtime_f;
        this->setgodmode(false);
    }
    
    if(!alive)
    {
        death();
      //  cout << alive;
    }

    this->gravity();
}


void Player::death(void)
{
    if (!only_once)
    {
        Sleep(300);
        accelerator1 = 0;
        accelerator2 = 0;
        jump_h = -13;
        grav_f = 1;

        is_jumping = true;
        only_once = true;
    }
}

void Player::GetJumpTime(void)
{
    jumpTimer = SDL_GetTicks64();
}

void Player::jump(void)
{
    
    if (jumpTimer - lastJump > 180) //reset all the values
    {
        accelerator1 = 0;
        accelerator2 = 0;
        lastJump = jumpTimer;
        is_jumping = false;
    }
    else
    {
        is_jumping = true;
        
    }

}