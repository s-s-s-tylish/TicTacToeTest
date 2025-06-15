#pragma once
#include "afxdialogex.h"
#include "TicTacToeTestDlg.h"


// Диалоговое окно CStartupDlg

class CStartupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartupDlg)

public:
	CStartupDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CStartupDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CString strSizeEdit;
private:
	// CString strPlayerName1;
	CString strPlayerName1;
	// CString strPlayerName2;
	CString strPlayerName2;
	CComboBox mTypePlayer1;
	CComboBox mTypePlayer2;
	CTicTacToeTestDlg* dlgParent;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStartbutton();
	void SetDlgParent(CTicTacToeTestDlg* p);
};
