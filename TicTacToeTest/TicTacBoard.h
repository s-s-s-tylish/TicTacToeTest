#pragma once
#include "CellType.h"

class TicTacBoard
{
private:
	unsigned int boardsize;
	CellType** cells;
	bool bVictory = false;
	bool IsRowMade(unsigned int row);
	bool IsColumnMade(unsigned int col);
	bool IsDiagMade();
	bool IsBoardFull();
public:
	TicTacBoard(unsigned int boardsize);
	TicTacBoard(TicTacBoard* board);
	virtual ~TicTacBoard();
	void Show();
	void SetCell(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegal(unsigned int xpos, unsigned int ypos);
	bool CheckEndCondition();
	bool IsVictory();
	unsigned int GetSize() const { return boardsize; }
	CellType GetCell(unsigned int xpos, unsigned int ypos);
	unsigned int GetBoardSize();
	void ClearBoard();
};

