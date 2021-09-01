#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GameOfLife.h"
#include "SDLController.h"

int main(void)
{
	const int MIN_CELL_SIZE = 5;
	const int MAX_CELL_SIZE = 25;
	const int DEFAULT_CELL_SIZE = 8;
	bool running;
	int cellSize; // Uses a SDL_Rect of dimensions cellSize*cellSize pixels to render each cell of the simulation on the SDL_Window
	Uint32 frameDelay;

	SDL_SetMainReady();

	std::cout << "IMPORTANT: Press ESCAPE key to exit fullscreen mode and stop the simulation.\n" << std::endl;
	std::cout << "Enter the cell size [MIN:" << MIN_CELL_SIZE << ", MAX:" << MAX_CELL_SIZE << ", DEFAULT:" << DEFAULT_CELL_SIZE << "]: ";
	std::cin >> cellSize;
	if (cellSize < MIN_CELL_SIZE || cellSize > MAX_CELL_SIZE)
	{
		std::cout << "Invalid Input!" << std::endl;
		std::cout << "Using default cell size value: " << DEFAULT_CELL_SIZE << std::endl;
		cellSize = DEFAULT_CELL_SIZE;
	}

	SDLController sdlController("Conway game of life using SDL - by Aakash.M", cellSize);
	GameOfLife gol(sdlController.m_windowWidth / cellSize, sdlController.m_WindowHeight / cellSize);
	sdlController.m_gol = &gol; // Pass the bool value on a cell in m_board_current_state from GameOfLife class to SDLController class

	running = true;
	while (running)
	{
		SDL_Event e;
		Uint32 frameStart = SDL_GetTicks();

		if (SDL_PollEvent(&e) > 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				running = false;
				break;
			}
		}
		
		// Goto next state after rendering each frame
		sdlController.updateWindow();
		gol.nextState();

		// Used to refresh the window at a stable FPS
		frameDelay = SDL_GetTicks() - frameStart;
		if (frameDelay < sdlController.m_FRAME_TIME_MILLISECONDS)
		{
			SDL_Delay(sdlController.m_FRAME_TIME_MILLISECONDS - frameDelay);
		}
	}
	return 0;
}