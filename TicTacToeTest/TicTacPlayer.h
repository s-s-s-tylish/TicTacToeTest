#pragma once
#include "TicTacBoard.h"
#include <string>
#include <conio.h>
using namespace std;

class TicTacPlayer
{
protected:
	TicTacBoard* board;
	CellType celltype;
	CString name;
public:
	TicTacPlayer();
	virtual ~TicTacPlayer();
	void SetupPlayer(CString name, CellType celltype);
	void SetBoard(TicTacBoard* board);
	virtual bool MakeMove(unsigned int col, unsigned int row) = 0;
	virtual bool IsHuman() = 0;
	CString GetName();
	void SetCellType(CellType newType);
	CellType GetCurrentCellType() const;
};

