// CTicTacToeField.cpp: файл реализации
//

#include "pch.h"
#include "TicTacToeTest.h"
#include "CTicTacToeField.h"
#define TICTACTOEFIELD_CLASSNAME L"TicTacToeField"
#define FIELDNUMBERSPACE 20
#define TIMER_ID 101

// CTicTacToeField

IMPLEMENT_DYNAMIC(CTicTacToeField, CWnd)

CTicTacToeField::CTicTacToeField()
{
	fieldSize = 10;
	gameParent = nullptr;
	this->RegisterClass();	
	nSelectedX = -1;
	nSelectedY = -1;
}

CTicTacToeField::~CTicTacToeField()
{
}


BEGIN_MESSAGE_MAP(CTicTacToeField, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// Обработчики сообщений CTicTacToeField




bool CTicTacToeField::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, TICTACTOEFIELD_CLASSNAME, &wndcls)))
	{
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = TICTACTOEFIELD_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return false;
		}
	}

	// TODO: Добавьте сюда код реализации.
	return true;
}


void CTicTacToeField::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CWnd::OnPaint() для сообщений рисования

	CRect rect;
	GetClientRect(&rect);
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;
	int fieldSize = this->gameParent->GetBoard()->GetBoardSize();

	CPen ourPen;
	ourPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(ourPen);

	int hPartSize = (rect.right - FIELDNUMBERSPACE) / fieldSize;
	int vPartSize = (rect.bottom - FIELDNUMBERSPACE) / fieldSize;
	
	this->HighlightSelection(dc);

	for (int i = 0; i < fieldSize + 1; i++)
	{
		dc.MoveTo(FIELDNUMBERSPACE + i * hPartSize, FIELDNUMBERSPACE);
		dc.LineTo(FIELDNUMBERSPACE + i * hPartSize, rect.bottom);
		dc.MoveTo(FIELDNUMBERSPACE, i * vPartSize + FIELDNUMBERSPACE);
		dc.LineTo(rect.right, i * vPartSize + FIELDNUMBERSPACE);
	}

	dc.SetTextColor(RGB(0, 0, 255));
	dc.SetTextAlign(TA_TOP | TA_LEFT);
	dc.SetBkMode(TRANSPARENT);

	for (int i = 0; i < fieldSize; i++)
	{
		CString str;
		str.Format(L"%d", i);
		dc.TextOutW(0, FIELDNUMBERSPACE / 2 + vPartSize / 2 + i * vPartSize, str);
		dc.TextOutW(FIELDNUMBERSPACE / 2 + hPartSize / 2 + i * hPartSize, 0, str);
	}

	for (int x = 0; x < fieldSize; x++)
		for (int y = 0; y < fieldSize ; y++)
		{
			if (this->gameParent->GetBoard()->GetCell(x,y) == CellType_X)
				this->DrawX(dc, this->GetRectFromField(x, y));
			if (this->gameParent->GetBoard()->GetCell(x, y) == CellType_O)
				this->DrawO(dc, this->GetRectFromField(x, y));
		}

	ourPen.DeleteObject();
}

