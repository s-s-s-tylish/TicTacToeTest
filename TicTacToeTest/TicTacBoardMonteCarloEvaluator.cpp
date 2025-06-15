#include "pch.h"
#include "TicTacBoardMonteCarloEvaluator.h"
#include "TicTacRandomPlayer.h"
#include <iostream>


using namespace std;

TicTacBoardMonteCarloEvaluator::TicTacBoardMonteCarloEvaluator(TicTacBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->xpos = xpos;
	this->ypos = ypos;
	this->startCellType = startCellType;
}

TicTacBoardMonteCarloEvaluator::~TicTacBoardMonteCarloEvaluator()
{

}

void TicTacBoardMonteCarloEvaluator::EvaluateBoard()
{
	TicTacBoard* b = new TicTacBoard(this->board);
	TicTacRandomPlayer* player1 = new TicTacRandomPlayer();
	TicTacRandomPlayer* player2 = new TicTacRandomPlayer();
	TicTacRandomPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->SetupPlayer(L"RandomX", CellType_X);
	player2->SetupPlayer(L"RandomO", CellType_O);
	player1->SetBoard(b);
	player2->SetBoard(b);
	currentPlayer = (this->startCellType == CellType_X) ? player1 : player2;

	// Checking already end condition!
	if (b->CheckEndCondition())
	{
		if (b->IsVictory())
			if (currentPlayer == player1)
				numLosses++;
			else
				numVictories++;
		else
			numDraws++;
		bGameFinished = true;
		delete b;
		delete player1;
		delete player2;
		return;
	}

	while (!bGameFinished)
	{
		while (!currentPlayer->MakeMove(0,0));

		if (b->CheckEndCondition())
		{
			if (b->IsVictory())
				if (currentPlayer == player1)
					numVictories++;
				else
					numLosses++;
			else
				numDraws++;
		}

		bGameFinished = true;
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
	delete b;
	delete player1;
	delete player2;
}


void TicTacBoardMonteCarloEvaluator::Evaluate()
{
	for (int i = 0; i < numGames; i++)
		EvaluateBoard();
}


