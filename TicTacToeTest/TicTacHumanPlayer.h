#pragma once
#include "TicTacBoard.h"
#include "TicTacPlayer.h"
#include <string>

using namespace std;

class TicTacHumanPlayer: public TicTacPlayer
{
public:
	TicTacHumanPlayer();
	virtual ~TicTacHumanPlayer();
	virtual bool MakeMove(unsigned int col, unsigned int row) override;
	virtual bool IsHuman();

};

