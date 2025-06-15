// CStartupDlg.cpp: файл реализации
//

#include "pch.h"
#include "TicTacToeTest.h"
#include "afxdialogex.h"
#include "CStartupDlg.h"


// Диалоговое окно CStartupDlg

IMPLEMENT_DYNAMIC(CStartupDlg, CDialogEx)

CStartupDlg::CStartupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTDIALOG, pParent)
	, strPlayerName1(_T(""))
	, strPlayerName2(_T(""))
{

}

CStartupDlg::~CStartupDlg()
{
}

void CStartupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER1, strPlayerName1);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER2, strPlayerName2);
	DDX_Control(pDX, ICD_COMBOTYPEPLAYER1, mTypePlayer1);
	DDX_Control(pDX, ICD_COMBOTYPEPLAYER2, mTypePlayer2);
}


BEGIN_MESSAGE_MAP(CStartupDlg, CDialogEx)
	ON_BN_CLICKED(ID_STARTBUTTON, &CStartupDlg::OnBnClickedStartbutton)
END_MESSAGE_MAP()


// Обработчики сообщений CStartupDlg


BOOL CStartupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	mTypePlayer1.SetCurSel(0);
	mTypePlayer2.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CStartupDlg::OnBnClickedStartbutton()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	if ((strPlayerName1 == L"") || (strPlayerName2 == L""))
	{
		AfxMessageBox(L"Имя игрока не может быть пустым!");
		return;
	}

	dlgParent->CreateBoard(10);
	dlgParent->CreatePlayer1(strPlayerName1, mTypePlayer1.GetCurSel());
	dlgParent->CreatePlayer2(strPlayerName2, mTypePlayer2.GetCurSel());
	this->EndDialog(IDOK);
}

void CStartupDlg::SetDlgParent(CTicTacToeTestDlg* p)
{
	this->dlgParent = p;
}