#include "pch.h"
#include "TicTacHumanPlayer.h"
#include <iostream>
using namespace std;

// ����������� � ����������

TicTacHumanPlayer::TicTacHumanPlayer()
{

}

TicTacHumanPlayer::~TicTacHumanPlayer()
{

}


bool TicTacHumanPlayer::MakeMove(unsigned int col, unsigned int row)
{
	cout << "����� " << name << ", ��� ���..." << endl;
	cout << "������� ������: ";
	cin >> row;
	cout << "������� �������: ";
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