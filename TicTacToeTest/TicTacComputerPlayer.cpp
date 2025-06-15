#include "pch.h"
#include "TicTacComputerPlayer.h"
#include "TicTacBoardMonteCarloEvaluator.h"
#include <iostream>
#include <vector>
#include <conio.h>


using namespace std;

// Конструктор и деструктор

TicTacComputerPlayer::TicTacComputerPlayer()
{

}

TicTacComputerPlayer::~TicTacComputerPlayer()
{

}

// Вспомогательная функция для проверки немедленной победы/блокировки
bool CheckImmediateOpportunity(TicTacBoard* board, CellType targetType, unsigned int& x, unsigned int& y) {
	unsigned int size = board->GetSize();
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < size; j++) {
			if (board->CheckLegal(j, i)) {
				board->SetCell(j, i, targetType);
				if (board->CheckEndCondition() && board->IsVictory()) {
					board->SetCell(j, i, CellType_Empty); // Возвращаем исходное состояние
					x = j;
					y = i;
					return true;
				}
				board->SetCell(j, i, CellType_Empty);
			}
		}
	}
	return false;
}



bool TicTacComputerPlayer::MakeMove(unsigned int col, unsigned int row) {
    if (this->board->CheckEndCondition()) {
        return false;
    }

    unsigned int bestX = 0, bestY = 0;
    double bestScore = -INFINITY;
    CellType opponentType = (this->celltype == CellType_X) ? CellType_O : CellType_X;

    // 1. Проверка на немедленную победу/блокировку
    if (CheckImmediateOpportunity(this->board, this->celltype, bestX, bestY) ||
        CheckImmediateOpportunity(this->board, opponentType, bestX, bestY)) {
        this->board->SetCell(bestX, bestY, this->celltype);
        return true;
    }

    // 2. Монте-Карло с прямым перебором клеток
    const int MONTE_CARLO_ITERATIONS = 1000; // Увеличено для сложности
    const int BOARD_SIZE = board->GetSize();

    for (unsigned int x = 0; x < BOARD_SIZE; x++) {
        for (unsigned int y = 0; y < BOARD_SIZE; y++) {
            if (!board->CheckLegal(x, y)) continue;

            // Временное установление символа
            board->SetCell(x, y, this->celltype);

            TicTacBoardMonteCarloEvaluator evaluator(
                board,
                MONTE_CARLO_ITERATIONS,
                opponentType,
                x,
                y
            );
            evaluator.Evaluate();

            // Возврат исходного состояния
            board->SetCell(x, y, CellType_Empty);

            // Расчет весов (усилены штрафы за поражения)
            double score = evaluator.GetVictories() * 2.0
                - evaluator.GetLosses() * 3.0
                + evaluator.GetDraws() * 0.5;

            // Учет центральных клеток (доп. сложность)
            if (x >= 3 && x <= 6 && y >= 3 && y <= 6) score *= 1.2;

            if (score > bestScore) {
                bestScore = score;
                bestX = x;
                bestY = y;
            }
        }
    }
    // 3. Резервный случайный ход
    if (bestScore <= 0) {
        do {
            bestX = rand() % BOARD_SIZE;
            bestY = rand() % BOARD_SIZE;
        } while (!board->CheckLegal(bestX, bestY));
    }

    board->SetCell(bestX, bestY, this->celltype);
    return true;
}

bool TicTacComputerPlayer::IsHuman()
{
    return false;
}