#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "SDLController.h"

SDLController::SDLController(int p_windowWidth, int p_windowHeight, const char* p_windowTitle, int p_cellSize, std::vector<std::vector<bool>>& p_current_board_state) : m_current_board_state(p_current_board_state)
{
	m_windowWidth = p_windowWidth;
	m_WindowHeight = p_windowHeight;
	m_cellSize = p_cellSize;
	
	m_window = nullptr;
	m_renderer = nullptr;
	
	m_cellRect.x = 0; 
	m_cellRect.y = 0;
	m_cellRect.w = m_cellSize;
	m_cellRect.h = m_cellSize;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init() failed!" << std::endl;
		SDL_Quit();
		exit(-1);
	}

	m_window = SDL_CreateWindow(p_windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_WindowHeight, SDL_WINDOW_OPENGL);
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

void SDLController::updateWindow(void)
{
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);	// Use a white background
	SDL_RenderClear(m_renderer);

	m_cellRect.x = 0;
	for (int x = 0; x < m_windowWidth / m_cellSize; x++)
	{
		for (int y = 0; y < m_WindowHeight / m_cellSize; y++)
		{
			bool cellValue = m_current_board_state[x][y];
			if (cellValue == true)	// If it is a live cell, fill black color
			{
				SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(m_renderer, &m_cellRect);
			}
			else // Else fill white color
			{
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderFillRect(m_renderer, &m_cellRect);
			}

			m_cellRect.y += m_cellSize;
		}
		m_cellRect.x += m_cellSize;
		m_cellRect.y = 0;
	}
	SDL_RenderPresent(m_renderer);
}
