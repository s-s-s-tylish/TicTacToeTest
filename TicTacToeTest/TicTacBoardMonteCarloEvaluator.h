#pragma once
#include "TicTacBoard.h"
#include "TicTacManager.h"

class TicTacBoardMonteCarloEvaluator
{
private:
	TicTacBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int xpos, ypos;
	CellType startCellType;
public:
	TicTacBoardMonteCarloEvaluator(TicTacBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos);
	~TicTacBoardMonteCarloEvaluator();
	void Evaluate();
	void EvaluateBoard();
	int GetVictories() { return numVictories; }
	int GetLosses() { return numLosses; }
	int GetDraws() { return numDraws; }
	int GetXPos() { return xpos; }
	int GetYPos() { return ypos; }
};

