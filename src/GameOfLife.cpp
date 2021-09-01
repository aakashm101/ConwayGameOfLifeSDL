#include <iostream>
#include <vector>
#include <random>
#include "GameOfLife.h"

GameOfLife::GameOfLife(const int p_rows, const int p_cols)
{
	std::vector<bool> rowVector;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

	m_rows = p_rows;
	m_cols = p_cols;

	for (int i = 0; i < m_rows; i++)
	{
		rowVector.clear();
		for (int j = 0; j < m_cols; j++)
		{
			rowVector.push_back(dist(mt));
		}
		m_board_current_state.push_back(rowVector);
	}
	m_board_next_state = m_board_current_state;
}

void GameOfLife::nextState(void)
{
	int liveNeighbourCount;
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			liveNeighbourCount = getNeighbourCount(i, j);
			if (m_board_current_state[i][j] == true && (liveNeighbourCount == 2 || liveNeighbourCount == 3))
			{
				m_board_next_state[i][j] = true;
			}
			else if (m_board_current_state[i][j] == false && liveNeighbourCount == 3)
			{
				m_board_next_state[i][j] = true;
			}
			else
			{
				m_board_next_state[i][j] = false;
			}
		}
	}
	m_board_current_state = m_board_next_state;
}

int GameOfLife::getNeighbourCount(int row, int col)
{
	int neighbourCount;
	int wrapped_row, wrapped_col;

	neighbourCount = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			wrapped_row = (row + i + m_rows) % m_rows;
			wrapped_col = (col + j + m_cols) % m_cols;
			if (m_board_current_state[wrapped_row][wrapped_col] == true)
			{
				neighbourCount++;
			}
		}
	}

	if (m_board_current_state[row][col] == true)
	{
		neighbourCount--;
	}

	return neighbourCount;
}

bool GameOfLife::getCurrentBoardStateCellValue(int x, int y)
{
	return m_board_current_state[x][y];
}
