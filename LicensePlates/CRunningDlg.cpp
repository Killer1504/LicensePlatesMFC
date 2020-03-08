// CRunningDlg.cpp : implementation file
//

#include "pch.h"
#include "LicensePlates.h"
#include "CRunningDlg.h"
#include "afxdialogex.h"


// CRunningDlg dialog

IMPLEMENT_DYNAMIC(CRunningDlg, CDialogEx)

CRunningDlg::CRunningDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_RUNNING, pParent)
{

}

CRunningDlg::~CRunningDlg()
{
}

void CRunningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRunningDlg, CDialogEx)
	ON_BN_CLICKED(IDC_TAB_RUNNING_BTN_TEST, &CRunningDlg::OnBnClickedTabRunningBtnTest)
END_MESSAGE_MAP()


// CRunningDlg message handlers


void CRunningDlg::OnBnClickedTabRunningBtnTest()
{
	// TODO: Add your control notification handler code here
	CString cstr = _T("Test");
	AfxMessageBox(cstr, MB_ICONINFORMATION);
}
