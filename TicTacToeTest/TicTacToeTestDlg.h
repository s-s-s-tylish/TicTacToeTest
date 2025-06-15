
// TicTacToeTestDlg.h: файл заголовка
//

#pragma once
#include "CTicTacToeField.h"
#include "TicTacBoard.h"
#include "TicTacPlayer.h"
#include "TicTacHumanPlayer.h"
#include "TicTacComputerPlayer.h"


// Диалоговое окно CTicTacToeTestDlg
class CTicTacToeField;
class CTicTacToeTestDlg : public CDialogEx
{
// Создание
public:
	CTicTacToeTestDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TICTACTOETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	CTicTacToeField tttField;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnStartupOpen();
	void CreateBoard(int size);
	void CreatePlayer1(CString name, int type);
	void CreatePlayer2(CString name, int type);
	TicTacBoard* GetBoard();
	TicTacPlayer* GetCurrentPlayer();
private:
	TicTacBoard* board;
	TicTacPlayer* player1;
	TicTacPlayer* player2;
	TicTacPlayer* currentPlayer;
	bool bGameInProgress = false;
	void Cleanup();
	unsigned int moveCount = 0;
	void InvertBoard();
public:
	afx_msg void OnDestroy();
	void SetGameInProgress(bool inProgress);
	CButton mStartStopButton;
	CString strPlayerTurn;
	void UpdateName();
	void TogglePlayer();
};
