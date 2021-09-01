#pragma once
#include <vector>

class GameOfLife
{
private:
	int m_rows;
	int m_cols;
	std::vector<std::vector<bool>> m_board_current_state;
	std::vector<std::vector<bool>> m_board_next_state;

	int getNeighbourCount(int i, int j);
public:
	GameOfLife(const int p_rows, const int p_cols);
	void nextState(void);
	bool getCurrentBoardStateCellValue(int x, int y);
};