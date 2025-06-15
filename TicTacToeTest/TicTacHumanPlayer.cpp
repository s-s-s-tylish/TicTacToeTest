#include "pch.h"
#include "TicTacHumanPlayer.h"
#include <iostream>
using namespace std;

// Конструктор и деструктор

TicTacHumanPlayer::TicTacHumanPlayer()
{

}

TicTacHumanPlayer::~TicTacHumanPlayer()
{

}


bool TicTacHumanPlayer::MakeMove(unsigned int col, unsigned int row)
{
	cout << "Игрок " << name << ", ваш ход..." << endl;
	cout << "Введите строку: ";
	cin >> row;
	cout << "Введите столбец: ";
	cin >> col;

	if (this->board->CheckLegal(col, row))
	{
		this->board->SetCell(col, row, this->celltype);
		return true;
	}
};

bool TicTacHumanPlayer::IsHuman()
{
	return true;
}