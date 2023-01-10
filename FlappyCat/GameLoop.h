#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Object.h"
#include "Player.h"
#include "background.h"
#include <iostream>
#include "Enemy.h"
#include "Entity.h"
#include "Events.h"
#include "Button.h"
#include "Block.h"
#include "Catalog.h"
#include "Items.h"


class GameLoop {
private:
	bool _GameState;
	SDL_Window* _window;
	SDL_Event event;
	SDL_Renderer* _renderer;
	background bg1;
	background bg2;
	Player playr;

//	Catalog<item> catalog();



public:
	GameLoop();
	void Initialize();
	void Update();
	bool getGameState(void) const { return _GameState; }
	//int get_height(void) const { return _height;  }
	//int get_width(void) const { return _width;  }
	void Event();
	void Render();
	Player* GetPlayer(void) { return &playr; }
	void Clear();
	void Menu();
	void Shop();
	void InitShopValues(Catalog<item>&);
	void Retry();
	void SaveProgress(const char* scoretxt,const char* catalogtxt);
};