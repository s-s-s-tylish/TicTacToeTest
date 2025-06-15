#include "pch.h"
#include "TicTacPlayer.h"
#include <iostream>
using namespace std;

// Конструктор и деструктор

TicTacPlayer::TicTacPlayer()
{

}

TicTacPlayer::~TicTacPlayer()
{

}

void TicTacPlayer::SetupPlayer(CString name, CellType celltype)
{
	this->name = name;
	this->celltype = celltype;
}

void TicTacPlayer::SetBoard(TicTacBoard* board)
{
	this->board = board;
}


CString TicTacPlayer::GetName()
{
	return this->name;
}

CellType TicTacPlayer::GetCurrentCellType() const {
	return celltype;
}

void TicTacPlayer::SetCellType(CellType newType) {
	this->celltype = newType;
}