#pragma once
#include <vector>
#include <SDL.h>
#include "GameOfLife.h"

class SDLController
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_cellSize;			// Used for the width and height of m_cellRect (A square target SDL_Rect on the SDL_Window)
public:
	const int m_FPS = 30;
	const int m_FRAME_TIME_MILLISECONDS = 1000.0 / m_FPS;
	int m_windowWidth;
	int m_WindowHeight;
	SDL_Rect m_cellRect;	// Each cell is a square on the sdl window. This is the target SDL_Rect.
	GameOfLife* m_gol;

	SDLController(const char* p_windowTitle, int p_cellSize);
	~SDLController();
	void updateWindow(void);
};

