// #include <windows.h>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GameOfLife.h"
#include "SDLController.h"

int main(void)
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	const int CELL_SIZE = 10;	// Uses a SDL_Rect of dimensions CELL_SIZE*CELL_SIZE pixels to render each cell of the simulation on the SDL_Window
	bool running;
	
	SDL_SetMainReady();

	GameOfLife gol(WINDOW_WIDTH / CELL_SIZE, WINDOW_HEIGHT / CELL_SIZE);
	// gol.displayCurrentBoardData();

	/*
	while (1)
	{
		Sleep(50);
		std::system("cls");
		gol.nextState();
		gol.displayCurrentBoardData();
	}
	*/

	SDLController sdlController(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway game of life using SDL - by Aakash.M", CELL_SIZE, gol.getCurrentBoardState());
	running = true;
	while (running)
	{
		SDL_Event e;
		
		if (SDL_PollEvent(&e) > 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				running = false;
			}
		}
		
		gol.nextState();
		sdlController.updateWindow();

		SDL_Delay(sdlController.m_FRAME_TIME_MILLISECONDS);
	}

	return 0;
}