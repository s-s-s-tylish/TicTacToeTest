#pragma once
#include "TicTacToeTestDlg.h"

// CTicTacToeField
class CTicTacToeTestDlg;
class CTicTacToeField : public CWnd
{
	DECLARE_DYNAMIC(CTicTacToeField)

public:
	CTicTacToeField();
	virtual ~CTicTacToeField();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterClass();
public:
	afx_msg void OnPaint();
private:
	int fieldSize;
public:
	// Установка размера игрового поля
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	void GetFieldPosition(CPoint point, int& xpos, int& ypos);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
	CRect GetRectFromField(int x, int y);
public:
	void DrawX(CPaintDC& dc, CRect rect);
	void DrawO(CPaintDC& dc, CRect rect);
private:
	int nSelectedX = -1;
	int nSelectedY = -1;
	bool bGameInProgress = false;
	CTicTacToeTestDlg* gameParent;
	void HighlightSelection(CPaintDC& dc);
public:
	void SetGameParent(CTicTacToeTestDlg* p);
	void SetGameInProgress(bool inProgress);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	bool CheckEndCondition();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


