#include "Button.h"
//#include <iostream>
//using namespace std;
//static bool phase1 = false; //Toate astea doar pentru a randa si animatia de pressed. de asemenea poti anula apasarea unui buton prin indepartarea
//mouseului

void Button::LoadTextures(SDL_Renderer* renderer, const char* base_path, const char* hovered_path, const char* pressed_path)
{
	SDL_Surface* surface = IMG_Load(base_path);
	base=SDL_CreateTextureFromSurface(renderer ,surface);

	surface = IMG_Load(hovered_path);
	hovered = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load(pressed_path);
	pressed = SDL_CreateTextureFromSurface(renderer, surface);
}

bool Button::Render(SDL_Renderer* renderer, bool mouse_pressed)
{
	int x, y;
	bool status = false;
	SDL_GetMouseState(&x, &y);
	tex = base;
	//cout << x << " " << y << " " <<dest.x<<" "<<dest.y<<" " << dest.x + dest.w << " " << dest.y + dest.h << endl;
	if ((x >= dest.x && x <= dest.x + dest.w) && (y >= dest.y && y <= dest.y + dest.h))
	{
		if (mouse_pressed)
		{
			tex = pressed;
			status = true;

		}
		else tex = hovered;
	}
	SDL_RenderCopy(renderer, tex, &src, &dest);
	return status;
}

void Button::setSource(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}
void Button::setDest(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}

bool Button::clicked()
{
	if (tex == pressed)
		phase1 = true;

	if (phase1 == true && tex == hovered)
	{
		//cout<<"\nCLICKED!!\n";
		phase1 = false; //in caz de mai avem nev;
		return 1; //clicked
	}

	if (tex == base)
		phase1 = false; //daca cursorul a disparut de pe button
	return 0;
	
}




bool switching_button::clicked()
{
	if (tex == pressed)
		phase1 = true;

	if (phase1 == true && tex == hovered)
	{
		phase1 = false; //in caz de mai avem nev;
		click_counter++;
		//cout << "\nAI APASAT BUTONUL!\n";
		change_button_icons(click_counter);
		return 1; //clicked
	}

	if (tex == base)
		phase1 = false; //daca cursorul a disparut de pe button
	return 0;
	
}


void switching_button::change_button_icons(size_t i)
{
	i = i % nr_of_buttons;//for assurance that i is sent correctly
	//0- 0 1 2
	//1- 3 4 5
	//2- 6 7 8  0+3*i (+1 +2)
	base = ButtonIcons[0 + 3 * i];
	hovered = ButtonIcons[1 + 3 * i];
	pressed = ButtonIcons[2 + 3 * i];

}


void switching_button::load_button_i(size_t i, SDL_Renderer* renderer,
	const char* base_path,
	const char* hovered_path,
	const char* pressed_path)
{
	i = i % nr_of_buttons;
	SDL_Surface* surface;

	surface = IMG_Load(base_path);
	ButtonIcons[0 + 3 * i] = SDL_CreateTextureFromSurface(renderer, surface);
	if (surface != NULL)
	{
		cout << "Am sters o suprafata\n";
		SDL_FreeSurface(surface);
	}	
	
	surface = IMG_Load(hovered_path);
	ButtonIcons[1 + 3 * i] = SDL_CreateTextureFromSurface(renderer, surface);
	if (surface != NULL)
	{
		cout << "Am sters o suprafata\n";
		SDL_FreeSurface(surface);
	}

	surface = IMG_Load(pressed_path);
	ButtonIcons[2 + 3 * i] = SDL_CreateTextureFromSurface(renderer, surface);
	if (surface != NULL)
	{
		cout << "Am sters o suprafata\n";
		SDL_FreeSurface(surface);
	}
	cout << "DAU VALORI LA BASE AND THINGS!!!\n";
	base = ButtonIcons[0 + 3 * i];
	hovered = ButtonIcons[1 + 3 * i];
	pressed = ButtonIcons[2 + 3 * i];
	tex = base;

}