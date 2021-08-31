#pragma once
#include <vector>
#include <SDL.h>

class SDLController
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_cellSize;			// Used for the width and height of m_cellRect (A square target SDL_Rect on the SDL_Window)
	std::vector<std::vector<bool>>& m_current_board_state;
public:
	const int m_FPS = 30;
	const int m_FRAME_TIME_MILLISECONDS = 1000.0 / m_FPS;
	int m_windowWidth;
	int m_WindowHeight;
	SDL_Rect m_cellRect;	// Each cell is a square on the sdl window. This is the target SDL_Rect.

	SDLController(int p_windowWidth, int p_windowHeight, const char* p_windowTitle, int cellSize, std::vector<std::vector<bool>>& p_current_board_state);
	~SDLController();
	void updateWindow(void);
};

