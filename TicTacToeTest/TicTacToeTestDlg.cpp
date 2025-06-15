
// TicTacToeTestDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "TicTacToeTest.h"
#include "TicTacToeTestDlg.h"
#include "CTicTacToeField.h"
#include "afxdialogex.h"
#include "CStartupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CTicTacToeTestDlg



CTicTacToeTestDlg::CTicTacToeTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TICTACTOETEST_DIALOG, pParent)
	, strPlayerTurn(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	board = nullptr;
	player1 = nullptr;
	player2 = nullptr;
	currentPlayer = nullptr;
}

void CTicTacToeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TICTACTOEFIELD, tttField);
	DDX_Control(pDX, IDC_BUTTON_CLEAR_FIELDS, mStartStopButton);
	DDX_Text(pDX, IDC_STATIC3, strPlayerTurn);
}

BEGIN_MESSAGE_MAP(CTicTacToeTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_FIELDS, &CTicTacToeTestDlg::OnBnStartupOpen)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Обработчики сообщений CTicTacToeTestDlg

BOOL CTicTacToeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	tttField.SetGameParent(this);

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTicTacToeTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTicTacToeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTicTacToeTestDlg::OnBnStartupOpen()
{
	if (bGameInProgress)
	{
		Cleanup();
		this->SetGameInProgress(false);
		this->Invalidate();
	}
	else
	{
		CStartupDlg sdlg;
		sdlg.SetDlgParent(this);
		int nRes = sdlg.DoModal();

		if (nRes == IDOK)
		{
			moveCount = 0;
			currentPlayer = player1;
			this->SetGameInProgress(true);
			this->UpdateName();
			this->Invalidate();

		}
	}
	
}

void CTicTacToeTestDlg::CreateBoard(int size)
{
	this->board = new TicTacBoard(10);
}

void CTicTacToeTestDlg::CreatePlayer1(CString name, int type)
{
	if (type == 0)
		this->player1 = new TicTacHumanPlayer();
	else
		this->player1 = new TicTacComputerPlayer();
	player1->SetupPlayer(name, CellType_X);
	player1->SetBoard(this->board);
}

void CTicTacToeTestDlg::CreatePlayer2(CString name, int type)
{
	if (type == 0)
		this->player2 = new TicTacHumanPlayer();
	else
		this->player2 = new TicTacComputerPlayer();
	player2->SetupPlayer(name, CellType_O);
	player2->SetBoard(this->board);

}

TicTacBoard* CTicTacToeTestDlg::GetBoard()
{
	return board;
}

TicTacPlayer* CTicTacToeTestDlg::GetCurrentPlayer()
{
	return currentPlayer;
}

void CTicTacToeTestDlg::Cleanup()
{
	if (player1 != nullptr)
	{
		delete player1;
		player1 = nullptr;
	}

	if (player2 != nullptr)
	{
		delete player2;
		player2 = nullptr;
	}

	if (board != nullptr)
	{
		delete board;
		board = nullptr;
	}
	currentPlayer = nullptr;
}

void CTicTacToeTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	Cleanup();

	// TODO: добавьте свой код обработчика сообщений
}

void CTicTacToeTestDlg::SetGameInProgress(bool inProgress)
{
	this->bGameInProgress = inProgress;
	this->tttField.SetGameInProgress(inProgress);
	if (inProgress)
	{
		mStartStopButton.SetWindowTextW(L"Остановить");
	}
	else
	{
		mStartStopButton.SetWindowTextW(L"Запустить");
		Cleanup();
		moveCount = 0;
	}
}

void CTicTacToeTestDlg::UpdateName()
{
	CString str;
	str.Format(L"Ход игрока: %s", currentPlayer->GetName());
	strPlayerTurn = str;
	UpdateData(false);
}

void CTicTacToeTestDlg::TogglePlayer()
{
	moveCount++; // Увеличиваем счетчик ходов

	if (moveCount % 4 == 0) { // Каждые 4 хода
		InvertBoard();
	}

	if (currentPlayer != player1)
		currentPlayer = player1;
	else
		currentPlayer = player2;
	UpdateName();
}

void CTicTacToeTestDlg::InvertBoard() {
	if (!board) return;

	// Инверсия клеток
	for (unsigned int i = 0; i < board->GetSize(); i++) {
		for (unsigned int j = 0; j < board->GetSize(); j++) {
			CellType current = board->GetCell(j, i);
			if (current == CellType_X) {
				board->SetCell(j, i, CellType_O);
			}
			else if (current == CellType_O) {
				board->SetCell(j, i, CellType_X);
			}
		}
	}

	// Инверсия символов игроков через метод
	if (player1) {
		player1->SetCellType((player1->GetCurrentCellType() == CellType_X) ? CellType_O : CellType_X);
	}
	if (player2) {
		player2->SetCellType((player2->GetCurrentCellType() == CellType_X) ? CellType_O : CellType_X);
	}

	tttField.Invalidate();
}