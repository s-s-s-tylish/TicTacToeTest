#include "pch.h"
#include "TicTacRandomPlayer.h"
#include <iostream>

TicTacRandomPlayer::TicTacRandomPlayer()
{

}

TicTacRandomPlayer::~TicTacRandomPlayer()
{

}

bool TicTacRandomPlayer::MakeMove(unsigned int col, unsigned int row)
{
	row = (unsigned int)(rand() % 6);
	col = (unsigned int)(rand() % 6);

	if (this->board->CheckLegal(col, row))
	{
		this->board->SetCell(col, row, this->celltype);
		return true;
	};

	return false;

}

bool TicTacRandomPlayer::IsHuman()
{
	return false;
}