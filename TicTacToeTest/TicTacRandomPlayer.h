#pragma once
#include "TicTacPlayer.h"
class TicTacRandomPlayer: public TicTacPlayer
{
public:
	TicTacRandomPlayer();
	virtual ~TicTacRandomPlayer();
	virtual bool MakeMove(unsigned int col, unsigned int row) override;
	virtual bool IsHuman();
};

