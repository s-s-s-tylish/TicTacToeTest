#include "pch.h"
#include "TicTacManager.h"
#include "TicTacComputerPlayer.h"
#include "TicTacHumanPlayer.h"
#include <iostream>

// Конструктор и деструктор

TicTacManager::TicTacManager()
{

}

TicTacManager::~TicTacManager()
{
    delete[] this->player2;
    delete[] this->player1;
    delete[] this->board;
}

bool TicTacManager::Init()
{
    return true;
}

void TicTacManager::ShowBoard()
{
    this->board->Show();
}

void TicTacManager::MakeMove()
{
    ShowBoard();
    unsigned int col = 0, row = 0;
    while (!currentPlayer->MakeMove(0, 0))
    {
        cout << "Недопустимый ход, попробуйте ещё раз" << endl;
        ShowBoard();
    }

    if (this->board->CheckEndCondition())
    {
        if (this->board->IsVictory())
            cout << "Игрок " << currentPlayer->GetName() << " победил!" << endl;
        else
            cout << "Ничья!" << endl;
        this->bGameFinished = true;
        ShowBoard();
        return;
    }
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool TicTacManager::IsGameFinished()
{
    return bGameFinished;
}