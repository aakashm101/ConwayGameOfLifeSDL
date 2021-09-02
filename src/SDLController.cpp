#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "SDLController.h"

SDLController::SDLController(const char* p_windowTitle, int p_cellSize)
{
	m_cellSize = p_cellSize;	
	m_window = nullptr;
	m_renderer = nullptr;
	m_gol = nullptr;
	
	m_cellRect.x = 0; 
	m_cellRect.y = 0;
	m_cellRect.w = m_cellSize;
	m_cellRect.h = m_cellSize;

	SDL_DisplayMode dm;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init() failed!" << std::endl;
		SDL_Quit();
		exit(-1);
	}
	SDL_GetCurrentDisplayMode(0, &dm);
	m_windowWidth = dm.w;
	m_WindowHeight = dm.h;

	m_window = SDL_CreateWindow(p_windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_WindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	if (m_window == nullptr)
	{
		std::cout << "SDL_CreateWindow() failed!" << std::endl;
		SDL_Quit();
		exit(-1);
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer() failed!" << std::endl;
		SDL_Quit();
		exit(-1);
	}
}

void SDLController::updateWindow(void)
{
	const int MIN_THRESHOLD = 50;	// Minimum threshold for R,G,B values (Range: 0 to 255)

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);	// Use a white background
	SDL_RenderClear(m_renderer);

	m_cellRect.x = 0;
	for (int x = 0; x < m_windowWidth / m_cellSize; x++)
	{
		for (int y = 0; y < m_WindowHeight / m_cellSize; y++)
		{
			bool cellValue = m_gol->getCurrentBoardStateCellValue(x,y);
			if (cellValue == true)	// If it is a live cell, fill black color
			{
				SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(m_renderer, &m_cellRect);
			}
			else // Else fill white color
			{
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0x00);
				SDL_RenderFillRect(m_renderer, &m_cellRect);
			}

			m_cellRect.y += m_cellSize;
		}
		m_cellRect.x += m_cellSize;
		m_cellRect.y = 0;
	}

	// Draw the grid lines
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	for (int row = 0; row < m_WindowHeight; row = row + m_cellSize)	// Horizontal lines
	{
		SDL_RenderDrawLine(m_renderer, 0, row, m_windowWidth, row);
	}

	for (int col = 0; col < m_windowWidth; col = col + m_cellSize)	// Vertical lines
	{
		SDL_RenderDrawLine(m_renderer, col, 0, col, m_WindowHeight);
	}

	SDL_RenderPresent(m_renderer);
}


SDLController::~SDLController()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
	}
	SDL_Quit();
}