
// LicensePlates.h : main header file for the LicensePlates application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

class CMainFrame;
class CLicensePlatesView;
class CLicensePlatesDoc;
// CLicensePlatesApp:
// See LicensePlates.cpp for the implementation of this class
//
extern CMainFrame* pMainFrame;
extern CLicensePlatesDoc* pDoc;
extern CLicensePlatesView* pView;
class CLicensePlatesApp : public CWinApp
{
public:
	CLicensePlatesApp() noexcept;


// Overrides
public:
	
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLicensePlatesApp theApp;
