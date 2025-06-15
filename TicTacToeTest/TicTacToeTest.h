
// TicTacToeTest.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTicTacToeTestApp:
// Сведения о реализации этого класса: TicTacToeTest.cpp
//

class CTicTacToeTestApp : public CWinApp
{
public:
	CTicTacToeTestApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CTicTacToeTestApp theApp;
