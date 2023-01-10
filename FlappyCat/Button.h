#pragma once
#include "TextureManager.h"
#include <iostream>
using namespace std;

class Button
{
protected:
	//Clasa are 3 texturi: base, hovered, hovered and pressed
	SDL_Texture* base;
	SDL_Texture* hovered;
	SDL_Texture* pressed;
	bool phase1 = false;
	SDL_Texture* tex; //textura actuala

	SDL_Rect src;
	SDL_Rect dest;
public:

	Button(int srcx,int srcy, int srcw, int srch, int destx, int desty, int destw, int desth)
	{
		base = NULL;
		hovered = NULL;
		pressed = NULL;
		setSource(srcx, srcy, srcw, srch);
		setDest(destx, desty, destw, desth);
	}

	void LoadTextures(SDL_Renderer* renderer,
		const char*  base_path,
		const char*  hovered_path,
		const char*  pressed_path);

	bool Render(SDL_Renderer* renderer, bool mouse_pressed);
	bool clicked();
	void setSource(int x, int y, int w, int h);
	void DestroyTex()
	{
		SDL_DestroyTexture(base);
		SDL_DestroyTexture(hovered);
		SDL_DestroyTexture(pressed);
	}
	void setDest(int x, int y, int w, int h);
	SDL_Rect get_dest(void)const { return dest; }
	//Bool care sa ne spuna daca daca clickul e apasat sau nu
	//void check_mouse(bool mouse_pressed);


};

//O clasa derivata din buton ce isi schimba texturile in functie de cate ori a fost apaasat
class switching_button :public Button
{
private:
	Uint16 nr_of_buttons;
	Uint64 click_counter;
	SDL_Texture** ButtonIcons=nullptr;
public:
	switching_button(int srcx, int srcy, int srcw, int srch, int destx, int desty, int destw, int desth, Uint16 NumberOfButtons) :
		Button(srcx, srcy, srcw, srch, destx, desty, destw, desth)
	{
		phase1 = false;
		nr_of_buttons = NumberOfButtons;
		click_counter = 0;
		try
		{
			ButtonIcons = new SDL_Texture * [nr_of_buttons*3];
			if (!ButtonIcons)
				throw 505;
		}
		catch (int error_code)
		{
			cout << "SPATIUL PENTRU BUTON SWITCH NEALOCAT! - " << error_code;
		}
	}
	~switching_button()
	{
		for (size_t i = 0; i < nr_of_buttons; i++)
		{
			SDL_DestroyTexture(base);
			SDL_DestroyTexture(hovered);
			SDL_DestroyTexture(pressed);
			change_button_icons(i);
		}
		if (ButtonIcons)
			delete[]ButtonIcons;
	}
	void change_button_icons(size_t i);
	virtual bool clicked(void);
	void load_button_i(size_t i, SDL_Renderer* renderer,
		const char* base_path,
		const char* hovered_path,
		const char* pressed_path);
	Uint16 get_nr_buttons(void) const { return nr_of_buttons; }
	Uint64 timesclicked(void) const { return click_counter; }
};