#include "GameLoop.h"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
using namespace std;
FILE* Score_File_in=nullptr;
GameLoop* game = new GameLoop(); //AICI SE CREAZA PLAYERUL SI ALTE PORCARII

int main(int argc, char* args[])
{
	PlaySound(TEXT("Sounds/bgs"), NULL, SND_ASYNC);
	fopen_s(&Score_File_in, "prop/score.txt", "r");
	if (!Score_File_in)// !Score_File_out)
	{
		cout << "COULDN'T FIND THE SCORE FILE!"; return 0;
	}

	const int fps = 60;
	// max time between frames
	const int frameDelay = 1000 / fps;

	game->Initialize();				//Aici se genereaza toate texturile, windowul si rendererul

	Uint32 x;
	cout << game->GetPlayer()->GetScore();
	fscanf_s(Score_File_in, "%u",&x);
	if (x == 0xFFFFFFFF)
		x = 0;
	game->GetPlayer()->SetScore(x);
	x = 0;


	while (game->getGameState())
	{
		Uint32 frameStart = SDL_GetTicks();
			game->Render();
			game->Event();
			game->Update();

		const int frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->Clear();
	fclose(Score_File_in);
	game->SaveProgress("prop/score.txt","prop/catalog_prop.txt");
	delete[] game;
	TTF_Quit();
	SDL_Quit();
	return 0;
}
