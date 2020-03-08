#pragma once
#include "pch.h"
#include "Assit.h"


CMainFrame* pMainFrame;
CLicensePlatesDoc* pDoc;
CLicensePlatesView* pView;

string CString2string(CString cstr)
{
	string str;
	str = CT2A(cstr);
	return str;
}

CString double2CString(double db)
{
	string str = to_string(db);
	CString cstr = string2CString(str);
	return cstr;
}

int CString2int(CString cstr)
{
	return _tstoi(cstr);
}

double CString2double(CString cstr)
{
	double db = _ttof(cstr);
	return db;
}

CString string2CString(string str)
{
	CString cstr = _T("");
	cstr = str.c_str();
	return cstr;
}

void InitPointer()
{
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CLicensePlatesDoc*)pMainFrame->GetActiveDocument();
	pView = (CLicensePlatesView*)pMainFrame->GetActiveView();
}
