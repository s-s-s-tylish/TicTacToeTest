#include "pch.h"
#include "TicTacBoard.h"
#include <iostream>
using namespace std;

// Конструктор и деструктор

TicTacBoard::TicTacBoard(unsigned int size)
{
    this->boardsize = size;
    cells = new CellType * [size];
    for (unsigned int i = 0; i < size; i++)
        cells[i] = new CellType[size];
    for (unsigned int i = 0; i < size; i++)
        for (unsigned int j = 0; j < size; j++)
            cells[i][j] = CellType_Empty;

}

TicTacBoard::~TicTacBoard()
{
    for (unsigned int i = 0; i < boardsize; i++)
        delete[] cells[i];
    delete[] cells;

}


void TicTacBoard::Show()
{
    cout << "  ";
    for (unsigned int j = 0; j < boardsize; j++)
        cout << j << " ";
    cout << endl;

    for (unsigned int i = 0; i < boardsize; i++)
    {
        cout << i << " ";
        for (unsigned int j = 0; j < boardsize; j++)
        {
            switch (cells[i][j])
            {
            case CellType_X:
                cout << "X";
                break;
            case CellType_O:
                cout << "O";
                break;
            case CellType_Empty:
                cout << "-";
                break;
            }
            cout << " ";
        }
        cout << endl;
    }
}

void TicTacBoard::SetCell(unsigned int xpos, unsigned int ypos, CellType ct)
{
    cells[ypos][xpos] = ct;
}


bool TicTacBoard::CheckLegal(unsigned int xpos, unsigned int ypos) {
    if (xpos >= boardsize || ypos >= boardsize) 
        return false;
    return (cells[ypos][xpos] == CellType_Empty);
}

bool TicTacBoard::IsRowMade(unsigned int row)
{
    for (unsigned int i = 0; i <= boardsize - 4; ++i) {
        CellType current = cells[row][i];
        if (current == CellType_Empty) continue;

        bool isWin = true;
        for (int j = 0; j < 4; ++j) {
            if (cells[row][i + j] != current) {
                isWin = false;
                break;
            }
        }
        if (isWin) {
            bVictory = true;
            return true;
        }
    }
    return false;
}


bool TicTacBoard::IsColumnMade(unsigned int col)
{
    for (unsigned int i = 0; i <= boardsize - 4; ++i) {
        CellType current = cells[i][col];
        if (current == CellType_Empty) continue;

        bool isWin = true;
        for (int j = 0; j < 4; ++j) {
            if (cells[i + j][col] != current) {
                isWin = false;
                break;
            }
        }
        if (isWin) {
            bVictory = true;
            return true;
        }
    }
    return false;
}


bool TicTacBoard::IsDiagMade()
{
    // Проверка диагоналей: сверху-вниз вправо
    for (unsigned int i = 0; i <= boardsize - 4; ++i) {
        for (unsigned int j = 0; j <= boardsize - 4; ++j) {
            CellType current = cells[i][j];
            if (current == CellType_Empty) continue;

            bool isWin = true;
            for (int k = 0; k < 4; ++k) {
                if (cells[i + k][j + k] != current) {
                    isWin = false;
                    break;
                }
            }
            if (isWin) {
                bVictory = true;
                return true;
            }
        }
    }

    // Проверка диагоналей: сверху-вниз влево
    for (unsigned int i = 0; i <= boardsize - 4; ++i) {
        for (unsigned int j = 3; j < boardsize; ++j) {
            CellType current = cells[i][j];
            if (current == CellType_Empty) continue;

            bool isWin = true;
            for (int k = 0; k < 4; ++k) {
                if (cells[i + k][j - k] != current) {
                    isWin = false;
                    break;
                }
            }
            if (isWin) {
                bVictory = true;
                return true;
            }
        }
    }

    return false;
}


bool TicTacBoard::IsBoardFull() {
    for (unsigned int i = 0; i < boardsize; i++) {
        for (unsigned int j = 0; j < boardsize; j++) {
            if (cells[i][j] == CellType_Empty)
                return false;
        }
    }
    return true;
}

bool TicTacBoard::CheckEndCondition() {
    bVictory = false;

    // Проверка строк и столбцов
    for (unsigned int i = 0; i < boardsize; i++) {
        if (IsRowMade(i) || IsColumnMade(i)) {
            bVictory = true;
            return true;
        }
    }

    if (IsDiagMade()) {
        bVictory = true;
        return true;
    }

    return IsBoardFull();
}

bool TicTacBoard::IsVictory() {
    return bVictory;
}

TicTacBoard::TicTacBoard(TicTacBoard* board)
{
    this->boardsize = board->boardsize;
    cells = new CellType * [boardsize];
    for (unsigned int i = 0; i < boardsize; i++)
        cells[i] = new CellType[boardsize];
    for (unsigned int i = 0; i < boardsize; i++)
        for (unsigned int j = 0; j < boardsize; j++)
            cells[i][j] = board->cells[i][j];
}


CellType TicTacBoard::GetCell(unsigned int xpos, unsigned int ypos)
{
    return cells[ypos][xpos];
}
unsigned int TicTacBoard::GetBoardSize()
{
    return boardsize;
}

void TicTacBoard::ClearBoard()
{
    for (unsigned int i = 0; i < boardsize; i++)
        for (unsigned int j = 0; j < boardsize; j++)
            cells[i][j] = CellType_Empty;
}