void CTicTacToeField::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CRect clientRect;
	GetClientRect(&clientRect);
	CString str;

	if ((bGameInProgress) && (this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((gameParent == nullptr) || (gameParent->GetBoard() == nullptr))
			return;
		int x, y;
		
		this->GetFieldPosition(point, x, y);
		if (this->gameParent->GetCurrentPlayer()->MakeMove(x, y) == true)
		{
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				this->gameParent->TogglePlayer();
			}
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CTicTacToeField::GetFieldPosition(CPoint point, int& xpos, int& ypos)
{
    CRect rect;
    if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
        return;

    GetClientRect(&rect);
    int boardSize = this->gameParent->GetBoard()->GetBoardSize(); // Используем актуальный размер
    int hPartSize = (rect.right - FIELDNUMBERSPACE) / boardSize;
    int vPartSize = (rect.bottom - FIELDNUMBERSPACE) / boardSize;

    xpos = ypos = -1;

    for (int i = 0; i < boardSize; i++)
    {
        if ((point.x > FIELDNUMBERSPACE + i * hPartSize) && 
            (point.x < FIELDNUMBERSPACE + (i + 1) * hPartSize))
            xpos = i;
        if ((point.y > FIELDNUMBERSPACE + i * vPartSize) && 
            (point.y < FIELDNUMBERSPACE + (i + 1) * vPartSize))
            ypos = i;
    }
}


CRect CTicTacToeField::GetRectFromField(int x, int y)
{
    CRect rectWnd;
    GetClientRect(&rectWnd);
    if ((gameParent == nullptr) || (gameParent->GetBoard() == nullptr))
        return CRect(0, 0, 0, 0);

    int fieldSize = gameParent->GetBoard()->GetBoardSize(); // Актуальный размер
    int hPartSize = (rectWnd.right - FIELDNUMBERSPACE) / fieldSize;
    int vPartSize = (rectWnd.bottom - FIELDNUMBERSPACE) / fieldSize;

    CRect rect(
        FIELDNUMBERSPACE + x * hPartSize + 1,
        FIELDNUMBERSPACE + y * vPartSize + 1,
        FIELDNUMBERSPACE + (x + 1) * hPartSize + 1,
        FIELDNUMBERSPACE + (y + 1) * vPartSize + 1
    );
    return rect;
}


void CTicTacToeField::DrawX(CPaintDC& dc, CRect rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));	
	HGDIOBJ oldPen = dc.SelectObject(pen);

	dc.MoveTo(rect.left + 4, rect.top + 4);
	dc.LineTo(rect.right - 4, rect.bottom - 4);
	dc.MoveTo(rect.right - 4, rect.top + 4);
	dc.LineTo(rect.left + 4, rect.bottom - 4);

	dc.SelectObject(oldPen);
	pen.DeleteObject();
}



void CTicTacToeField::DrawO(CPaintDC& dc, CRect rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	HGDIOBJ oldBrush = dc.SelectObject(GetStockObject(HOLLOW_BRUSH));

	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);

	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

	pen.DeleteObject();
}


void CTicTacToeField::HighlightSelection(CPaintDC& dc)
{
	if ((nSelectedX < 0) || nSelectedY < 0)
		return;

	CRect rect = GetRectFromField(nSelectedX, nSelectedY);
	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 249, 255));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldBrush);
	brush.DeleteObject();

}


void CTicTacToeField::OnMouseMove(UINT nFlags, CPoint point)
{
	int x, y;

	GetFieldPosition(point, x, y);
	if ((nSelectedX != x) || (nSelectedY != y))
	{
		nSelectedX = x;
		nSelectedY = y;
		this->Invalidate();
	}

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->m_hWnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;

	TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
	CWnd::OnMouseMove(nFlags, point);
}




void CTicTacToeField::OnMouseLeave()
{
	nSelectedX = -1;
	nSelectedY = -1;
	this->Invalidate();

	CWnd::OnMouseLeave();
}

void CTicTacToeField::SetGameParent(CTicTacToeTestDlg* p)
{
	this->gameParent = p;
}

void CTicTacToeField::SetGameInProgress(bool inProgress)
{
	if (bGameInProgress != inProgress)
	{
		this->bGameInProgress = inProgress;
		this->gameParent->SetGameInProgress(inProgress);
		if (inProgress)
			SetTimer(TIMER_ID, 1000, NULL);
		else
			KillTimer(TIMER_ID);
	}
}

bool CTicTacToeField::CheckEndCondition()
{
	if (this->gameParent->GetBoard()->CheckEndCondition())
	{
		if (this->gameParent->GetBoard()->IsVictory())
		{
			CString str;
			str.Format(L"Игрок %s победил! Ура!", this->gameParent->GetCurrentPlayer()->GetName());
			AfxMessageBox(str);
		}
		else
		{
			AfxMessageBox(L"Ничья! Увы!");
		}
		return true;
	}
	return false;
}

void CTicTacToeField::OnTimer(UINT_PTR nIDEvent)
{
	if ((bGameInProgress) && (!this->gameParent->GetCurrentPlayer()->IsHuman()))
	{

		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;

		if (this->gameParent->GetCurrentPlayer()->MakeMove(0, 0) == true)
		{
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				this->gameParent->TogglePlayer();
			}
		}

		this->Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}
